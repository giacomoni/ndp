#include "../../../transportlayer/contract/ndp/NDPSocket.h"
#include "inet/common/packet/Message.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/applications/common/SocketTag_m.h"
#include "../../../common/ProtocolNdp.h"

namespace inet {

NDPSocket::NDPSocket() {
    // don't allow user-specified connIds because they may conflict with
    // automatically assigned ones.
    connId = getEnvir()->getUniqueNumber();
}

NDPSocket::NDPSocket(cMessage *msg) {
    connId = check_and_cast<Indication *>(msg)->getTag<SocketInd>()->getSocketId();
    sockstate = CONNECTED;

    if (msg->getKind() == NDP_I_AVAILABLE) {
        NDPAvailableInfo *availableInfo = check_and_cast<NDPAvailableInfo *>(msg->getControlInfo());
        connId = availableInfo->getNewSocketId();
        localAddr = availableInfo->getLocalAddr();
        remoteAddr = availableInfo->getRemoteAddr();
        localPrt = availableInfo->getLocalPort();
        remotePrt = availableInfo->getRemotePort();
    }
    else if (msg->getKind() == NDP_I_ESTABLISHED) {
        // management of stockstate is left to processMessage() so we always
        // set it to CONNECTED in the ctor, whatever TCP_I_xxx arrives.
        // However, for convenience we extract TcpConnectInfo already here, so that
        // remote address/port can be read already after the ctor call.

        NDPConnectInfo *connectInfo = check_and_cast<NDPConnectInfo *>(msg->getControlInfo());
        localAddr = connectInfo->getLocalAddr();
        remoteAddr = connectInfo->getRemoteAddr();
        localPrt = connectInfo->getLocalPort();
        remotePrt = connectInfo->getRemotePort();
    }
}

NDPSocket::NDPSocket(NDPAvailableInfo *availableInfo)
{
    connId = availableInfo->getNewSocketId();
    sockstate = CONNECTED;
    localAddr = availableInfo->getLocalAddr();
    remoteAddr = availableInfo->getRemoteAddr();
    localPrt = availableInfo->getLocalPort();
    remotePrt = availableInfo->getRemotePort();
    EV_INFO << "\n\n\n\nMARKER LOCAL ADDRESS: " << localAddr.str();
}

NDPSocket::~NDPSocket() {
    if (cb) {
        cb->socketDeleted(this);
        cb = nullptr;
    }
    delete receiveQueue;
}


const char *NDPSocket::stateName(NDPSocket::State state) {
#define CASE(x)    case x: \
        s = #x; break
    const char *s = "unknown";
    switch (state) {
    CASE(NOT_BOUND)
;        CASE(BOUND);
        CASE(LISTENING);
        CASE(CONNECTING);
        CASE(CONNECTED);
        CASE(PEER_CLOSED);
        CASE(LOCALLY_CLOSED);
        CASE(CLOSED);
        CASE(SOCKERROR);
    }
    return s;
#undef CASE
}

void NDPSocket::sendToNDP(cMessage *msg, int connId) {
    if (!gateToNdp)
        throw cRuntimeError( "NDPSocket: setOutputGate() must be invoked before socket can be used");

    auto& tags = getTags(msg);
    //tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&ProtocolNdp::ndp);
    tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&ProtocolNdp::ndp);
    tags.addTagIfAbsent<SocketReq>()->setSocketId(connId == -1 ? this->connId : connId);
    check_and_cast<cSimpleModule *>(gateToNdp->getOwnerModule())->send(msg, gateToNdp);
}

void NDPSocket::bind(int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NDPSocket::bind(): socket already bound");

    if (lPort < 0 || lPort > 65535)
        throw cRuntimeError("NDPSocket::bind(): invalid port number %d", lPort);

    localPrt = lPort;
    sockstate = BOUND;
}


void NDPSocket::bind(L3Address lAddr, int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NDPSocket::bind(): socket already bound");

    // allow -1 here, to make it possible to specify address only
    if ((lPort < 0 || lPort > 65535) && lPort != -1)
        throw cRuntimeError("NDPSocket::bind(): invalid port number %d", lPort);
//std::cout << " bind localAddr " << lAddr << "\n";
    localAddr = lAddr;
    localPrt = lPort;
    sockstate = BOUND;
}

 void NDPSocket::listen(bool fork) {

    if (sockstate != BOUND)
        throw cRuntimeError(sockstate == NOT_BOUND ? "NDPSocket: must call bind() before listen()"
                : "NDPSocket::listen(): connect() or listen() already called");

    auto request = new Request("PassiveOPEN", NDP_C_OPEN_PASSIVE);

    NDPOpenCommand *openCmd = new NDPOpenCommand();

    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());
    openCmd->setIsSender(false);
    openCmd->setIsReceiver(true);
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = LISTENING;
    //throw cRuntimeError( "Local address %d Local Port %d", localAddr, localPrt);
}
 void NDPSocket::accept(int socketId)
 {
     auto request = new Request("ACCEPT", NDP_C_ACCEPT);
     NDPAcceptCommand *acceptCmd = new NDPAcceptCommand();
     request->setControlInfo(acceptCmd);
     sendToNDP(request, socketId);
 }

// note: moh i added localAddress here, so instead of waiting for the syn/ack to be received to know my loaca add
// this is now should be known from the par("localAddress"); --> so this par should be specified correctly now
// note that the local port will be assigend by the transport layer (ndpmain based on the available number) see
// ushort Ndp::getEphemeralPort() (its -1 now)

void NDPSocket::connect(L3Address  localAddress ,  L3Address remoteAddress, int remotePort, bool isSender , bool isReceiver  , unsigned int numPacketsToSend , bool isLongFlow   , unsigned int priorityValue) {
    if (sockstate != NOT_BOUND && sockstate != BOUND)
        throw cRuntimeError( "NDPSocket::connect(): connect() or listen() already called (need renewSocket()?)");

    if (remotePort < 0 || remotePort > 65535)
        throw cRuntimeError( "NDPSocket::connect(): invalid remote port number %d", remotePort);


    auto request = new Request("ActiveOPEN", NDP_C_OPEN_ACTIVE);
    localAddr = localAddress;
    remoteAddr = remoteAddress;
    remotePrt = remotePort;
    EV_INFO << "\n\n\n wwwwww socket bind-- localAddr: " << localAddr << "  , remoteAddr: " << remoteAddr << "\n";
    EV_INFO << "localPrt: " << localPrt << " , remotePort:" << remotePrt << "\n\n\n";

    EV_INFO << "\nCreating Command";
    NDPOpenCommand *openCmd = new NDPOpenCommand();
    EV_INFO << "\nCommand Created!";
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setRemoteAddr(remoteAddr);
    openCmd->setRemotePort(remotePrt);

    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());

    EV_INFO << "\n\n\n\nNUMBER OF PACKETS TO SEND: " << numPacketsToSend << "\n\n\n\n";
    openCmd->setNumPacketsToSend(numPacketsToSend);
    openCmd->setPriorityValue(priorityValue);
    openCmd->setIsSender(isSender);
    openCmd->setIsReceiver(isReceiver);
    openCmd->setIsLongFlow(isLongFlow);


    EV_INFO << "\n\n\nCONTROL INFO SENT";
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = CONNECTING;
    EV_INFO << "\n\n\nCONNECTING FINISHED";
}

void NDPSocket::send(Packet *msg) {
    if (sockstate != CONNECTED && sockstate != CONNECTING && sockstate != PEER_CLOSED)
        throw cRuntimeError(
                "NDPSocket::send(): socket not connected or connecting, state is %s",
                stateName(sockstate));

    msg->setKind(NDP_C_SEND);
    sendToNDP(msg);
}

void NDPSocket::sendCommand(Request *msg) {
    sendToNDP(msg);
}

void NDPSocket::close() {
    std::cout << "NDPSocket::close() " << std::endl;
    if (sockstate != CONNECTED && sockstate != PEER_CLOSED
            && sockstate != CONNECTING && sockstate != LISTENING)
        throw cRuntimeError(
                "NDPSocket::close(): not connected or close() already called (sockstate=%s)",
                stateName(sockstate));

    auto request = new Request("CLOSE", NDP_C_CLOSE);
    NDPCommand *cmd = new NDPCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
    sockstate = (sockstate == CONNECTED) ? LOCALLY_CLOSED : CLOSED;
}

void NDPSocket::abort() {
    if (sockstate != NOT_BOUND && sockstate != BOUND && sockstate != CLOSED
            && sockstate != SOCKERROR) {
        auto request = new Request("ABORT", NDP_C_ABORT);
        NDPCommand *cmd = new NDPCommand();
        request->setControlInfo(cmd);
        sendToNDP(request);
    }
    sockstate = CLOSED;
}

void NDPSocket::destroy()
{
    auto request = new Request("DESTROY", NDP_C_DESTROY);
    NDPCommand *cmd = new NDPCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
    sockstate = CLOSED;
}

void NDPSocket::requestStatus() {
    auto request = new Request("STATUS", NDP_C_STATUS);
    NDPCommand *cmd = new NDPCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
}

void NDPSocket::renewSocket() {
    connId = getEnvir()->getUniqueNumber();
    remoteAddr = localAddr = L3Address();
    remotePrt = localPrt = -1;
    sockstate = NOT_BOUND;
}

bool NDPSocket::isOpen() const
{
    switch (sockstate) {
    case BOUND:
    case LISTENING:
    case CONNECTING:
    case CONNECTED:
    case PEER_CLOSED:
    case LOCALLY_CLOSED:
    case SOCKERROR: //TODO check SOCKERROR is opened or is closed socket
        return true;
    case NOT_BOUND:
    case CLOSED:
        return false;
    default:
        throw cRuntimeError("invalid NdpSocket state: %d", sockstate);
    }
}

bool NDPSocket::belongsToSocket(cMessage *msg) const
{
    auto& tags = getTags(msg);
    auto socketInd = tags.findTag<SocketInd>();
    return socketInd != nullptr && socketInd->getSocketId() == connId;
}

void NDPSocket::setCallback(ICallback *callback) {
    cb = callback;
}

void NDPSocket::processMessage(cMessage *msg) {

     ASSERT(belongsToSocket(msg));

    NDPStatusInfo *status;
    NDPAvailableInfo *availableInfo;
    NDPConnectInfo *connectInfo;

    switch (msg->getKind()) {
    case NDP_I_DATA:
        if (cb)
            cb->socketDataArrived(this, check_and_cast<Packet*>(msg), false); // see NdpBasicClientApp::socketDataArrived
        else
            delete msg;

        break;

    case NDP_I_URGENT_DATA:
        if (cb)
            cb->socketDataArrived(this, check_and_cast<Packet*>(msg), true);
        else
            delete msg;

        break;
    case NDP_I_AVAILABLE:
                availableInfo = check_and_cast<NDPAvailableInfo *>(msg->getControlInfo());
                if (cb)
                    cb->socketAvailable(this, availableInfo);
                else
                    accept(availableInfo->getNewSocketId());
                delete msg;
                break;
    case NDP_I_ESTABLISHED:
        // Note: this code is only for sockets doing active open, and nonforking
        // listening sockets. For a forking listening sockets, NDP_I_ESTABLISHED
        // carries a new connId which won't match the connId of this NDPSocket,
        // so you won't get here. Rather, when you see NDP_I_ESTABLISHED, you'll
        // want to create a new NDPSocket object via new NDPSocket(msg).
        sockstate = CONNECTED;
       connectInfo = check_and_cast<NDPConnectInfo *>(msg->getControlInfo());
       localAddr = connectInfo->getLocalAddr();
       remoteAddr = connectInfo->getRemoteAddr();
       localPrt = connectInfo->getLocalPort();
       remotePrt = connectInfo->getRemotePort();
       if (cb)
           cb->socketEstablished(this);
       delete msg;
       break;

    case NDP_I_PEER_CLOSED:
        sockstate = PEER_CLOSED;
        if (cb)
            cb->socketPeerClosed(this);
        delete msg;
        break;

    case NDP_I_CLOSED:
        std::cout << " socket closed \n";
        sockstate = CLOSED;
        if (cb) {
            cb->socketClosed(this);
        }
        delete msg;
        break;

    case NDP_I_CONNECTION_REFUSED:
    case NDP_I_CONNECTION_RESET:
    case NDP_I_TIMED_OUT:
        sockstate = SOCKERROR;
        if (cb)
            cb->socketFailure(this, msg->getKind());
        delete msg;
        break;

    case NDP_I_STATUS:
        status = check_and_cast<NDPStatusInfo *>(msg->removeControlInfo());
        if (cb)
            cb->socketStatusArrived(this, status);
        delete msg;
        break;

    default:
        throw cRuntimeError(
                "NDPSocket: invalid msg kind %d, one of the NDP_I_xxx constants expected",
                msg->getKind());
    }
}


} // namespace inet


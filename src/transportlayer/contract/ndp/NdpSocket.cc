#include "NdpSocket.h"

#include "inet/common/packet/Message.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/Protocol.h"

namespace inet {

NdpSocket::NdpSocket() {
    // don't allow user-specified connIds because they may conflict with
    // automatically assigned ones.
    connId = getEnvir()->getUniqueNumber();
}

NdpSocket::NdpSocket(cMessage *msg) {
    connId =
            check_and_cast<Indication*>(msg)->getTag<SocketInd>()->getSocketId();
    sockstate = CONNECTED;

    if (msg->getKind() == NDP_I_AVAILABLE) {
        NdpAvailableInfo *availableInfo = check_and_cast<NdpAvailableInfo*>(
                msg->getControlInfo());
        connId = availableInfo->getNewSocketId();
        localAddr = availableInfo->getLocalAddr();
        remoteAddr = availableInfo->getRemoteAddr();
        localPrt = availableInfo->getLocalPort();
        remotePrt = availableInfo->getRemotePort();
    } else if (msg->getKind() == NDP_I_ESTABLISHED) {
        // management of stockstate is left to processMessage() so we always
        // set it to CONNECTED in the ctor, whatever TCP_I_xxx arrives.
        // However, for convenience we extract TcpConnectInfo already here, so that
        // remote address/port can be read already after the ctor call.

        NdpConnectInfo *connectInfo = check_and_cast<NdpConnectInfo*>(
                msg->getControlInfo());
        localAddr = connectInfo->getLocalAddr();
        remoteAddr = connectInfo->getRemoteAddr();
        localPrt = connectInfo->getLocalPort();
        remotePrt = connectInfo->getRemotePort();
    }
}

NdpSocket::NdpSocket(NdpAvailableInfo *availableInfo) {
    connId = availableInfo->getNewSocketId();
    sockstate = CONNECTED;
    localAddr = availableInfo->getLocalAddr();
    remoteAddr = availableInfo->getRemoteAddr();
    localPrt = availableInfo->getLocalPort();
    remotePrt = availableInfo->getRemotePort();
}

NdpSocket::~NdpSocket() {
    if (cb) {
        cb->socketDeleted(this);
        cb = nullptr;
    }
    delete receiveQueue;
}

const char* NdpSocket::stateName(NdpSocket::State state) {
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

void NdpSocket::sendToNDP(cMessage *msg, int connId) {
    if (!gateToNdp)
        throw cRuntimeError(
                "NdpSocket: setOutputGate() must be invoked before socket can be used");

    auto &tags = getTags(msg);
    // tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&ProtocolNdp::ndp);
    tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ndp);
    tags.addTagIfAbsent<SocketReq>()->setSocketId(
            connId == -1 ? this->connId : connId);
    check_and_cast<cSimpleModule*>(gateToNdp->getOwnerModule())->send(msg,
            gateToNdp);
}

void NdpSocket::bind(int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NdpSocket::bind(): socket already bound");

    if (lPort < 0 || lPort > 65535)
        throw cRuntimeError("NdpSocket::bind(): invalid port number %d", lPort);

    localPrt = lPort;
    sockstate = BOUND;
}

void NdpSocket::bind(L3Address lAddr, int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NdpSocket::bind(): socket already bound");

    // allow -1 here, to make it possible to specify address only
    if ((lPort < 0 || lPort > 65535) && lPort != -1)
        throw cRuntimeError("NdpSocket::bind(): invalid port number %d", lPort);
    localAddr = lAddr;
    localPrt = lPort;
    sockstate = BOUND;
}

void NdpSocket::listen(bool fork) {

    if (sockstate != BOUND)
        throw cRuntimeError(
                sockstate == NOT_BOUND ?
                        "NdpSocket: must call bind() before listen()" :
                        "NdpSocket::listen(): connect() or listen() already called");

    auto request = new Request("PassiveOPEN", NDP_C_OPEN_PASSIVE);

    NdpOpenCommand *openCmd = new NdpOpenCommand();

    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());
    openCmd->setIsSender(false);
    openCmd->setIsReceiver(true);
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = LISTENING;
}
void NdpSocket::accept(int socketId) {
    auto request = new Request("ACCEPT", NDP_C_ACCEPT);
    NdpAcceptCommand *acceptCmd = new NdpAcceptCommand();
    request->setControlInfo(acceptCmd);
    sendToNDP(request, socketId);
}

// note: moh i added localAddress here, so instead of waiting for the syn/ack to be received to know my loaca add
// this is now should be known from the par("localAddress"); --> so this par should be specified correctly now
// note that the local port will be assigend by the transport layer (ndpmain based on the available number) see
// ushort Ndp::getEphemeralPort() (its -1 now)

void NdpSocket::connect(L3Address localAddress, L3Address remoteAddress,
        int remotePort, bool isSender, bool isReceiver,
        unsigned int numPacketsToSend, bool isLongFlow,
        unsigned int priorityValue) {
    if (sockstate != NOT_BOUND && sockstate != BOUND)
        throw cRuntimeError(
                "NdpSocket::connect(): connect() or listen() already called (need renewSocket()?)");

    if (remotePort < 0 || remotePort > 65535)
        throw cRuntimeError(
                "NdpSocket::connect(): invalid remote port number %d",
                remotePort);

    auto request = new Request("ActiveOPEN", NDP_C_OPEN_ACTIVE);
    localAddr = localAddress;
    remoteAddr = remoteAddress;
    remotePrt = remotePort;
    EV_INFO << "\n\n\n wwwwww socket bind-- localAddr: " << localAddr
                   << "  , remoteAddr: " << remoteAddr << "\n";
    EV_INFO << "localPrt: " << localPrt << " , remotePort:" << remotePrt
                   << "\n\n\n";

    EV_INFO << "\nCreating Command";
    NdpOpenCommand *openCmd = new NdpOpenCommand();
    EV_INFO << "\nCommand Created!";
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setRemoteAddr(remoteAddr);
    openCmd->setRemotePort(remotePrt);

    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());

    EV_INFO << "\nNUMBER OF PACKETS TO SEND: " << numPacketsToSend
                   << "\n";
    openCmd->setNumPacketsToSend(numPacketsToSend);
    openCmd->setPriorityValue(priorityValue);
    openCmd->setIsSender(isSender);
    openCmd->setIsReceiver(isReceiver);
    openCmd->setIsLongFlow(isLongFlow);

    EV_INFO << "\nCONTROL INFO SENT";
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = CONNECTING;
    EV_INFO << "\nCONNECTING FINISHED";
}

void NdpSocket::send(Packet *msg) {
    if (sockstate != CONNECTED && sockstate != CONNECTING
            && sockstate != PEER_CLOSED)
        throw cRuntimeError(
                "NdpSocket::send(): socket not connected or connecting, state is %s",
                stateName(sockstate));

    msg->setKind(NDP_C_SEND);
    sendToNDP(msg);
}

void NdpSocket::sendCommand(Request *msg) {
    sendToNDP(msg);
}

void NdpSocket::close() {
    std::cout << "NdpSocket::close() " << std::endl;
    if (sockstate != CONNECTED && sockstate != PEER_CLOSED
            && sockstate != CONNECTING && sockstate != LISTENING)
        throw cRuntimeError(
                "NdpSocket::close(): not connected or close() already called (sockstate=%s)",
                stateName(sockstate));

    auto request = new Request("CLOSE", NDP_C_CLOSE);
    NdpCommand *cmd = new NdpCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
    sockstate = (sockstate == CONNECTED) ? LOCALLY_CLOSED : CLOSED;
}

void NdpSocket::abort() {
    if (sockstate != NOT_BOUND && sockstate != BOUND && sockstate != CLOSED
            && sockstate != SOCKERROR) {
        auto request = new Request("ABORT", NDP_C_ABORT);
        NdpCommand *cmd = new NdpCommand();
        request->setControlInfo(cmd);
        sendToNDP(request);
    }
    sockstate = CLOSED;
}

void NdpSocket::destroy() {
    auto request = new Request("DESTROY", NDP_C_DESTROY);
    NdpCommand *cmd = new NdpCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
    sockstate = CLOSED;
}

void NdpSocket::requestStatus() {
    auto request = new Request("STATUS", NDP_C_STATUS);
    NdpCommand *cmd = new NdpCommand();
    request->setControlInfo(cmd);
    sendToNDP(request);
}

void NdpSocket::renewSocket() {
    connId = getEnvir()->getUniqueNumber();
    remoteAddr = localAddr = L3Address();
    remotePrt = localPrt = -1;
    sockstate = NOT_BOUND;
}

bool NdpSocket::isOpen() const {
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

bool NdpSocket::belongsToSocket(cMessage *msg) const {
    auto &tags = getTags(msg);
    auto socketInd = tags.findTag<SocketInd>();
    return socketInd != nullptr && socketInd->getSocketId() == connId;
}

void NdpSocket::setCallback(ICallback *callback) {
    cb = callback;
}

void NdpSocket::processMessage(cMessage *msg) {

    ASSERT(belongsToSocket(msg));
    NdpStatusInfo *status;
    NdpAvailableInfo *availableInfo;
    NdpConnectInfo *connectInfo;

    switch (msg->getKind()) {
    case NDP_I_DATA:
        if (cb)
            cb->socketDataArrived(this, check_and_cast<Packet*>(msg), false); // see NdpBasicClientApp::socketDataArrived
        else
            delete msg;

        break;

    case NDP_I_ESTABLISHED:
        // Note: this code is only for sockets doing active open, and nonforking
        // listening sockets. For a forking listening sockets, NDP_I_ESTABLISHED
        // carries a new connId which won't match the connId of this NdpSocket,
        // so you won't get here. Rather, when you see NDP_I_ESTABLISHED, you'll
        // want to create a new NdpSocket object via new NdpSocket(msg).
        sockstate = CONNECTED;
        connectInfo = check_and_cast<NdpConnectInfo*>(msg->getControlInfo());
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
        status = check_and_cast<NdpStatusInfo*>(msg->removeControlInfo());
        if (cb)
            cb->socketStatusArrived(this, status);
        delete msg;
        break;

    default:
        throw cRuntimeError(
                "NdpSocket: invalid msg kind %d, one of the NDP_I_xxx constants expected",
                msg->getKind());
    }
}

} // namespace inet


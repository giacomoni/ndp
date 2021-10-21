#include "NdpSocket.h"

#include "inet/common/packet/Message.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/Protocol.h"

namespace inet {

NdpSocket::NdpSocket()
{
    // don't allow user-specified connIds because they may conflict with
    // automatically assigned ones.
    connId = getEnvir()->getUniqueNumber();
}

NdpSocket::~NdpSocket()
{
    if (cb) {
        cb->socketDeleted(this);
        cb = nullptr;
    }
}

const char* NdpSocket::stateName(NdpSocket::State state)
{
#define CASE(x)    case x: \
        s = #x; break
    const char *s = "unknown";
    switch (state) {
        CASE(NOT_BOUND)
;            CASE(BOUND);
            CASE(LISTENING);
            CASE(CONNECTING);
            CASE(CONNECTED);
        }
    return s;
#undef CASE
}

void NdpSocket::sendToNDP(cMessage *msg, int connId)
{
    if (!gateToNdp)
        throw cRuntimeError("NdpSocket: setOutputGate() must be invoked before socket can be used");

    auto &tags = getTags(msg);
    tags.addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ndp);
    tags.addTagIfAbsent<SocketReq>()->setSocketId(connId == -1 ? this->connId : connId);
    check_and_cast<cSimpleModule*>(gateToNdp->getOwnerModule())->send(msg, gateToNdp);
}

void NdpSocket::bind(L3Address lAddr, int lPort)
{
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NdpSocket::bind(): socket already bound");

    // allow -1 here, to make it possible to specify address only
    if ((lPort < 0 || lPort > 65535) && lPort != -1)
        throw cRuntimeError("NdpSocket::bind(): invalid port number %d", lPort);
    localAddr = lAddr;
    localPrt = lPort;
    sockstate = BOUND;
}

void NdpSocket::listen(bool fork)
{
    if (sockstate != BOUND)
        throw cRuntimeError(sockstate == NOT_BOUND ? "NdpSocket: must call bind() before listen()" : "NdpSocket::listen(): connect() or listen() already called");

    auto request = new Request("PassiveOPEN", NDP_C_OPEN_PASSIVE);
    NdpOpenCommand *openCmd = new NdpOpenCommand();
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = LISTENING;
}
void NdpSocket::accept(int socketId)
{
    throw cRuntimeError("NdpSocket::accept(): never called");
}

void NdpSocket::connect(L3Address localAddress, L3Address remoteAddress, int remotePort, unsigned int numPacketsToSend)
{
    if (sockstate != NOT_BOUND && sockstate != BOUND)
        throw cRuntimeError("NdpSocket::connect(): connect() or listen() already called (need renewSocket()?)");

    if (remotePort < 0 || remotePort > 65535)
        throw cRuntimeError("NdpSocket::connect(): invalid remote port number %d", remotePort);

    auto request = new Request("ActiveOPEN", NDP_C_OPEN_ACTIVE);
    localAddr = localAddress;
    remoteAddr = remoteAddress;
    remotePrt = remotePort;
    EV_INFO << "socket bind-- localAddr: " << localAddr << "  , remoteAddr: " << remoteAddr << endl;
    EV_INFO << "localPrt: " << localPrt << " , remotePort:" << remotePrt << endl;

    NdpOpenCommand *openCmd = new NdpOpenCommand();
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setRemoteAddr(remoteAddr);
    openCmd->setRemotePort(remotePrt);
    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());
    openCmd->setNumPacketsToSend(numPacketsToSend);
    request->setControlInfo(openCmd);
    sendToNDP(request);
    sockstate = CONNECTING;
    EV_INFO << "Socket Connection Finished" << endl;
}

void NdpSocket::send(Packet *msg)
{
    throw cRuntimeError("NdpSocket::send(): never called by application - hack where NDP handles all data");
}

void NdpSocket::close()
{
    throw cRuntimeError("NdpSocket::close(): never called by application");
}

void NdpSocket::abort()
{
    throw cRuntimeError("NdpSocket::abort(): never called by application - hack where NDP handles all data");
}

void NdpSocket::destroy()
{
    throw cRuntimeError("NdpSocket::destroy(): never called by application - hack where NDP handles all data");
}

void NdpSocket::renewSocket()
{
    throw cRuntimeError("NdpSocket::renewSocket(): not needed as the socket should never be closed to begin with");
}

bool NdpSocket::isOpen() const
{
    throw cRuntimeError("NdpSocket::isOpen(): never called");
}

bool NdpSocket::belongsToSocket(cMessage *msg) const
{
    auto &tags = getTags(msg);
    auto socketInd = tags.findTag<SocketInd>();
    return socketInd != nullptr && socketInd->getSocketId() == connId;
}

void NdpSocket::setCallback(ICallback *callback)
{
    cb = callback;
}

void NdpSocket::processMessage(cMessage *msg)
{
    ASSERT(belongsToSocket(msg));
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
        default:
            throw cRuntimeError("NdpSocket: invalid msg kind %d, one of the NDP_I_xxx constants expected", msg->getKind());
    }
}

} // namespace inet


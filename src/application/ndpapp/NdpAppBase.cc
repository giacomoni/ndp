#include "NdpAppBase.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include  "../../transportlayer/contract/ndp/NdpSocket.h"

namespace inet {

void NdpAppBase::initialize(int stage) {
    EV_TRACE << "NdpAppBase::initialize stage " << stage;
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        numSessions = numBroken = packetsSent = packetsRcvd = bytesSent =
                bytesRcvd = 0;
    } else if (stage == INITSTAGE_APPLICATION_LAYER) {
        // parameters
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");

        socket.bind(
                *localAddress ?
                        L3AddressResolver().resolve(localAddress) : L3Address(),
                localPort);
        socket.setCallback(this);
        socket.setOutputGate(gate("socketOut"));
        setStatusString("Sender ready ...");
    }
}

void NdpAppBase::handleMessageWhenUp(cMessage *msg) {
    EV_TRACE << "NdpAppBase::handleMessageWhenUp" << endl;
    if (msg->isSelfMessage()) {
        handleTimer(msg);
    } else
        socket.processMessage(msg);
}

void NdpAppBase::connect() {
    EV_TRACE << "NdpAppBase::connect" << endl;
    // we need a new connId if this is not the first connection
    socket.renewSocket();

    int numPacketsToSend = par("numPacketsToSend").intValue();
    int priorityValue = par("priorityValue").intValue();
    bool isBackroundFlow = par("isBackroundFlow").boolValue();
    bool isSender = par("isSender").boolValue();
    bool isReceiver = par("isReceiver").boolValue();

    // connect
    const char *connectAddress = par("connectAddress");
    int connectPort = par("connectPort");

    L3Address destination;
    L3AddressResolver().tryResolve(connectAddress, destination);

    // added by MOH
    const char *srcAddress = par("localAddress");
    L3Address localAddress;
    L3AddressResolver().tryResolve(srcAddress, localAddress);
    EV_INFO << "localAddress add " << localAddress << endl;

    if (destination.isUnspecified()) {
        EV_ERROR << "Connecting to " << connectAddress << " port="
                        << connectPort
                        << ": cannot resolve destination address\n";
    } else {
        EV_INFO << "Connecting to " << connectAddress << "(" << destination
                       << ") port=" << connectPort << endl;

        setStatusString("connecting");
        socket.connect(localAddress, destination, connectPort, isSender,
                isReceiver, numPacketsToSend, priorityValue);
        EV_INFO << "Connecting to mmmmm" << connectAddress << "(" << destination
                       << ") port=" << connectPort << endl;

        numSessions++;
    }
}

void NdpAppBase::close() {
    setStatusString("closing");
    EV_INFO << "issuing CLOSE command\n";
    socket.close();
}

void NdpAppBase::setStatusString(const char *s) {
    if (hasGUI())
        getDisplayString().setTagArg("t", 0, s);
}

void NdpAppBase::socketEstablished(NdpSocket*) {

    // *redefine* to perform or schedule first sending
    EV_INFO << "\nconnected\n";
    setStatusString("Established");
}

void NdpAppBase::socketDataArrived(NdpSocket*, Packet *msg, bool) {
    // *redefine* to perform or schedule next sending
    packetsRcvd++;
    bytesRcvd += msg->getByteLength();
    delete msg;
}

void NdpAppBase::socketPeerClosed(NdpSocket *socket_) {
    ASSERT(socket_ == &socket);
    // close the connection (if not already closed)
    if (socket.getState() == NdpSocket::PEER_CLOSED) {
        EV_INFO << "remote NDP closed, closing here as well\n";
        close();
    }
}

void NdpAppBase::socketClosed(NdpSocket*) {
    // *redefine* to start another session etc.
    EV_INFO << "connection closed\n";
    setStatusString("closed");
}

void NdpAppBase::socketFailure(NdpSocket*, int code) {
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV_WARN << "connection broken\n";
    setStatusString("broken");
    numBroken++;
}

void NdpAppBase::finish() {
    std::string modulePath = getFullPath();
    EV_INFO << modulePath << ": opened " << numSessions << " sessions\n";
    EV_INFO << modulePath << ": sent " << bytesSent << " bytes in "
                   << packetsSent << " packets\n";
    EV_INFO << modulePath << ": received " << bytesRcvd << " bytes in "
                   << packetsRcvd << " packets\n";

}

} // namespace inet

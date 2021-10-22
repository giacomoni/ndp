#include "NdpAppBase.h"

#include <inet/networklayer/common/L3AddressResolver.h>
#include  "../../transportlayer/contract/ndp/NdpSocket.h"

namespace inet {

void NdpAppBase::initialize(int stage)
{
    EV_TRACE << "NdpAppBase::initialize stage " << stage;
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_APPLICATION_LAYER) {
        // parameters
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");

        socket.bind(*localAddress ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
        socket.setCallback(this);
        socket.setOutputGate(gate("socketOut"));
    }
}

void NdpAppBase::handleMessageWhenUp(cMessage *msg)
{
    EV_TRACE << "NdpAppBase::handleMessageWhenUp" << endl;
    if (msg->isSelfMessage()) {
        handleTimer(msg);
    }
    else {
        socket.processMessage(msg);
    }
}

void NdpAppBase::connect()
{
    EV_TRACE << "NdpAppBase::connect" << endl;

    int numPacketsToSend = par("numPacketsToSend").intValue();

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
        EV_ERROR << "Connecting to " << connectAddress << " port=" << connectPort << ": cannot resolve destination address\n";
    }
    else {
        EV_INFO << "Connecting to " << connectAddress << "(" << destination << ") port=" << connectPort << endl;

        socket.connect(localAddress, destination, connectPort, numPacketsToSend);
        EV_INFO << "Connecting to mmmmm" << connectAddress << "(" << destination << ") port=" << connectPort << endl;
    }
}

void NdpAppBase::close()
{
    EV_INFO << "issuing CLOSE command\n";
    socket.close();
}

void NdpAppBase::socketEstablished(NdpSocket*)
{

    // *redefine* to perform or schedule first sending
    EV_INFO << "connected" << endl;
}

void NdpAppBase::socketDataArrived(NdpSocket*, Packet *msg, bool)
{
    // *redefine* to perform or schedule next sending
    delete msg;
}

void NdpAppBase::socketPeerClosed(NdpSocket *socket_)
{
    throw cRuntimeError("NdpAppBase::socketPeerClosed(): never called");
}

void NdpAppBase::socketClosed(NdpSocket*)
{
    // *redefine* to start another session etc.
    EV_INFO << "connection closed\n";
}

void NdpAppBase::socketFailure(NdpSocket*, int code)
{
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV_WARN << "connection broken\n";
}

void NdpAppBase::finish()
{
    std::string modulePath = getFullPath();
}

} // namespace inet

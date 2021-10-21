#include <iostream>
#include <random>
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"

#include "GenericAppMsgNdp_m.h"
#include "NdpBasicClientApp.h"
namespace inet {

#define MSGKIND_CONNECT    0
#define MSGKIND_SEND       1

Define_Module(NdpBasicClientApp);

NdpBasicClientApp::~NdpBasicClientApp()
{
    cancelAndDelete(timeoutMsg);
}

void NdpBasicClientApp::initialize(int stage)
{
    EV_TRACE << "NdpBasicClientApp::initialize stage " << stage << endl;
    NdpAppBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        timeoutMsg = new cMessage("timer");
    }
}

void NdpBasicClientApp::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t now = simTime();
    simtime_t start = std::max(startTime, now);
    if (timeoutMsg && ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime))) {
        timeoutMsg->setKind(MSGKIND_CONNECT);
        scheduleAt(start, timeoutMsg);
    }
}

void NdpBasicClientApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(timeoutMsg);
    if (socket.getState() == NdpSocket::CONNECTED || socket.getState() == NdpSocket::CONNECTING || socket.getState() == NdpSocket::PEER_CLOSED)
        close();
}

void NdpBasicClientApp::handleCrashOperation(LifecycleOperation *operation)
{
    EV_WARN << "NdpBasicClientApp crash operation" << endl;
    cancelEvent(timeoutMsg);
    if (operation->getRootModule() != getContainingNode(this))
        socket.destroy();
}

void NdpBasicClientApp::handleTimer(cMessage *msg)
{
    // Added MOH send requests based on a timer
    switch (msg->getKind()) {
        case MSGKIND_CONNECT:
            connect();    // active OPEN
            break;
        default:
            throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
    }
}

void NdpBasicClientApp::socketEstablished(NdpSocket *socket)
{
    NdpAppBase::socketEstablished(socket);
}

void NdpBasicClientApp::rescheduleOrDeleteTimer(simtime_t d, short int msgKind)
{
    cancelEvent(timeoutMsg);

    if (stopTime < SIMTIME_ZERO || d < stopTime) {
        timeoutMsg->setKind(msgKind);
        scheduleAt(d, timeoutMsg);
    }
    else {
        delete timeoutMsg;
        timeoutMsg = nullptr;
    }
}

void NdpBasicClientApp::close()
{
    NdpAppBase::close();
    cancelEvent(timeoutMsg);
}
void NdpBasicClientApp::socketClosed(NdpSocket *socket)
{
    NdpAppBase::socketClosed(socket);
}

void NdpBasicClientApp::socketFailure(NdpSocket *socket, int code)
{
    NdpAppBase::socketFailure(socket, code);
    // reconnect after a delay
    if (timeoutMsg) {
        simtime_t d = simTime() + (simtime_t) par("reconnectInterval");
        rescheduleOrDeleteTimer(d, MSGKIND_CONNECT);
    }
}

}    // namespace inet

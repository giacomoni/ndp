#include "NdpServerHostApp.h"
#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace inet {

Define_Module(NdpServerHostApp);

void NdpServerHostApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
}

void NdpServerHostApp::handleStartOperation(LifecycleOperation *operation)
{
    const char *localAddress = par("localAddress");
    int localPort = par("localPort");
    EV_INFO << "\n\nMARKER LOCAL ADDRESS CHAR: " << localAddress;
    serverSocket.setOutputGate(gate("socketOut"));
    serverSocket.setCallback(this);
    //serverSocket.bind(localAddress[0] ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
    serverSocket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), localPort);
    EV_INFO << "\n\n\n\n\nMARKER LOCAL ADDRESS: " << serverSocket.getLocalAddress().str();
    serverSocket.listen();
}

void NdpServerHostApp::handleStopOperation(LifecycleOperation *operation)
{
    for (auto thread: threadSet)
        thread->getSocket()->close();
    serverSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void NdpServerHostApp::handleCrashOperation(LifecycleOperation *operation)
{
    // remove and delete threads
    while (!threadSet.empty()) {
        auto thread = *threadSet.begin();
        // TODO: destroy!!!
        thread->getSocket()->close();
        removeThread(thread);
    }
    // TODO: always?
    if (operation->getRootModule() != getContainingNode(this))
        serverSocket.destroy();
}

void NdpServerHostApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[32];
    sprintf(buf, "%d threads", socketMap.size());
    getDisplayString().setTagArg("t", 0, buf);
}

void NdpServerHostApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        NdpServerThreadBase *thread = (NdpServerThreadBase *)msg->getContextPointer();
        if (threadSet.find(thread) == threadSet.end())
            throw cRuntimeError("Invalid thread pointer in the timer (msg->contextPointer is invalid)");
        thread->timerExpired(msg);
    }
    else {
        NDPSocket *socket = check_and_cast_nullable<NDPSocket*>(socketMap.findSocketFor(msg));
        if (socket)
            socket->processMessage(msg);
        else if (serverSocket.belongsToSocket(msg))
            serverSocket.processMessage(msg);
        else {
            // throw cRuntimeError("Unknown incoming message: '%s'", msg->getName());
            EV_ERROR << "message " << msg->getFullName() << "(" << msg->getClassName() << ") arrived for unknown socket \n";
            delete msg;
        }
    }
}

void NdpServerHostApp::finish()
{
    // remove and delete threads
    while (!threadSet.empty())
        removeThread(*threadSet.begin());
}

void NdpServerHostApp::socketAvailable(NDPSocket *socket, NDPAvailableInfo *availableInfo)
{
    // new NDP connection -- create new socket object and server process
    NDPSocket *newSocket = new NDPSocket(availableInfo);
    newSocket->setOutputGate(gate("socketOut"));

    const char *serverThreadModuleType = par("serverThreadModuleType");
    cModuleType *moduleType = cModuleType::get(serverThreadModuleType);
    char name[80];
    sprintf(name, "thread_%i", newSocket->getSocketId());
    NdpServerThreadBase *proc = check_and_cast<NdpServerThreadBase *>(moduleType->create(name, this));
    proc->finalizeParameters();
    proc->callInitialize();

    newSocket->setCallback(proc);
    proc->init(this, newSocket);

    socketMap.addSocket(newSocket);
    threadSet.insert(proc);

    socket->accept(availableInfo->getNewSocketId());
}

void NdpServerHostApp::socketClosed(NDPSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION && threadSet.empty() && !serverSocket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void NdpServerHostApp::removeThread(NdpServerThreadBase *thread)
{
    // remove socket
    socketMap.removeSocket(thread->getSocket());
    threadSet.erase(thread);

    // remove thread object
    thread->deleteModule();
}

void NdpServerHostApp::threadClosed(NdpServerThreadBase *thread)
{
    // remove socket
    socketMap.removeSocket(thread->getSocket());
    threadSet.erase(thread);

    socketClosed(thread->getSocket());

    // remove thread object
    thread->deleteModule();
}

void NdpServerThreadBase::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 0, NDPSocket::stateName(sock->getState()));
}

} // namespace inet

//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef APPLICATION_NDPAPP_NDPSERVERHOSTAPP_H_
#define APPLICATION_NDPAPP_NDPSERVERHOSTAPP_H_

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/socket/SocketMap.h"
#include "../../transportlayer/contract/ndp/NDPSocket.h"

namespace inet {

//forward declaration:
class NdpServerThreadBase;

/**
 * Hosts a server application, to be subclassed from NdpServerProcess (which
 * is a sSimpleModule). Creates one instance (using dynamic module creation)
 * for each incoming connection. More info in the corresponding NED file.
 */
class INET_API NdpServerHostApp : public ApplicationBase, public NDPSocket::ICallback
{
  protected:
    NDPSocket serverSocket;
    SocketMap socketMap;
    typedef std::set<NdpServerThreadBase *> ThreadSet;
    ThreadSet threadSet;

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    virtual void socketDataArrived(NDPSocket* socket, Packet *msg, bool urgent) override { throw cRuntimeError("Unexpected data"); }
    virtual void socketAvailable(NDPSocket *socket, NDPAvailableInfo *availableInfo) override;
    virtual void socketEstablished(NDPSocket* socket) override {}
    virtual void socketPeerClosed(NDPSocket* socket) override {}
    virtual void socketClosed(NDPSocket* socket) override;
    virtual void socketFailure(NDPSocket* socket, int code) override {}
    virtual void socketStatusArrived(NDPSocket* socket,NDPStatusInfo *status) override { }
    virtual void socketDeleted(NDPSocket* socket) override {}

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

  public:
    virtual ~NdpServerHostApp() { socketMap.deleteSockets(); }
    virtual void removeThread(NdpServerThreadBase *thread);
    virtual void threadClosed(NdpServerThreadBase *thread);

    friend class NdpServerThreadBase;
};

/**
 * Abstract base class for server processes to be used with TcpServerHostApp.
 * Subclasses need to be registered using the Register_Class() macro.
 *
 * @see TcpServerHostApp
 */
class INET_API NdpServerThreadBase : public cSimpleModule, public NDPSocket::ICallback
{
  protected:
    NdpServerHostApp *hostmod;
    NDPSocket *sock;    // ptr into socketMap managed by TcpServerHostApp

    // internal: NDPSocket::ICallback methods
    virtual void socketDataArrived(NDPSocket* socket, Packet *msg, bool urgent) override { dataArrived(msg, urgent); }
    virtual void socketAvailable(NDPSocket* socket, NDPAvailableInfo *availableInfo) override { socket->accept(availableInfo->getNewSocketId()); }
    virtual void socketEstablished(NDPSocket* socket) override { established(); }
    virtual void socketPeerClosed(NDPSocket* socket) override { peerClosed(); }
    virtual void socketClosed(NDPSocket *socket) override { hostmod->threadClosed(this); };
    virtual void socketFailure(NDPSocket* socket, int code) override { failure(code); }
    virtual void socketStatusArrived(NDPSocket* socket,NDPStatusInfo *status) override { statusArrived(status); }
    virtual void socketDeleted(NDPSocket* socket) override { if (socket == sock) sock = nullptr; }

    virtual void refreshDisplay() const override;

  public:

    NdpServerThreadBase() { sock = nullptr; hostmod = nullptr; }
    virtual ~NdpServerThreadBase() { delete sock; }

    // internal: called by NdpServerHostApp after creating this module
    virtual void init(NdpServerHostApp *hostmodule, NDPSocket *socket) { hostmod = hostmodule; sock = socket; }

    /*
     * Returns the socket object
     */
    virtual NDPSocket *getSocket() { return sock; }

    /*
     * Returns pointer to the host module
     */
    virtual NdpServerHostApp *getHostModule() { return hostmod; }

    /**
     * Called when connection is established. To be redefined.
     */
    virtual void established() = 0;

    /*
     * Called when a data packet arrives. To be redefined.
     */
    virtual void dataArrived(Packet *msg, bool urgent) = 0;

    /*
     * Called when a timer (scheduled via scheduleAt()) expires. To be redefined.
     */
    virtual void timerExpired(cMessage *timer) = 0;

    /*
     * Called when the client closes the connection. By default it closes
     * our side too, but it can be redefined to do something different.
     */
    virtual void peerClosed() { getSocket()->close(); }

    /*
     * Called when the connection breaks (TCP error). By default it deletes
     * this thread, but it can be redefined to do something different.
     */
    virtual void failure(int code) { hostmod->removeThread(this); }

    /*
     * Called when a status arrives in response to getSocket()->getStatus().
     * By default it deletes the status object, redefine it to add code
     * to examine the status.
     */
    virtual void statusArrived(NDPStatusInfo *status) { }
};

} // namespace inet

#endif // ifndef __INET_TCPSRVHOSTAPP_H

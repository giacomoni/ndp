#ifndef __NDP_RAPTONDPAPPBASE_H
#define __NDP_RAPTONDPAPPBASE_H

#include <inet/common/INETDefs.h>
#include <inet/applications/base/ApplicationBase.h>
#include "../../transportlayer/contract/ndp/NdpSocket.h"

namespace inet {

/**
 * Base class for clients app for NDP-based request-reply protocols or apps.
 * Handles a single session (and NDP connection) at a time.
 *
 * It needs the following NED parameters: localAddress, localPort, connectAddress, connectPort.
 */
class INET_API NdpAppBase : public ApplicationBase, public NdpSocket::ICallback
{
protected:
    NdpSocket socket;

protected:
    // Initializes the application, binds the socket to the local address and port.
    virtual void initialize(int stage) override;

    virtual int numInitStages() const override
    {
        return NUM_INIT_STAGES;
    }

    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;

    /* Utility functions */
    // Creates a socket connection based on the NED parameters specified.
    virtual void connect();
    // Closes the socket.
    virtual void close();

    /* NdpSocket::ICallback callback methods */
    virtual void handleTimer(cMessage *msg) = 0;

    // Called once the socket is established. Currently does nothing but set the status string.
    virtual void socketEstablished(NdpSocket *socket) override;

    //Called once a packet arrives at the application.
    virtual void socketDataArrived(NdpSocket *socket, Packet *msg, bool urgent) override;

    virtual void socketAvailable(NdpSocket *socket, NdpAvailableInfo *availableInfo) override
    {
        socket->accept(availableInfo->getNewSocketId());
    }
    virtual void socketPeerClosed(NdpSocket *socket) override;
    virtual void socketClosed(NdpSocket *socket) override;
    virtual void socketFailure(NdpSocket *socket, int code) override;
    virtual void socketStatusArrived(NdpSocket *socket, NdpStatusInfo *status)
    override
    {
        delete status;
    }
    virtual void socketDeleted(NdpSocket *socket) override
    {
    }
};

} // namespace inet

#endif // ifndef __INET_RAPTONDPAPPBASE_H


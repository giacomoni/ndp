

#ifndef __NDP_RAPTONDPAPPBASE_H
#define __NDP_RAPTONDPAPPBASE_H

#include "inet/common/INETDefs.h"
#include "../../transportlayer/contract/ndp/NDPSocket.h"
#include "inet/applications/base/ApplicationBase.h"

namespace inet {

/**
 * Base class for clients app for NDP-based request-reply protocols or apps.
 * Handles a single session (and NDP connection) at a time.
 *
 * It needs the following NED parameters: localAddress, localPort, connectAddress, connectPort.
 */
class INET_API NdpAppBase : public ApplicationBase, public NDPSocket::ICallback
{
  protected:
    NDPSocket socket;

    // statistics
    int numSessions;
    int numBroken;
    int packetsSent;
    int packetsRcvd;
    int bytesSent;
    long bytesRcvd;




  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;

    /* Utility functions */
    virtual void connect();
    virtual void close();
    virtual void sendPacket(cPacket *pkt);
    virtual void setStatusString(const char *s);

    /* NDPSocket::ICallback callback methods */
    virtual void handleTimer(cMessage *msg) = 0;

    virtual void socketEstablished(NDPSocket *socket) override;
    virtual void socketDataArrived(NDPSocket *socket, Packet *msg, bool urgent) override;
    virtual void socketAvailable(NDPSocket *socket, NDPAvailableInfo *availableInfo) override { socket->accept(availableInfo->getNewSocketId()); }
    virtual void socketPeerClosed(NDPSocket *socket) override;
    virtual void socketClosed(NDPSocket *socket) override;
    virtual void socketFailure(NDPSocket *socket, int code) override;
    virtual void socketStatusArrived(NDPSocket *socket, NDPStatusInfo *status) override { delete status; }
};

} // namespace inet

#endif // ifndef __INET_RAPTONDPAPPBASE_H


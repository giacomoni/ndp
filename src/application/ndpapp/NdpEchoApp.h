
#ifndef __INET_NdpEchoApp_H
#define __INET_NdpEchoApp_H

#include "inet/common/INETDefs.h"
#include "inet/common/INETMath.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "../../transportlayer/contract/ndp/NDPSocket.h"
#include "NdpServerHostApp.h"

namespace inet {
/**
 * Accepts any number of incoming connections, and sends back whatever
 * arrives on them.
 */
class NdpEchoApp : public NdpServerHostApp
{
  protected:
    simtime_t delay;
    double echoFactor = NaN;

    long bytesRcvd = 0;
    long bytesSent = 0;

  protected:
    virtual void sendDown(Packet *packet);

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void finish() override;
    virtual void refreshDisplay() const override;

  public:
    NdpEchoApp();
    ~NdpEchoApp();

    friend class NdpEchoAppThread;
};

class INET_API NdpEchoAppThread : public NdpServerThreadBase
{
  protected:
    NdpEchoApp *echoAppModule = nullptr;

  public:
    /**
     * Called when connection is established.
     */
    virtual void established() override;

    /*
     * Called when a data packet arrives. To be redefined.
     */
    virtual void dataArrived(Packet *msg, bool urgent) override;

    /*
     * Called when a timer (scheduled via scheduleAt()) expires. To be redefined.
     */
    virtual void timerExpired(cMessage *timer) override;

    virtual void init(NdpServerHostApp *hostmodule, NDPSocket *socket) override { NdpServerThreadBase::init(hostmodule, socket); echoAppModule = check_and_cast<NdpEchoApp *>(hostmod); }
};

} // namespace inet
#endif // ifndef __INET_NdpEchoApp_H



#ifndef __INET_NdpBasicClientApp_H
#define __INET_NdpBasicClientApp_H
#include "NdpAppBase.h"
#include "inet/common/INETDefs.h"

#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/lifecycle/ILifecycle.h"

namespace inet {

/**
 * An example request-reply based client application.
 */
class INET_API NdpBasicClientApp : public NdpAppBase
{
  protected:
    cMessage *timeoutMsg = nullptr;
    NodeStatus *nodeStatus = nullptr;

    static simsignal_t packetReceivedSignal; // moh


    simtime_t startTime;
    simtime_t stopTime;
    unsigned int sendBytes = 0;


    #define NDP_TIMEOUT_REQUEST_REXMIT_MAX    240  // 4 mins (will only be used with request)
    #define MAX_REQUEST_REXMIT_COUNT         5     // (Added)
    #define NDP_TIMEOUT_REQUEST_REXMIT        1     // (Added)  request timeout
    int request_rexmit_count;                      // (Added) number of request retransmissions
    simtime_t request_rexmit_timeout;              // (Added) current request retransmission timeout
    cMessage *requestRexmitTimer = nullptr;        // (Added) for retransmitting request


    virtual void sendWriteRequest();

    virtual void rescheduleOrDeleteTimer(simtime_t d, short int msgKind);
//    virtual void  startRequestRexmitTimer(); // Added

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleTimer(cMessage *msg) override;

    virtual void socketEstablished(NDPSocket *socket) override;
    virtual void socketDataArrived(NDPSocket *socket, Packet *msg, bool urgent) override;
    virtual void socketClosed(NDPSocket *socket) override;
    virtual void socketFailure(NDPSocket *socket, int code) override;

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual void close() override;

  public:
    NdpBasicClientApp() {}
    virtual ~NdpBasicClientApp();
};

} // namespace inet

#endif // ifndef __INET_NdpBasicClientApp_H


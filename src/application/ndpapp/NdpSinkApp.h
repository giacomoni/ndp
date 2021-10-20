
#ifndef __INET_NdpSinkApp_H
#define __INET_NdpSinkApp_H

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "../../transportlayer/contract/ndp/NdpSocket.h"
#include "inet/common/lifecycle/ILifecycle.h"
namespace inet {

/**
 * Accepts any number of incoming connections, and discards whatever arrives
 * on them.
 */
class INET_API NdpSinkApp : public cSimpleModule, public ILifecycle
{
  protected:
    long bytesRcvd;
    NdpSocket socket;

     //statistics:
    static simsignal_t rcvdPkSignalNDP;

    cMessage *timeoutMsg = nullptr;
    // MOH: added
    simtime_t tStartAdded;
    simtime_t tEndAdded;
    double numRcvTrimmedHeader = 0 ;

    bool firstDataReceived = true;

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    virtual bool handleOperationStage(LifecycleOperation *operation, IDoneCallback *doneCallback) override
    { Enter_Method_Silent(); throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName()); return true; }
};

} // namespace inet

#endif // ifndef __INET_NdpSinkApp_H


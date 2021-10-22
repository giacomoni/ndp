#ifndef __INET_NdpSinkApp_H
#define __INET_NdpSinkApp_H

#include <inet/common/INETDefs.h>
#include <inet/common/lifecycle/LifecycleOperation.h>
#include <inet/common/lifecycle/ILifecycle.h>

#include "../../transportlayer/contract/ndp/NdpSocket.h"
namespace inet {

/**
 * Accepts any number of incoming connections, and discards whatever arrives
 * on them.
 */
class INET_API NdpSinkApp : public cSimpleModule
{
protected:
    long bytesRcvd;
    NdpSocket socket;
    //statistics:
    static simsignal_t rcvdPkSignalNDP;
    // MOH: added
    simtime_t tStartAdded;
    simtime_t tEndAdded;
    double numRcvTrimmedHeader = 0;
    bool firstDataReceived = true;

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override
    {
        return NUM_INIT_STAGES;
    }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;
};

} // namespace inet

#endif // ifndef __INET_NdpSinkApp_H


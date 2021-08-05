
#ifndef __INET_NdpSinkApp_H
#define __INET_NdpSinkApp_H

#include "NdpServerHostApp.h"
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
//#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "../../transportlayer/contract/ndp/NDPSocket.h"




namespace inet {

/**
 * Accepts any number of incoming connections, and discards whatever arrives
 * on them.
 */
class INET_API NdpSinkApp : public NdpServerHostApp
{
  protected:
    long bytesRcvd;
     //statistics:
//    static simsignal_t fctRecordv1;

    cMessage *timeoutMsg = nullptr;
    // MOH: added

    cGate *gateToNdp;


    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

  public:
    NdpSinkApp();
    ~NdpSinkApp();

    friend class NdpSinkAppThread;
};

class INET_API NdpSinkAppThread : public NdpServerThreadBase
{
  protected:
    static simsignal_t rcvdPkSignalNDP;
    long bytesRcvd;
    simtime_t tStartAdded;
    simtime_t tEndAdded;
    bool firstDataReceived = true;
    bool isLongFlow;
    unsigned int numRcvTrimmedHeader = 0 ;
    NdpSinkApp *sinkAppModule = nullptr;

    virtual void sendRequest();
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void refreshDisplay() const override;
    virtual void finish() override;
    //TcpServerThreadBase:
    /**
     * Called when connection is established.
     */
    virtual void established() override;

    /*
     * Called when a data packet arrives.
     */
    virtual void dataArrived(Packet *msg, bool urgent) override;

    /*
     * Called when a timer (scheduled via scheduleAt()) expires.
     */
    virtual void timerExpired(cMessage *timer) override { throw cRuntimeError("Model error: unknown timer message arrived"); }

    virtual void init(NdpServerHostApp *hostmodule, NDPSocket *socket) override { NdpServerThreadBase::init(hostmodule, socket); sinkAppModule = check_and_cast<NdpSinkApp *>(hostmod); }
};
} // namespace inet

#endif // ifndef __INET_NdpSinkApp_H


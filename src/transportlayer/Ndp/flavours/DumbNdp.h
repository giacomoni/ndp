
#ifndef __INET_DumbNdp_H
#define __INET_DumbNdp_H

#include "inet/common/INETDefs.h"
#include "../NdpAlgorithm.h"

namespace inet {

namespace ndp {

/**
 * State variables for DumbNdp.
 */
class INET_API DumbNdpStateVariables : public NdpStateVariables
{
  public:
    //...
};

/**
 * A very-very basic NdpAlgorithm implementation, with hardcoded
 * retransmission timeout and no other sophistication. It can be
 * used to demonstrate what happened if there was no adaptive
 * timeout calculation, delayed acks, silly window avoidance,
 * congestion control, etc.
 */
class INET_API DumbNdp : public NdpAlgorithm
{
  protected:
    DumbNdpStateVariables *& state;    // alias to TCLAlgorithm's 'state'

    cMessage *rexmitTimer;    // retransmission timer

  protected:
    /** Creates and returns a DumbNdpStateVariables object. */
    virtual NdpStateVariables *createStateVariables() override
    {
        return new DumbNdpStateVariables();
    }

  public:
    /** Ctor */
    DumbNdp();

    virtual ~DumbNdp();

    virtual void initialize() override;

    virtual void connectionClosed() override;

    virtual void processTimer(cMessage *timer, NdpEventCode& event) override;

    virtual void dataSent(uint32 fromseq) override;
};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_DumbNdp_H


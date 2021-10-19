
#ifndef __INET_DUMBNDP_H
#define __INET_DUMBNDP_H

#include "../../../transportlayer/Ndp/NDPAlgorithm.h"
#include "inet/common/INETDefs.h"


namespace inet {

namespace ndp {

/**
 * State variables for DumbNDP.
 */
class INET_API DumbNDPStateVariables : public NdpStateVariables
{
  public:
    //...
};

/**
 * A very-very basic NDPAlgorithm implementation, with hardcoded
 * retransmission timeout and no other sophistication. It can be
 * used to demonstrate what happened if there was no adaptive
 * timeout calculation, delayed acks, silly window avoidance,
 * congestion control, etc.
 */
class INET_API DumbNDP : public NDPAlgorithm
{
  protected:
    DumbNDPStateVariables *& state;    // alias to TCLAlgorithm's 'state'

    cMessage *rexmitTimer;    // retransmission timer

  protected:
    /** Creates and returns a DumbNDPStateVariables object. */
    virtual NdpStateVariables *createStateVariables() override
    {
        return new DumbNDPStateVariables();
    }

  public:
    /** Ctor */
    DumbNDP();

    virtual ~DumbNDP();

    virtual void initialize() override;

    virtual void connectionClosed() override;

    virtual void processTimer(cMessage *timer, NDPEventCode& event) override;

    virtual void dataSent(uint32 fromseq) override;
};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_DUMBNDP_H


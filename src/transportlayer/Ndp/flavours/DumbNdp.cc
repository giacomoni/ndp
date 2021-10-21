
#include "DumbNdp.h"

#include "../Ndp.h"

namespace inet {

namespace ndp {

Register_Class(DumbNdp);

#define REXMIT_TIMEOUT    2 // Just a dummy value

DumbNdp::DumbNdp() :
        NdpAlgorithm(), state((DumbNdpStateVariables*&) NdpAlgorithm::state)
{
    rexmitTimer = nullptr;
}

DumbNdp::~DumbNdp()
{
    // cancel and delete timers
    if (rexmitTimer)
        delete conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNdp::initialize()
{
    NdpAlgorithm::initialize();

    rexmitTimer = new cMessage("DumbNdp-REXMIT");
    rexmitTimer->setContextPointer(conn);
}

void DumbNdp::connectionClosed()
{
    conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNdp::processTimer(cMessage *timer, NdpEventCode &event)
{
    if (timer != rexmitTimer)
        throw cRuntimeError(timer, "unrecognized timer");
    conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

void DumbNdp::dataSent(uint32 fromseq)
{
    if (rexmitTimer->isScheduled()){
        conn->getNDPMain()->cancelEvent(rexmitTimer);
    }
    conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

} // namespace NDP

} // namespace inet


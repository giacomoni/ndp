

#include "DumbNDP.h"

#include "../Ndp.h"

namespace inet {

namespace ndp {

Register_Class(DumbNDP);

// just a dummy value
#define REXMIT_TIMEOUT    2

DumbNDP::DumbNDP() : NDPAlgorithm(),
    state((DumbNDPStateVariables *&)NDPAlgorithm::state)
{
    rexmitTimer = nullptr;
}

DumbNDP::~DumbNDP()
{
    // cancel and delete timers
    if (rexmitTimer)
        delete conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNDP::initialize()
{
    NDPAlgorithm::initialize();

    rexmitTimer = new cMessage("DumbNDP-REXMIT");
    rexmitTimer->setContextPointer(conn);
}

void DumbNDP::connectionClosed()
{
    conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNDP::processTimer(cMessage *timer, NDPEventCode& event)
{
    if (timer != rexmitTimer)
        throw cRuntimeError(timer, "unrecognized timer");
    conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

void DumbNDP::dataSent(uint32 fromseq)
{
    if (rexmitTimer->isScheduled())
     conn->getNDPMain()->cancelEvent(rexmitTimer);
     conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

} // namespace NDP

} // namespace inet


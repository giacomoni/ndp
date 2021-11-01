#include <string.h>
#include <assert.h>

#include "ndp_common/NdpHeader.h"
#include "Ndp.h"
#include "NdpAlgorithm.h"
#include "NdpConnection.h"
#include "NdpSendQueue.h"

using namespace std;
namespace inet {

namespace ndp {
Define_Module(NdpConnection);

NdpStateVariables::NdpStateVariables() {
    internal_request_id = 0;
    request_id = 0;  // source block number (8-bit unsigned integer)

    numPacketsToGet = 0;
    numPacketsToSend = 0;

    numRcvTrimmedHeader = 0;
    numberReceivedPackets = 0;
    numberSentPackets = 0;
    IW = 0; // send the initial window (12 Packets as in NDP) IWWWWWWWWWWWW
    connFinished = false;
    isfinalReceivedPrintedOut = false;
    numRcvdPkt = 0;
    delayedNackNo = 0;
    connNotAddedYet = true;

    active = false;
}

std::string NdpStateVariables::str() const {
    std::stringstream out;
    return out.str();
}

std::string NdpStateVariables::detailedInfo() const {
    std::stringstream out;
    out << "active=" << active << "\n";
    return out.str();
}

void NdpConnection::initConnection(Ndp *_mod, int _socketId) {
    Enter_Method_Silent
    ();

    ndpMain = _mod;
    socketId = _socketId;

    fsm.setName(getName());
    fsm.setState(NDP_S_INIT);

    // queues and algorithm will be created on active or passive open
}

NdpConnection::~NdpConnection() {

    std::list<PacketsToSend>::iterator iter;  // received iterator

    while (!receivedPacketsList.empty()) {
        delete receivedPacketsList.front().msg;
        receivedPacketsList.pop_front();
    }

    delete sendQueue;
    delete ndpAlgorithm;
    delete state;
}

void NdpConnection::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (!processTimer(msg))
            EV_INFO << "\nConnection Attempted Removal!\n";
    } else
        throw cRuntimeError(
                "model error: NdpConnection allows only self messages");
}

bool NdpConnection::processTimer(cMessage *msg) {
    printConnBrief();
    EV_DETAIL << msg->getName() << " timer expired\n";

    // first do actions
    NdpEventCode event;
    event = NDP_E_IGNORE;
    ndpAlgorithm->processTimer(msg, event); // seeeee processTimer method in NDPBaseAlg.cc
    // then state transitions
    return performStateTransition(event);
}

bool NdpConnection::processNDPSegment(Packet *packet,
        const Ptr<const NdpHeader> &ndpseg, L3Address segSrcAddr,
        L3Address segDestAddr) {
    Enter_Method_Silent
    ();

    printConnBrief();
    NdpEventCode event = process_RCV_SEGMENT(packet, ndpseg, segSrcAddr,
            segDestAddr);
    // then state transitions
    return performStateTransition(event);
}

bool NdpConnection::processAppCommand(cMessage *msg) {
    Enter_Method_Silent
    ();

    printConnBrief();

    NdpCommand *ndpCommand = check_and_cast_nullable<NdpCommand*>(
            msg->removeControlInfo());
    NdpEventCode event = preanalyseAppCommandEvent(msg->getKind());
    EV_INFO << "App command eventName: " << eventName(event) << "\n";
//     std::cout << "App command: " << eventName(event) << std::endl;
    switch (event) {
    case NDP_E_OPEN_ACTIVE:
        process_OPEN_ACTIVE(event, ndpCommand, msg);
        break;

    case NDP_E_OPEN_PASSIVE:
        process_OPEN_PASSIVE(event, ndpCommand, msg);
        break;

    default:
        throw cRuntimeError(ndpMain, "wrong event code");
    }

    // then state transitions
    return performStateTransition(event);
}

NdpEventCode NdpConnection::preanalyseAppCommandEvent(int commandCode) {
    switch (commandCode) {
    case NDP_C_OPEN_ACTIVE:
        return NDP_E_OPEN_ACTIVE;

    case NDP_C_OPEN_PASSIVE:
        return NDP_E_OPEN_PASSIVE;

    default:
        throw cRuntimeError(ndpMain, "Unknown message kind in app command");
    }
}

bool NdpConnection::performStateTransition(const NdpEventCode &event) {
    ASSERT(fsm.getState() != NDP_S_CLOSED); // closed connections should be deleted immediately

    if (event == NDP_E_IGNORE) {    // e.g. discarded segment
        EV_DETAIL << "Staying in state: " << stateName(fsm.getState())
                         << " (no FSM event)\n";
        return true;
    }

    // state machine
    // TBD add handling of connection timeout event (KEEP-ALIVE), with transition to CLOSED
    // Note: empty "default:" lines are for gcc's benefit which would otherwise spit warnings
    int oldState = fsm.getState();

    switch (fsm.getState()) {
    case NDP_S_INIT:
        switch (event) {
        case NDP_E_OPEN_PASSIVE:
            FSM_Goto(fsm, NDP_S_LISTEN);
            break;

        case NDP_E_OPEN_ACTIVE:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);

//            FSM_Goto(fsm, NDP_S_SYN_SENT); mohhh
            break;

        default:
            break;
        }
        break;

    case NDP_S_LISTEN:
        switch (event) {
        case NDP_E_OPEN_ACTIVE:
            FSM_Goto(fsm, NDP_S_SYN_SENT);
            break;

        case NDP_E_RCV_SYN:
            FSM_Goto(fsm, NDP_S_SYN_RCVD);
            break;

        default:
            break;
        }
        break;

    case NDP_S_SYN_RCVD:
        switch (event) {

        default:
            break;
        }
        break;

    case NDP_S_SYN_SENT:
        switch (event) {

        case NDP_E_RCV_SYN:
            FSM_Goto(fsm, NDP_S_SYN_RCVD);
            break;

        default:
            break;
        }
        break;

    case NDP_S_ESTABLISHED:
        switch (event) {

        default:
            break;
        }
        break;

    case NDP_S_CLOSED:
        break;
    }

    if (oldState != fsm.getState()) {
        EV_INFO << "Transition: " << stateName(oldState) << " --> "
                       << stateName(fsm.getState()) << "  (event was: "
                       << eventName(event) << ")\n";
        EV_DEBUG_C("testing") << ndpMain->getName() << ": "
                                     << stateName(oldState) << " --> "
                                     << stateName(fsm.getState()) << "  (on "
                                     << eventName(event) << ")\n";

        // cancel timers, etc.
        stateEntered(fsm.getState(), oldState, event);
    } else {
        EV_DETAIL << "Staying in state: " << stateName(fsm.getState())
                         << " (event was: " << eventName(event) << ")\n";
    }

    return fsm.getState() != NDP_S_CLOSED;
}

void NdpConnection::stateEntered(int state, int oldState, NdpEventCode event) {
    // cancel timers
    switch (state) {
    case NDP_S_INIT:
        // we'll never get back to INIT
        break;

    case NDP_S_LISTEN:
        // we may get back to LISTEN from SYN_RCVD
        break;

    case NDP_S_SYN_RCVD:
    case NDP_S_SYN_SENT:
        break;

    case NDP_S_ESTABLISHED:
        // we're in ESTABLISHED, these timers are no longer needed
        // NDP_I_ESTAB notification moved inside event processing
        break;

    case NDP_S_CLOSED:
        sendIndicationToApp(NDP_I_CLOSED);
        // all timers need to be cancelled
        ndpAlgorithm->connectionClosed();
        break;
    }
}
} // namespace NDP
} // namespace inet


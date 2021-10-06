#include <string.h>
#include <assert.h>

#include "ndp_common/NdpHeader.h"
#include "Ndp.h"
#include "NDPAlgorithm.h"
#include "NDPReceiveQueue.h"
#include "NDPSendQueue.h"
#include "../contract/ndp/NDPCommand_m.h"
#include "NDPConnection.h"


using namespace std;
namespace inet {

namespace ndp {
Define_Module(NDPConnection);

//simsignal_t NDPConnection::stateSignal = registerSignal("state");    // FSM state
//simsignal_t NDPConnection::sndWndSignal = registerSignal("sndWnd");    // snd_wnd
//simsignal_t NDPConnection::rcvWndSignal = registerSignal("rcvWnd");    // rcv_wnd
//simsignal_t NDPConnection::rcvAdvSignal = registerSignal("rcvAdv");    // current advertised window (=rcv_adv)
//simsignal_t NDPConnection::sndNxtSignal = registerSignal("sndNxt");    // sent seqNo
//simsignal_t NDPConnection::sndAckSignal = registerSignal("sndAck");    // sent ackNo
//simsignal_t NDPConnection::rcvSeqSignal = registerSignal("rcvSeq");    // received seqNo
//simsignal_t NDPConnection::rcvAckSignal = registerSignal("rcvAck");    // received ackNo (=snd_una)
//simsignal_t NDPConnection::unackedSignal = registerSignal("unacked");    // number of bytes unacknowledged
//simsignal_t NDPConnection::dupAcksSignal = registerSignal("dupAcks");    // current number of received dupAcks
//simsignal_t NDPConnection::pipeSignal = registerSignal("pipe");    // current sender's estimate of bytes outstanding in the network
//simsignal_t NDPConnection::sndSacksSignal = registerSignal("sndSacks");    // number of sent Sacks
//simsignal_t NDPConnection::rcvSacksSignal = registerSignal("rcvSacks");    // number of received Sacks
//simsignal_t NDPConnection::rcvOooSegSignal = registerSignal("rcvOooSeg");    // number of received out-of-order segments
//simsignal_t NDPConnection::rcvNASegSignal = registerSignal("rcvNASeg");    // number of received not acceptable segments
//simsignal_t NDPConnection::sackedBytesSignal = registerSignal("sackedBytes");    // current number of received sacked bytes
//simsignal_t NDPConnection::tcpRcvQueueBytesSignal = registerSignal("ndpRcvQueueBytes");    // current amount of used bytes in tcp receive queue
//simsignal_t NDPConnection::tcpRcvQueueDropsSignal = registerSignal("ndpRcvQueueDrops");    // number of drops in tcp receive queue
NdpStateVariables::NdpStateVariables() {
    internal_request_id = 0;
    request_id = 0;  // source block number (8-bit unsigned integer)

    numPacketsToGet = 0;
    numPacketsToSend = 0;
    priorityValue = 0;
    isLongFlow = false;
    isSender = false;
    isReceiver =false;

    numRcvTrimmedHeader = 0;
    numberReceivedPackets = 0;
    numberSentPackets=0;
    IW = 0; // send the initial window (12 Packets as in NDP) IWWWWWWWWWWWW
    connFinished= false;

    isfinalReceivedPrintedOut = false;
//    sequenceNumber = 0;

    numRcvdPkt=0;

    request_rexmit_count = 0;
    request_rexmit_timeout = 0;
    numPullsTimeOuts = 0;
    isHeader = false;
    connNotAddedYet = true;

    active = false;
    //fork = false;
    snd_mss = 0;
    iss = 0;

    syn_rexmit_count = 0;
    syn_rexmit_timeout = 0;
}

std::string NdpStateVariables::str() const {
    std::stringstream out;
    return out.str();
}

std::string NdpStateVariables::detailedInfo() const {
    std::stringstream out;
    out << "active=" << active << "\n";
    out << "snd_mss=" << snd_mss << "\n";
    out << "iss=" << iss << "\n";
    out << "irs=" << irs << "\n";
    return out.str();
}

void NDPConnection::initConnection(Ndp *_mod, int _socketId) {
    Enter_Method_Silent();

    ndpMain = _mod;
    socketId = _socketId;

    fsm.setName(getName());
    fsm.setState(NDP_S_INIT);

    // queues and algorithm will be created on active or passive open

    requestInternalTimer = new cMessage("requestInternalTimer");
    the2MSLTimer = new cMessage("2MSL");
    connEstabTimer = new cMessage("CONN-ESTAB");
    finWait2Timer = new cMessage("FIN-WAIT-2");
    synRexmitTimer = new cMessage("SYN-REXMIT");

    requestInternalTimer->setContextPointer(this);
    the2MSLTimer->setContextPointer(this);
    connEstabTimer->setContextPointer(this);
    finWait2Timer->setContextPointer(this);
    synRexmitTimer->setContextPointer(this);
}

NDPConnection::~NDPConnection() {

    std::list<PacketsToSend>::iterator iter;  // received iterator

    while (!receivedPacketsList.empty()) {
        delete receivedPacketsList.front().msg;
        receivedPacketsList.pop_front();
    }

    delete sendQueue;
//    delete rexmitQueue;
    delete receiveQueue;
    delete ndpAlgorithm;
    delete state;

    if (the2MSLTimer)
        delete cancelEvent(the2MSLTimer);
    if (connEstabTimer)
        delete cancelEvent(connEstabTimer);
    if (finWait2Timer)
        delete cancelEvent(finWait2Timer);
    if (synRexmitTimer)
        delete cancelEvent(synRexmitTimer);
    if (requestInternalTimer)
        delete cancelEvent(requestInternalTimer);
}

void NDPConnection::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (!processTimer(msg))
            EV_INFO << "\nConnection Attempted Removal!\n";
            //ndpMain->removeConnection(this);
    }
    else
        throw cRuntimeError("model error: NDPConnection allows only self messages");
}

bool NDPConnection::processTimer(cMessage *msg) {
    printConnBrief();
    EV_DETAIL << msg->getName() << " timer expired\n";
    std::cout << msg->getFullPath() << " timer expired\n";

    // first do actions
    NDPEventCode event;

    if (msg == requestInternalTimer) {
        event = NDP_E_IGNORE;
        process_TIMEOUT_REQUEST_REXMIT();
//            sendRequest();   // based on my congestion control, I send requests after receiving  a packet not based on a timer
    }

    else if (msg == the2MSLTimer) {
        event = NDP_E_TIMEOUT_2MSL;
        process_TIMEOUT_2MSL();
    } else if (msg == connEstabTimer) {
        event = NDP_E_TIMEOUT_CONN_ESTAB;
        process_TIMEOUT_CONN_ESTAB();
    } else if (msg == finWait2Timer) {
        event = NDP_E_TIMEOUT_FIN_WAIT_2;
        process_TIMEOUT_FIN_WAIT_2();
    } else if (msg == synRexmitTimer) {
        event = NDP_E_IGNORE;
//        process_TIMEOUT_SYN_REXMIT(event);
    } else {
        event = NDP_E_IGNORE;
        ndpAlgorithm->processTimer(msg, event); // seeeee processTimer method in NDPBaseAlg.cc
    }

    // then state transitions
    return performStateTransition(event);
}



bool NDPConnection::processNDPSegment(Packet *packet, const Ptr<const NdpHeader>& ndpseg, L3Address segSrcAddr, L3Address segDestAddr)
{
    Enter_Method_Silent();

    printConnBrief();
    NDPEventCode event = process_RCV_SEGMENT(packet, ndpseg, segSrcAddr, segDestAddr);
    // then state transitions
    return performStateTransition(event);
}

 bool NDPConnection::processAppCommand(cMessage *msg) {
    Enter_Method_Silent();

    printConnBrief();

    NDPCommand *ndpCommand = check_and_cast_nullable<NDPCommand *>(msg->removeControlInfo());
    NDPEventCode event = preanalyseAppCommandEvent(msg->getKind());
    EV_INFO << "App command eventName: " << eventName(event) << "\n";
//     std::cout << "App command: " << eventName(event) << std::endl;
    switch (event) {
    case NDP_E_OPEN_ACTIVE:
        process_OPEN_ACTIVE(event, ndpCommand, msg);
        break;

    case NDP_E_OPEN_PASSIVE:
        process_OPEN_PASSIVE(event, ndpCommand, msg);
        break;
    case NDP_E_SETOPTION:
        process_OPTIONS(event, ndpCommand, msg);
        break;
    case NDP_E_CLOSE:
//        process_CLOSE(event, ndpCommand, msg);
        break;


    default:
        throw cRuntimeError(ndpMain, "wrong event code");
    }

    // then state transitions
    return performStateTransition(event);
}

NDPEventCode NDPConnection::preanalyseAppCommandEvent(int commandCode) {
    switch (commandCode) {
    case NDP_C_OPEN_ACTIVE:
        return NDP_E_OPEN_ACTIVE;

    case NDP_C_OPEN_PASSIVE:
        return NDP_E_OPEN_PASSIVE;

    case NDP_C_SEND:
        return NDP_E_SEND;

    case NDP_C_CLOSE:
        return NDP_E_CLOSE;

    default:
        throw cRuntimeError(ndpMain, "Unknown message kind in app command");
    }
}

bool NDPConnection::performStateTransition(const NDPEventCode& event) {
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

        case NDP_E_SEND:
            FSM_Goto(fsm, NDP_S_SYN_SENT);
            break;

        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
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
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_1);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_CONN_ESTAB:
            FSM_Goto(fsm, state->active ? NDP_S_CLOSED : NDP_S_LISTEN);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, state->active ? NDP_S_CLOSED : NDP_S_LISTEN);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSE_WAIT);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_SYN_SENT:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_CONN_ESTAB:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_SYN_ACK:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            break;

        case NDP_E_RCV_SYN:
            FSM_Goto(fsm, NDP_S_SYN_RCVD);
            break;

        default:
            break;
        }
        break;

    case NDP_S_ESTABLISHED:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_1);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSE_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_CLOSE_WAIT:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_LAST_ACK);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_LAST_ACK:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_FIN_WAIT_1:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSING);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_2);
            break;

        case NDP_E_RCV_FIN_ACK:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_FIN_WAIT_2:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_TIMEOUT_FIN_WAIT_2:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_CLOSING:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_TIME_WAIT:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_2MSL:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

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

void NDPConnection::stateEntered(int state, int oldState, NDPEventCode event) {
    // cancel timers
    switch (state) {
    case NDP_S_INIT:
        // we'll never get back to INIT
        break;

    case NDP_S_LISTEN:
        // we may get back to LISTEN from SYN_RCVD
        ASSERT(connEstabTimer && synRexmitTimer);
        cancelEvent(connEstabTimer);
        cancelEvent(synRexmitTimer);
        break;

    case NDP_S_SYN_RCVD:
    case NDP_S_SYN_SENT:
        break;

    case NDP_S_ESTABLISHED:
        // we're in ESTABLISHED, these timers are no longer needed
        delete cancelEvent(connEstabTimer);
        delete cancelEvent(synRexmitTimer);
        connEstabTimer = synRexmitTimer = nullptr;
        // NDP_I_ESTAB notification moved inside event processing
        break;

    case NDP_S_CLOSE_WAIT:
    case NDP_S_LAST_ACK:
    case NDP_S_FIN_WAIT_1:
    case NDP_S_FIN_WAIT_2:
    case NDP_S_CLOSING:
        if (state == NDP_S_CLOSE_WAIT)
            sendIndicationToApp(NDP_I_PEER_CLOSED);
        // whether connection setup succeeded (ESTABLISHED) or not (others),
        // cancel these timers
        if (connEstabTimer)
            cancelEvent(connEstabTimer);
        if (synRexmitTimer)
            cancelEvent(synRexmitTimer);
        break;

    case NDP_S_TIME_WAIT:
        sendIndicationToApp(NDP_I_CLOSED);
        break;

    case NDP_S_CLOSED:
        if (oldState != NDP_S_TIME_WAIT && event != NDP_E_ABORT)
            sendIndicationToApp(NDP_I_CLOSED);
        // all timers need to be cancelled
        if (the2MSLTimer)
            cancelEvent(the2MSLTimer);
        if (connEstabTimer)
            cancelEvent(connEstabTimer);
        if (finWait2Timer)
            cancelEvent(finWait2Timer);
        if (synRexmitTimer)
            cancelEvent(synRexmitTimer);
        ndpAlgorithm->connectionClosed();
        break;
    }
}

} // namespace NDP
} // namespace inet


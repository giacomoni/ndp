#include <string.h>

#include "inet/applications/common/SocketTag_m.h"

#include "Ndp.h"
#include "NdpAlgorithm.h"
#include "NdpConnection.h"
#include "NdpSendQueue.h"
#include "ndp_common/NdpHeader.h"
#include "ndp_common/NdpHeader.h"
#include "../contract/ndp/NdpCommand_m.h"
#include "../../application/ndpapp/GenericAppMsgNdp_m.h"
//Preprocessor directives
//  #define  ShowOut
#ifdef ShowOut
#define MY_COUT std::cout
#else
#define MY_COUT if(false) std::cout
#endif

namespace inet {
namespace ndp {

void NdpConnection::sendInitialWindow() {

    // TODO  we don't do any checking about the received request segment, e.g. check if it's  a request nothing else
    // fetch the next Packet from the encodingPackets list
    std::list<PacketsToSend>::iterator itt;
    if (state->IW > state->numPacketsToSend) {
        state->IW = state->numPacketsToSend;
    }
    for (int i = 1; i <= state->IW; i++) {
        std::tuple<Ptr<NdpHeader>, Packet*> packSeg = sendQueue->getNdpHeader();
        auto ndpseg = std::get<0>(packSeg);
        auto fp = std::get<1>(packSeg);
        if (ndpseg) {
            ndpseg->setIsDataPacket(true);
            ndpseg->setIsPullPacket(false);
            ndpseg->setIsHeader(false);
            ndpseg->setSynBit(true);  //  oooooooooooooooooooooooooo
            ndpseg->setAckBit(false);
            ndpseg->setNackBit(false);

            ndpseg->setNumPacketsToSend(state->numPacketsToSend);
            ndpseg->setPriorityValue(state->priorityValue);
            sendToIP(fp, ndpseg);
        }
    }
}

NdpEventCode NdpConnection::process_RCV_SEGMENT(Packet *packet,
        const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest) {
    EV_INFO << "Seg arrived: ";
    printSegmentBrief(packet, ndpseg);
    EV_DETAIL << "TCB: " << state->str() << "\n";
    NdpEventCode event;
    if (fsm.getState() == NDP_S_LISTEN) {
        event = processSegmentInListen(packet, ndpseg, src, dest);
        if (event == NDP_E_RCV_SYN) {
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            event = processSegment1stThru8th(packet, ndpseg);
        }
    } else {
        ndpMain->updateSockPair(this, dest, src, ndpseg->getDestPort(),
                ndpseg->getSrcPort());
        event = processSegment1stThru8th(packet, ndpseg);
    }
    delete packet;
    return event;
}

NdpEventCode NdpConnection::processSegment1stThru8th(Packet *packet,
        const Ptr<const NdpHeader> &ndpseg) {
    NdpEventCode event = NDP_E_IGNORE;
    // (S.1)   at the sender: NACK Arrived at the sender, then prepare the trimmed pkt for retranmission
    //        (not to transmit yet just make it to be the first one to transmit upon getting a pull pkt later)
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    // ££££££££££££££££££££££££ NACK Arrived at the sender £££££££££££££££££££ Tx
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    ASSERT(fsm.getState() == NDP_S_ESTABLISHED);
    if (state->isSender == true && ndpseg->getNackBit() == true) {
        sendQueue->nackArrived(ndpseg->getNackNo());
    }

    // (S.2)  at the sender:  ACK arrived, so free the acknowledged pkt from the buffer.
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    // ££££££££££££££££££££££££ ACK Arrived at the sender £££££££££££££££££££ Tx
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    if (state->isSender == true && ndpseg->getAckBit() == true) {
//        MY_COUT  << "  \n\n\n  £££££££££ Sender ££££££££ new  ACK arrived: ackNum = "  << ndpseg->getAckNo() << std::endl;
        sendQueue->ackArrived(ndpseg->getAckNo());
    }

    // (S.3)  at the sender: PULL pkt arrived, this pkt triggers either retransmission of trimmed pkt or sending a new data pkt.
// ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
// ££££££££££££££££££££££££ REQUEST Arrived at the sender £££££££££££££££
// ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    if (state->isSender == true && ndpseg->isPullPacket() == true) {
        int requestsGap = ndpseg->getPullSequenceNumber()
                - state->internal_request_id;
        EV_INFO << "\n\n\n\n\nPULL SEQ NUMB: "
                       << ndpseg->getPullSequenceNumber() << "\n";
        EV_INFO << "\nINTERNAL REQ NUMB: " << state->internal_request_id
                       << "\n";
        EV_INFO << "\nREQUESTGAP: " << requestsGap << "\n\n\n\n\n";
        if (requestsGap >= 1) {
            //  we send Packets  based on requestsGap value
            // if the requestsGap is smaller than 1 that means we received a delayed request which we need to  ignore
            // as we have assumed it was lost and we send extra Packets previously
            for (int i = 1; i <= requestsGap; i++) {
                ++state->internal_request_id;
                std::tuple<Ptr<NdpHeader>, Packet*> headPack =
                        sendQueue->getNdpHeader();
                const auto &ndpseg = std::get<0>(headPack);
                Packet *fp = std::get<1>(headPack);
                if (ndpseg) {
                    ndpseg->setIsDataPacket(true);
                    ndpseg->setIsPullPacket(false);
                    ndpseg->setIsHeader(false);
                    ndpseg->setAckBit(false);
                    ndpseg->setNackBit(false);
                    ndpseg->setSynBit(false);
                    ndpseg->setNumPacketsToSend(state->numPacketsToSend);
                    ndpseg->setPriorityValue(state->priorityValue);
                    sendToIP(fp, ndpseg);
                }
                //else{
                //    --state->internal_request_id;
                //}
            }
        } else if (requestsGap < 1) {
            EV_INFO << "Delayed pull arrived --> ignore it \n";
        }
    }
// (R.1)  at the receiver
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$  HEADER arrived   $$$$$$$$$$$$$$$$   Rx
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// header arrived at the receiver==> send new request with pacing (fixed pacing: MTU/1Gbps)
    if (ndpseg->isHeader() == true && ndpseg->isDataPacket() == false) { // 1 read, 2 write
        sendNackNdp(ndpseg->getDataSequenceNumber());
        ++state->numRcvTrimmedHeader;
        addRequestToPullsQueue();
        if (state->numberReceivedPackets == 0
                && state->connNotAddedYet == true) {
            getNDPMain()->requestCONNMap[getNDPMain()->connIndex] = this; // moh added
            state->connNotAddedYet = false;
            EV
                      << "sendFirstRequest sendFirstRequest sendFirstRequest sendFirstRequest .\n";
            ++getNDPMain()->connIndex;
            getNDPMain()->sendFirstRequest();
        }
    }

// (R.2) at the receiver
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$  data pkt arrived at the receiver  $$$$$$$$$$$$$$$$
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    if (state->isReceiver == true && ndpseg->isDataPacket() == true
            && ndpseg->isHeader() == false) {
        unsigned int arrivedPktSeqNo = ndpseg->getDataSequenceNumber();
        sendAckNdp(arrivedPktSeqNo);
        unsigned int seqNo = ndpseg->getDataSequenceNumber();
        ++state->numberReceivedPackets;
        unsigned int numberReceivedPackets = state->numberReceivedPackets;
        int initialSentPackets = state->IW;
        int wantedPackets = state->numPacketsToGet;
        // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // %%%%%%%%%%%%%%%%%%%%%%%% 1   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if (numberReceivedPackets > wantedPackets) {
            state->connFinished = true;
            getNDPMain()->allConnFinished();
            goto ll;
        } else {
            if (numberReceivedPackets <= (wantedPackets - initialSentPackets)
                    && state->connFinished == false) {
                addRequestToPullsQueue();
            }

            if (numberReceivedPackets == 1 && state->connNotAddedYet == true) {
                getNDPMain()->requestCONNMap[getNDPMain()->connIndex] = this; // moh added

                ++getNDPMain()->connIndex;
                state->connNotAddedYet = false;
                EV << "sendFirstRequest. \n";
                getNDPMain()->sendFirstRequest();
            }
            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            // %%%%%%%%%%%%%%%%%%%%%%%%%  4  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //  send any received Packet to the app
            Ptr<Chunk> msgRx;
            msgRx = packet->removeAll(); // each segment has just one packet
            if (state->connFinished == false) {
                // buffer the received Packet segment
                std::list<PacketsToSend>::iterator itR;  // received iterator
                itR = receivedPacketsList.begin();
                std::advance(itR, seqNo); // increment the iterator by esi
                // MOH: Send any received Packet to the app, just for now to test the Incast example, this shouldn't be the normal case
                Packet *newPacket = new Packet("ReceivedPacket", msgRx);
                PacketsToSend receivedPkts;
                receivedPkts.pktId = seqNo;
                receivedPkts.msg = newPacket;
                receivedPacketsList.push_back(receivedPkts);
                newPacket->setKind(NDP_I_DATA); // TBD currently we never send TCP_I_URGENT_DATA
                newPacket->addTag<SocketInd>()->setSocketId(socketId);
                sendToApp(newPacket);
            }
            // All the Packets have been received
            if (state->isfinalReceivedPrintedOut == false) {
                EV_INFO << "\n\n\n\n\nRECEIVED PACKETS: "
                               << numberReceivedPackets << "\n\n\n\n\n";
                EV_INFO << "\n\n\n\n\nWANTED PACKETS: " << wantedPackets
                               << "\n\n\n\n\n";
                if (numberReceivedPackets == wantedPackets
                        || state->connFinished == true) {
                    std::list<PacketsToSend>::iterator iter; // received iterator
                    iter = receivedPacketsList.begin();
                    int index = 0;
                    while (iter != receivedPacketsList.end()) {
                        iter++;
                    }

                    MY_COUT << " numRcvTrimmedHeader:    "
                            << state->numRcvTrimmedHeader << "\n\n";
                    EV_INFO << "\n\n\n\nCONNECTION FINISHED!" << "\n\n\n";
                    sendIndicationToApp(NDP_I_PEER_CLOSED); // this is ok if the sinkApp is used by one conn
                    state->isfinalReceivedPrintedOut = true;
                }
            }
        }
    }
    ll: return event;
}

void NdpConnection::addRequestToPullsQueue() {
    EV_INFO << "\n\n\n\n Add new request packet to pullsQueue.\n";

    ++state->request_id;
    char msgname[16];
    sprintf(msgname, "PULL-%d", state->request_id);
    Packet *ndppack = new Packet(msgname);

    const auto &ndpseg = makeShared<NdpHeader>();
    ndpseg->setIsDataPacket(false);
    ndpseg->setIsPullPacket(true);
    ndpseg->setIsHeader(false);
    ndpseg->setSynBit(false);
    ndpseg->setAckBit(false);
    ndpseg->setNackBit(false);
    ndpseg->setPriorityValue(state->priorityValue);
    ndpseg->setPullSequenceNumber(state->request_id);
    ndppack->insertAtFront(ndpseg);
    pullQueue.insert(ndppack);
    EV << "Adding new request to the pull queue -- pullsQueue length now = "
              << pullQueue.getLength() << "\n\n\n\n";
    bool napState = getNDPMain()->getNapState();
    if (napState == true) {
        getNDPMain()->requestTimer();
    }
}

void NdpConnection::sendRequestFromPullsQueue() {
    if (pullQueue.getLength() > 0) {
        Packet *fp = check_and_cast<Packet*>(pullQueue.pop());
        auto ndpseg = fp->removeAtFront<ndp::NdpHeader>();
        EV
                  << "a request has been popped from the Pull queue, the new queue length  = "
                  << pullQueue.getLength() << " \n\n";
        sendToIP(fp, ndpseg);
    }
}

int NdpConnection::getPullsQueueLength() {
    int len = pullQueue.getLength();
    return len;
}

bool NdpConnection::isConnFinished() {
    return state->connFinished;
}

int NdpConnection::getNumRcvdPackets() {
    return state->numberReceivedPackets;
}

void NdpConnection::setConnFinished() {
    MY_COUT << "allReceivedCloseAllMultiSourcingConnsmmmm \n\n\n\n";

    state->connFinished = true;
}

NdpEventCode NdpConnection::processSegmentInListen(Packet *packet,
        const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr,
        L3Address destAddr) {
    EV_DETAIL << "Processing segment in LISTEN\n";
    EV_INFO << " \n\n aaaMMM srcAddr" << srcAddr << " \n";
    EV_INFO << " \n\n aaaMMM destAddr" << destAddr << " \n";

    if (ndpseg->getSynBit()) {
        EV_DETAIL << "\n\n MMMM  SYN bit set: filling in foreign socket\n";
        ndpMain->updateSockPair(this, destAddr, srcAddr, ndpseg->getDestPort(),
                ndpseg->getSrcPort());
        // this is a receiver
        state->numPacketsToGet = ndpseg->getNumPacketsToSend();
        return NDP_E_RCV_SYN; // this will take us to SYN_RCVD
    }
    EV_WARN << "Unexpected segment: dropping it\n";
    return NDP_E_IGNORE;
}

void NdpConnection::process_TIMEOUT_CONN_ESTAB() {
    switch (fsm.getState()) {
    case NDP_S_SYN_RCVD:
    case NDP_S_SYN_SENT:
// Nothing to do here. TIMEOUT_CONN_ESTAB event will automatically
// take the connection to LISTEN or CLOSED, and cancel SYN-REXMIT timer.
        if (state->active) {
            // notify user if we're on the active side
            sendIndicationToApp(NDP_I_TIMED_OUT);
        }
        break;

    default:
// We should not receive this timeout in this state.
        throw cRuntimeError(ndpMain,
                "Internal error: received CONN_ESTAB timeout in state %s",
                stateName(fsm.getState()));
    }
}

void NdpConnection::process_TIMEOUT_2MSL() {
    //"
    // If the time-wait timeout expires on a connection delete the TCB,
    // enter the CLOSED state and return.
    //"
    switch (fsm.getState()) {
    case NDP_S_TIME_WAIT:
        break;

    default:
// We should not receive this timeout in this state.
        throw cRuntimeError(ndpMain,
                "Internal error: received time-wait (2MSL) timeout in state %s",
                stateName(fsm.getState()));
    }
}

void NdpConnection::process_TIMEOUT_FIN_WAIT_2() {
    switch (fsm.getState()) {
    case NDP_S_FIN_WAIT_2:
// Nothing to do here. The TIMEOUT_FIN_WAIT_2 event will automatically take
// the connection to CLOSED.
        break;

    default:
// We should not receive this timeout in this state.
        throw cRuntimeError(ndpMain,
                "Internal error: received FIN_WAIT_2 timeout in state %s",
                stateName(fsm.getState()));
    }
}

void NdpConnection::segmentArrivalWhileClosed(Packet *packet,
        const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr,
        L3Address destAddr) {
    EV_INFO << "Seg arrived: ";
    printSegmentBrief(packet, ndpseg);

    // This segment doesn't belong to any connection, so this object
    // must be a temp object created solely for the purpose of calling us

    ASSERT(state == nullptr);

    EV_INFO << "Segment doesn't belong to any existing connection\n";

    if (ndpseg->getRstBit()) {
        EV_DETAIL << "RST bit set: dropping segment\n";
        return;
    }

    if (!ndpseg->getAckBit()) {
        EV_DETAIL << "ACK bit not set: sending RST+ACK\n";
        uint32 ackNo = ndpseg->getDataSequenceNumber()
                + packet->getByteLength();
        sendRstAck(0, ackNo, destAddr, srcAddr, ndpseg->getDestPort(),
                ndpseg->getSrcPort());
    } else {
        EV_DETAIL << "ACK bit set: sending RST\n";
        sendRst(ndpseg->getAckNo(), destAddr, srcAddr, ndpseg->getDestPort(),
                ndpseg->getSrcPort());
    }
}

}    // namespace ndp

} // namespace inet


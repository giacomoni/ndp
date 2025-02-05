#include <string.h>

#include <inet/applications/common/SocketTag_m.h>
#include <inet/common/TimeTag_m.h>
#include "Ndp.h"
#include "NdpAlgorithm.h"
#include "NdpConnection.h"
#include "NdpSendQueue.h"
#include "ndp_common/NdpHeader.h"
#include "../contract/ndp/NdpCommand_m.h"
#include "../../application/ndpapp/GenericAppMsgNdp_m.h"

namespace inet {
namespace ndp {

void NdpConnection::sendInitialWindow()
{

    // TODO  we don't do any checking about the received request segment, e.g. check if it's  a request nothing else
    // fetch the next Packet from the encodingPackets list
    EV_TRACE << "NdpConnection::sendInitialWindow";
    std::list<PacketsToSend>::iterator itt;
    if (state->IW > state->numPacketsToSend) {
        state->IW = state->numPacketsToSend;
    }
    for (int i = 1; i <= state->IW; i++) {
        std::tuple<Ptr<NdpHeader>, Packet*> packSeg = sendQueue->getNdpHeader();
        auto ndpseg = std::get<0>(packSeg);
        auto fp = std::get<1>(packSeg);
        if (ndpseg) {
            EV_INFO << "Sending IW packet " << ndpseg->getDataSequenceNumber() << endl;
            ndpseg->setIsDataPacket(true);
            ndpseg->setIsPullPacket(false);
            ndpseg->setIsHeader(false);
            ndpseg->setSynBit(true);
            ndpseg->setAckBit(false);
            ndpseg->setNackBit(false);
            ndpseg->setNumPacketsToSend(state->numPacketsToSend);
            sendToIP(fp, ndpseg);
        }
    }
}

NdpEventCode NdpConnection::process_RCV_SEGMENT(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest)
{
    EV_TRACE << "NdpConnection::process_RCV_SEGMENT" << endl;
    //EV_INFO << "Seg arrived: ";
    //printSegmentBrief(packet, ndpseg);
    EV_DETAIL << "TCB: " << state->str() << "\n";
    NdpEventCode event;
    if (fsm.getState() == NDP_S_LISTEN) {
        EV_INFO << "NDP_S_LISTEN processing the segment in listen state" << endl;
        event = processSegmentInListen(packet, ndpseg, src, dest);
        if (event == NDP_E_RCV_SYN) {
            EV_INFO << "NDP_E_RCV_SYN received syn. Changing state to Established" << endl;
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            EV_INFO << "Processing Segment" << endl;
            event = processSegment1stThru8th(packet, ndpseg);
        }
    }
    else {
        ndpMain->updateSockPair(this, dest, src, ndpseg->getDestPort(), ndpseg->getSrcPort());
        event = processSegment1stThru8th(packet, ndpseg);
    }
    delete packet;
    return event;
}

NdpEventCode NdpConnection::processSegment1stThru8th(Packet *packet, const Ptr<const NdpHeader> &ndpseg)
{
    EV_TRACE << "NdpConnection::processSegment1stThru8th" << endl;
    EV_INFO << "_________________________________________" << endl;
    NdpEventCode event = NDP_E_IGNORE;
    // (S.1)   at the sender: NACK Arrived at the sender, then prepare the trimmed pkt for retranmission
    //        (not to transmit yet just make it to be the first one to transmit upon getting a pull pkt later)
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    // ££££££££££££££££££££££££ NACK Arrived at the sender £££££££££££££££££££ Tx
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    ASSERT(fsm.getState() == NDP_S_ESTABLISHED);
    if (ndpseg->getNackBit() == true) {
        EV_INFO << "Nack arrived at the sender - move data packet to front" << endl;
        sendQueue->nackArrived(ndpseg->getNackNo());
    }

    // (S.2)  at the sender:  ACK arrived, so free the acknowledged pkt from the buffer.
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    // ££££££££££££££££££££££££ ACK Arrived at the sender £££££££££££££££££££ Tx
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    if (ndpseg->getAckBit() == true) {
        EV_INFO << "Ack arrived at the sender - free ack buffer" << endl;
        sendQueue->ackArrived(ndpseg->getAckNo());
    }

    // (S.3)  at the sender: PULL pkt arrived, this pkt triggers either retransmission of trimmed pkt or sending a new data pkt.
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    // ££££££££££££££££££££££££ REQUEST Arrived at the sender £££££££££££££££
    // ££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££££
    if (ndpseg->isPullPacket() == true || ((ndpseg->getNackBit() == true) && (state->delayedNackNo > 0))) {
        int requestsGap = ndpseg->getPullSequenceNumber() - state->internal_request_id;
        EV_INFO << "Pull packet arrived at the sender - request gap " << requestsGap << endl;
        if(state->delayedNackNo > 0){
            requestsGap = 1;
            --state->delayedNackNo;
        }
        if (requestsGap >= 1) {
            //  we send Packets  based on requestsGap value
            // if the requestsGap is smaller than 1 that means we received a delayed request which we need to  ignore
            // as we have assumed it was lost and we send extra Packets previously
            for (int i = 1; i <= requestsGap; i++) {
                ++state->internal_request_id;
                std::tuple<Ptr<NdpHeader>, Packet*> headPack = sendQueue->getNdpHeader();
                const auto &ndpseg = std::get<0>(headPack);
                Packet *fp = std::get<1>(headPack);
                if (ndpseg) {
                    EV_INFO << "Sending data packet - " << ndpseg->getDataSequenceNumber() << endl;
                    ndpseg->setIsDataPacket(true);
                    ndpseg->setIsPullPacket(false);
                    ndpseg->setIsHeader(false);
                    ndpseg->setAckBit(false);
                    ndpseg->setNackBit(false);
                    ndpseg->setSynBit(false);
                    ndpseg->setNumPacketsToSend(state->numPacketsToSend);
                    sendToIP(fp, ndpseg);
                }
                else {
                    EV_WARN << "No Ndp header within the send queue!" << endl;
                    ++state->delayedNackNo;
                    --state->internal_request_id;
                    //EV_INFO << "No Ndp header within the send queue!" << endl;
                    //--state->internal_request_id;
                    //state->internal_request_id = state->internal_request_id - requestsGap;
                    //--state->request_id;

                }
            }
        }
        else if (requestsGap < 1) {
            EV_INFO << "Delayed pull arrived --> ignore it" << endl;
        }
    }
    // (R.1)  at the receiver
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$  HEADER arrived   $$$$$$$$$$$$$$$$   Rx
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // header arrived at the receiver==> send new request with pacing (fixed pacing: MTU/1Gbps)
    if (ndpseg->isHeader() == true && ndpseg->isDataPacket() == false) { // 1 read, 2 write
        EV_INFO << "Header arrived at the receiver" << endl;
        sendNackNdp(ndpseg->getDataSequenceNumber());
        ++state->numRcvTrimmedHeader;
        addRequestToPullsQueue();
        if (state->numberReceivedPackets == 0 && state->connNotAddedYet == true) {
            getNDPMain()->requestCONNMap[getNDPMain()->connIndex] = this; // moh added
            state->connNotAddedYet = false;
            ++getNDPMain()->connIndex;
            EV_INFO << "sending first request" << endl;
            getNDPMain()->sendFirstRequest();
        }
    }

    // (R.2) at the receiver
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$  data pkt arrived at the receiver  $$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    if (ndpseg->isDataPacket() == true && ndpseg->isHeader() == false) {
        EV_INFO << "Data packet arrived at the receiver - seq num " << ndpseg->getDataSequenceNumber() << endl;
        unsigned int arrivedPktSeqNo = ndpseg->getDataSequenceNumber();
        sendAckNdp(arrivedPktSeqNo);
        unsigned int seqNo = ndpseg->getDataSequenceNumber();
        ++state->numberReceivedPackets;
        int numberReceivedPackets = state->numberReceivedPackets;
        int initialSentPackets = state->IW;
        int wantedPackets = state->numPacketsToGet;
        // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // %%%%%%%%%%%%%%%%%%%%%%%% 1   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        if (numberReceivedPackets > wantedPackets) {
            EV_INFO << "All packets received - finish all connections!" << endl;
            state->connFinished = true;
            getNDPMain()->allConnFinished();
            goto ll;
        }
        else {
            if (numberReceivedPackets <= (wantedPackets - initialSentPackets) && state->connFinished == false) {
                EV_INFO << "Adding pull request to pull queue!" << endl;
                addRequestToPullsQueue();
            }

            if (numberReceivedPackets == 1 && state->connNotAddedYet == true) {
                getNDPMain()->requestCONNMap[getNDPMain()->connIndex] = this; // moh added
                ++getNDPMain()->connIndex;
                state->connNotAddedYet = false;
                EV << "Requesting Pull Timer" << endl;
                getNDPMain()->sendFirstRequest();
            }
            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            // %%%%%%%%%%%%%%%%%%%%%%%%%  4  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            //  send any received Packet to the app
            auto tag = ndpseg->getTag(0);
            const CreationTimeTag *timeTag = dynamic_cast<const CreationTimeTag *>(tag);
            //packet->setFrontOffset(B(0));
            //packet->setBackOffset(B(1500));
            Ptr<Chunk> msgRx;
            msgRx = packet->removeAll();
            if (state->connFinished == false) {
                EV_INFO << "Sending Data Packet to Application" << endl;
                // buffer the received Packet segment
                std::list<PacketsToSend>::iterator itR;  // received iterator
                itR = receivedPacketsList.begin();
                std::advance(itR, seqNo); // increment the iterator by esi
                // MOH: Send any received Packet to the app, just for now to test the Incast example, this shouldn't be the normal case
                //Packet *newPacket = packet->dup();
                std::string packetName = "DATAPKT-" + std::to_string(seqNo);
                Packet *newPacket = new Packet(packetName.c_str(), msgRx);
                newPacket->addTag<CreationTimeTag>()->setCreationTime(timeTag->getCreationTime());
                PacketsToSend receivedPkts;
                receivedPkts.pktId = seqNo;
                receivedPkts.msg = newPacket;
                receivedPacketsList.push_back(receivedPkts);
                newPacket->setKind(NDP_I_DATA); // TBD currently we never send NDP_I_URGENT_DATA
                newPacket->addTag<SocketInd>()->setSocketId(socketId);
                EV_INFO << "Sending to App packet: " << newPacket->str() << endl;
                sendToApp(newPacket);
            }
            // All the Packets have been received
            if (state->isfinalReceivedPrintedOut == false) {
                EV_INFO << "Total Received Packets: " << numberReceivedPackets << endl;
                EV_INFO << "Total Wanted Packets: " << wantedPackets << endl;
                if (numberReceivedPackets == wantedPackets || state->connFinished == true) {
                    std::list<PacketsToSend>::iterator iter; // received iterator
                    iter = receivedPacketsList.begin();
                    while (iter != receivedPacketsList.end()) {
                        iter++;
                    }
                    EV_INFO << " numRcvTrimmedHeader:    " << state->numRcvTrimmedHeader << endl;
                    EV_INFO << "CONNECTION FINISHED!" << endl;
                    sendIndicationToApp(NDP_I_PEER_CLOSED); // this is ok if the sinkApp is used by one conn
                    state->isfinalReceivedPrintedOut = true;
                }
            }
        }
    }
    ll: return event;
}

void NdpConnection::addRequestToPullsQueue()
{
    EV_TRACE << "NdpConnection::addRequestToPullsQueue" << endl;
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
    ndpseg->setPullSequenceNumber(state->request_id);
    ndppack->insertAtFront(ndpseg);
    pullQueue.insert(ndppack);
    EV_INFO << "Adding new request to the pull queue -- pullsQueue length now = " << pullQueue.getLength() << endl;
    bool napState = getNDPMain()->getNapState();
    if (napState == true) {
        EV_INFO << "Requesting Pull Timer (12 microseconds)" << endl;
        getNDPMain()->requestTimer();
    }
}

void NdpConnection::sendRequestFromPullsQueue()
{
    EV_TRACE << "NdpConnection::sendRequestFromPullsQueue" << endl;
    if (pullQueue.getLength() > 0) {
        Packet *fp = check_and_cast<Packet*>(pullQueue.pop());
        auto ndpseg = fp->removeAtFront<ndp::NdpHeader>();
        EV << "a request has been popped from the Pull queue, the new queue length  = " << pullQueue.getLength() << " \n\n";
        sendToIP(fp, ndpseg);
    }
}

int NdpConnection::getPullsQueueLength()
{
    int len = pullQueue.getLength();
    return len;
}

bool NdpConnection::isConnFinished()
{
    return state->connFinished;
}

int NdpConnection::getNumRcvdPackets()
{
    return state->numberReceivedPackets;
}

void NdpConnection::setConnFinished()
{
    state->connFinished = true;
}

NdpEventCode NdpConnection::processSegmentInListen(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr, L3Address destAddr)
{
    EV_DETAIL << "Processing segment in LISTEN" << endl;

    if (ndpseg->getSynBit()) {
        EV_DETAIL << "SYN bit set: filling in foreign socket" << endl;
        ndpMain->updateSockPair(this, destAddr, srcAddr, ndpseg->getDestPort(), ndpseg->getSrcPort());
        // this is a receiver
        state->numPacketsToGet = ndpseg->getNumPacketsToSend();
        return NDP_E_RCV_SYN; // this will take us to SYN_RCVD
    }
    EV_WARN << "Unexpected segment: dropping it" << endl;
    return NDP_E_IGNORE;
}

void NdpConnection::segmentArrivalWhileClosed(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr, L3Address destAddr)
{
    EV_TRACE << "NdpConnection::segmentArrivalWhileClosed" << endl;
    EV_INFO << "Seg arrived: " << endl;
    printSegmentBrief(packet, ndpseg);
    // This segment doesn't belong to any connection, so this object
    // must be a temp object created solely for the purpose of calling us
    ASSERT(state == nullptr);
    EV_INFO << "Segment doesn't belong to any existing connection" << endl;
    EV_FATAL << "NdpConnection::segmentArrivalWhileClosed should not be called!";
}

}    // namespace ndp

} // namespace inet


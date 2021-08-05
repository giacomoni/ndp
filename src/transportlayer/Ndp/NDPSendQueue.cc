


#include "NDPSendQueue.h"

namespace inet {

namespace ndp {

Register_Class(NDPSendQueue);

NDPSendQueue::NDPSendQueue()
{
}

NDPSendQueue::~NDPSendQueue()
{
}

void NDPSendQueue::init(unsigned int numPacketsToSend , unsigned int mss)
{
    dataToSendQueue.clear();          // clear dataBuffer
    sentDataQueue.clear();
    // filling the dataToSendQueue queue with (random data) packets based on the numPacketsToSend value that the application passes
    // TODO: I would update this to get  bytes stream from the application then packetise this data at the transport layer
     EV_INFO << "\n\n\n\n\n\n\n\n\n generateSymbolsList "     << "\n";
    char msgname[16];
    for (int i = 1; i <= numPacketsToSend; i++) {
        sprintf(msgname, "DATAPKT-%d", i);
        GenericAppMsgNdp *datamsg = new GenericAppMsgNdp(msgname); // state->iss
        Payload payload;
        payload.sequenceNo = i;
        payload.msg = PK(datamsg);
        payload.msg->setByteLength(mss);
        dataToSendQueue.push(payload);
    }
}

std::string NDPSendQueue::str() const
{
    std::stringstream out;
    out << "[" << begin << ".." << end << ")" << dataBuffer;
    return out.str();
}

void NDPSendQueue::enqueueAppData(Packet *msg)
{
    //tcpEV << "sendQ: " << str() << " enqueueAppData(bytes=" << msg->getByteLength() << ")\n";
    dataBuffer.push(msg->peekDataAt(B(0), msg->getDataLength()));
    end += msg->getByteLength();
    if (seqLess(end, begin))
        throw cRuntimeError("Send queue is full");
    delete msg;
}

uint32 NDPSendQueue::getBufferStartSeq()
{
    return begin;
}

uint32 NDPSendQueue::getBufferEndSeq()
{
    return end;
}

NdpHeader *NDPSendQueue::getNdpSegment()
{

//    ASSERT(seqLE(begin, fromSeq) && seqLE(fromSeq + numBytes, end));
    if (dataToSendQueue.size() > 0) {
        NdpHeader *ndpseg = new NdpHeader(nullptr);
        ndpseg->setPayloadLength(1500);

        std::list<Payload>::iterator iter = dataToSendQueue.begin();
//        auto iter = dataToSendQueue.begin();
        const char *payloadName = iter->msg->getName();
        ndpseg->addPayloadMessage(iter->msg->dup(), 1);
        ndpseg->setName(payloadName);
        ndpseg->setDataSequenceNumber(iter->sequenceNo);

//        ndpseg->isLastPktToSend(isLastSymbolToSend);

        EV_INFO << "  \n\n\n\n\n\n getNewNDP segment ........." << iter->sequenceNo << " \n\n\n";
        removeFromDataQueueToSentQueue(iter);

        return ndpseg;
    } else {
        EV_INFO << " Nothing to send !! \n";
        return nullptr;
    }
}

void NDPSendQueue::removeFromDataQueueToSentQueue( std::list<Payload>::iterator iter) {
    Payload payload;
    payload.sequenceNo = iter->sequenceNo;
    payload.msg = iter->msg;
    payload.msg->setByteLength(1500);
    sentDataQueue.push_back(payload);

//    delete iter->msg;
    dataToSendQueue.erase(iter);
}


void NDPSendQueue::moveFrontDataQueue( std::list<Payload>::iterator iter) {
    Payload payload;
    payload.sequenceNo = iter->sequenceNo;
    payload.msg = iter->msg;
    payload.msg->setByteLength(1500);
    dataToSendQueue.push_front(payload);

//    delete iter->msg;
    sentDataQueue.erase(iter);
}

void NDPSendQueue::ackArrivedFreeBuffer(unsigned int ackNum){
    EV_INFO << " ackArrivedFreeBuffer: " <<  ackNum << "\n";


    auto iter = sentDataQueue.begin();
    while (iter != sentDataQueue.end()) {
        if (iter->sequenceNo == ackNum) {
            EV_INFO << "ackArrivedFreeBuffer erase pktId: " << iter->sequenceNo << "\n\n";
//            delete iter->msg;
            sentDataQueue.erase(iter);
//            printAllInfoInQueue();
            break;
        } else {
//        MY_COUT << " SQN: " << iter->pktId << " msgName "  << iter->msg->getFullName() << "\n";
            iter++;
        }
    }
    printAllInfoInQueue();
}

void NDPSendQueue::nackArrivedMoveFront(unsigned int nackNum){

    EV_INFO << " nack arrived: " <<  nackNum << "\n";

    auto iter = sentDataQueue.begin();
    while (iter != sentDataQueue.end()) {
        if (iter->sequenceNo == nackNum) {
            moveFrontDataQueue(iter);
            break;
        } else {
            iter++;
        }
    }
    printAllInfoInQueue();
}

Packet *NDPSendQueue::createSegmentWithBytes(uint32 fromSeq, ulong numBytes)
{
    //tcpEV << "sendQ: " << str() << " createSeg(seq=" << fromSeq << " len=" << numBytes << ")\n";

    char msgname[32];
    sprintf(msgname, "ndpseg(l=%lu)", numBytes);

    Packet *packet = new Packet(msgname);
    const auto& payload = dataToSendQueue.peekAt(B(fromSeq - begin), B(numBytes));   //get data from buffer
    //std::cout << "#: " << getSimulation()->getEventNumber() << ", T: " << simTime() << ", SENDER: " << conn->getTcpMain()->getParentModule()->getFullName() << ", DATA: " << payload << std::endl;
    packet->insertAtBack(payload);
    return packet;
}

void NDPSendQueue::discardUpTo(uint32 seqNum)
{
    //tcpEV << "sendQ: " << str() << " discardUpTo(seq=" << seqNum << ")\n";

    if (seqNum != begin) {
        dataToSendQueue.pop(B(seqNum - begin));
        begin = seqNum;
    }
}

} // namespace tcp

} // namespace inet





#include "NDPSendQueue.h"
#include "inet/common/TimeTag_m.h"
namespace inet {

namespace ndp {

Register_Class(NDPSendQueue);

NDPSendQueue::NDPSendQueue()
{
}

NDPSendQueue::~NDPSendQueue()
{
    dataToSendQueue.clear();
    sentDataQueue.clear();
}

void NDPSendQueue::init(unsigned int numPacketsToSend , B mss)
{
    //dataToSendQueue.empty();
    dataToSendQueue.clear();          // clear dataBuffer
    sentDataQueue.clear();
    // filling the dataToSendQueue queue with (random data) packets based on the numPacketsToSend value that the application passes
    // TODO: I would update this to get  bytes stream from the application then packetise this data at the transport layer
     EV_INFO << "\n\n\n\n\n\n\n\n\n generateSymbolsList "     << "\n";
    char msgname[16];
    for (int i = 1; i <= numPacketsToSend; i++) {
        sprintf(msgname, "DATAPKT-%d", i);
//        auto packet = new Packet("DATAPKT-%d", i);
//        GenericAppMsgNdp *datamsg = new GenericAppMsgNdp(msgname); // state->iss
//        Payload payload;
//        payload.sequenceNo = i;
//        payload.msg = PK(datamsg);
//        payload.msg->setByteLength(mss);
//        dataToSendQueue.push(payload);

        const auto& payload = makeShared<GenericAppMsgNdp>(); // state->iss
        std::string packetName = "DATAPKT-"+std::to_string(i);
        Packet *packet = new Packet(packetName.c_str());
        payload->setSequenceNumber(i);
        payload->setChunkLength(mss);
        payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
        packet->insertAtBack(payload);
        //auto packet = new Packet(packetName.c_str(), check_and_cast<Ptr <const Chunk>>(datamsg));
        //auto packet = new Packet(packetName.c_str(), 0); //FIX
        //auto header = makeShared<NdpHeader>();
        //header->setDataSequenceNumber(i);
        //packet->insertAtFront(header); // insert header into segment
        //dataToSendQueue.push((packet->peekDataAt(B(0), packet->getDataLength())));
        dataToSendQueue.insert(packet);
        EV_INFO << "\n\n SQN: " << i << " msgName " << packet->str() << "\n";
    }
}

std::string NDPSendQueue::str() const
{
    std::stringstream out;
    out << "[" << begin << ".." << end << ")" << dataToSendQueue;
    return out.str();
}

void NDPSendQueue::enqueueAppData(Packet *msg)
{
    //tcpEV << "sendQ: " << str() << " enqueueAppData(bytes=" << msg->getByteLength() << ")\n";
    //dataToSendQueue.push(msg->peekDataAt(B(0), msg->getDataLength()));
    dataToSendQueue.insert(msg);
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

const std::tuple<Ptr<NdpHeader>, Packet*> NDPSendQueue::getNdpHeader()
{ //TODO

//    ASSERT(seqLE(begin, fromSeq) && seqLE(fromSeq + numBytes, end));
    EV_INFO << "\n\n\nDATA QUEUE LENGTH :"<< dataToSendQueue.getLength() << std::endl;
    if (dataToSendQueue.getLength() > 0) {

        //NdpHeader *ndpseg = new NdpHeader(nullptr);
        const auto& ndpseg = makeShared<NdpHeader>();
        //dataToSendQueue.begin();
        //char msgname[32];
        //sprintf(msgname, "ndpseg(l=%lu)", numBytes);
        //Packet *packet = new Packet(msgname);
        //packet->setByteLength(1500);
        //ndpseg->setPayloadLength(1500);

        //std::list<Payload>::iterator iter = dataToSendQueue.begin();
//        auto iter = dataToSendQueue.begin();
        //const auto& payload = dataToSendQueue.peekAt(B(fromSeq - begin), B(numBytes));
        //const char *payloadName = iter->msg->getName();
        //packet->insertAtBack(payload);
        //ndpseg->addPayloadMessage(iter->msg->dup(), 1);

        //ndpseg->setDataSequenceNumber(iter->sequenceNo); PLEASE FIX
        //auto& appmsg = dataToSendQueue.pop<GenericAppMsgNdp>(b(-1), Chunk::PF_ALLOW_NULLPTR);
        Packet* queuePacket = check_and_cast<Packet *>(dataToSendQueue.pop());
        auto& appmsg = queuePacket->peekData<GenericAppMsgNdp>();
        EV_INFO << "\n\n\nDATA SEQUENCE NUMBER :"<< appmsg->getSequenceNumber() << std::endl;
        //const auto& appmsg = prevPacket->peekData<GenericAppMsgNdp>;
        //Packet *packet = createSegmentWithBytes(0, 1500);
        std::string packetName = "DATAPKT-"+std::to_string(appmsg->getSequenceNumber());
        Packet *packet = new Packet(packetName.c_str());
        //packet->insertAtBack(appmsg->getContent());
        //packet->setByteLength(1500);e
//        ndpseg->isLastPktToSend(isLastSymbolToSend);
        packet->insertAtBack(appmsg);
        ndpseg->setDataSequenceNumber(appmsg->getSequenceNumber());
        //EV_INFO << "  \n\n\n\n\n\n getNewNDP segment ........." << iter->sequenceNo << " \n\n\n";
        //removeFromDataQueueToSentQueue(iter);
        //discardUpTo(1500);

        //packet->insertAtFront(ndpseg);
        Packet * dupPacket = packet->dup();
        //sentDataQueue.push(dupPacket->peekDataAt(B(0), dupPacket->getDataLength()));
        sentDataQueue.insert(dupPacket);
        delete queuePacket;
        return std::make_tuple(ndpseg,packet);
    } else {
        EV_INFO << " Nothing to send !! \n";
        return std::make_tuple(nullptr,nullptr);
    }
}

//void NDPSendQueue::removeFromDataQueueToSentQueue( std::list<Chunk>::iterator iter) {
//    //Payload payload;
//    //payload.sequenceNo = iter->sequenceNo;
//    //payload.msg = iter->msg;
//    //payload.msg->setByteLength(1500);
//    //sentDataQueue.push_back(packet);
//    Packet *packet = new Packet(iter->msg);
//    auto header = makeShared<NdpHeader>();
//    header->setDataSequenceNumber(iter->sequenceNo);
//    packet->setByteLength(1500);
//    packet->insertAtFront(header); // insert header into segment
//    sentDataQueue.push(packet->peekDataAt(B(0), packet->getDataLength()));
////    delete iter->msg;
//    dataToSendQueue.
//    //dataToSendQueue.erase(iter);
//}


void NDPSendQueue::moveFrontDataQueue(Chunk::Iterator iter) {
//    Payload payload;
//    payload.sequenceNo = iter->sequenceNo;
//    payload.msg = iter->msg;
//    payload.msg->setByteLength(1500);
//
//    dataToSendQueue.push_front(iter->getPosition(B(0), msg->getDataLength()));
//
//    delete iter->msg;
//    sentDataQueue.erase(iter);
//    Packet *packet = createSegmentWithBytes(begin, 1500);
//    packet->setByteLength(1500);

}

void NDPSendQueue::ackArrivedFreeBuffer(Packet* packet){
    EV_INFO << "\n ackArrivedFreeBuffer: " <<  packet->str() << "\n";
    sentDataQueue.remove(packet);

//    delete packet;
//    for(int i = 0; i < sentDataQueue.length(); i++){
//        Packet* packet = check_and_cast<Packet *>(sentDataQueue.get(i));
//        auto ndpseg = packet->removeAtFront<ndp::NdpHeader>();
//        if(ndpseg->getDataSequenceNumber() == ackNum){
//            sentDataQueue.remove(sentDataQueue.get(i));
//            //delete ndpseg;
//            delete packet;
//        }
//    }
    //printAllInfoInQueue();
}

void NDPSendQueue::nackArrivedMoveFront(Packet* packet, unsigned int nackNum){
    sentDataQueue.remove(packet);
    //Packet *newPacket = packet->dup();
    std::string packetName = "NACK DATAPKT-"+std::to_string(nackNum);
    const auto& payload = makeShared<GenericAppMsgNdp>();
    Packet *newPacket = new Packet(packetName.c_str());
    payload->setSequenceNumber(nackNum);
    payload->setChunkLength(B(1500));
    newPacket->insertAtBack(payload);
    if(dataToSendQueue.getLength() > 0){
        dataToSendQueue.insertBefore(dataToSendQueue.front(), newPacket);
    }
    else{
        dataToSendQueue.insert(newPacket);
    }
    //dataToSendQueue.insert(newPacket);
    //const auto& payload = makeShared<GenericAppMsgNdp>(); // state->iss
    //std::string packetName = "DATAPKT-"+std::to_string(nackNum);
    //Packet *packet = new Packet(packetName.c_str());
    //payload->setSequenceNumber(nackNum);
    //payload->setChunkLength(1500);
    //payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
    //packet->insertAtBack(payload);
//
//    EV_INFO << " nack arrived: " <<  nackNum << "\n";
//
//    auto iter = sentDataQueue.begin();
//    while (iter != sentDataQueue.end()) {
//        if (iter->sequenceNo == nackNum) {
//            moveFrontDataQueue(iter);
//            break;
//        } else {
//            iter++;
//        }
//    }
//    printAllInfoInQueue();
}

//Packet *NDPSendQueue::createSegmentWithBytes(uint32 fromSeq, ulong numBytes)
//{
//    //tcpEV << "sendQ: " << str() << " createSeg(seq=" << fromSeq << " len=" << numBytes << ")\n";
//
//    char msgname[32];
//    sprintf(msgname, "ndpseg(l=%lu)", numBytes);
//
//    Packet *packet = new Packet(msgname);
//    const auto& payload = dataToSendQueue.peekAt(B(fromSeq - begin), B(numBytes));   //get data from buffer
//    //std::cout << "#: " << getSimulation()->getEventNumber() << ", T: " << simTime() << ", SENDER: " << conn->getTcpMain()->getParentModule()->getFullName() << ", DATA: " << payload << std::endl;
//    packet->insertAtBack(payload);
//    return packet;
//}
//
//void NDPSendQueue::discardUpTo(uint32 seqNum)
//{
//    //tcpEV << "sendQ: " << str() << " discardUpTo(seq=" << seqNum << ")\n";
//
//    if (seqNum != begin) {
//        dataToSendQueue.pop(B(seqNum - begin));
//        begin = seqNum;
//    }
//}

} // namespace tcp

} // namespace inet


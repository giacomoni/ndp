#include <inet/common/TimeTag_m.h>

#include "NdpSendQueue.h"
namespace inet {

namespace ndp {

Register_Class(NdpSendQueue);

NdpSendQueue::NdpSendQueue()
{
}

NdpSendQueue::~NdpSendQueue()
{
    dataToSendQueue.clear();
    auto iter = sentDataQueue.begin();
    while (iter != sentDataQueue.end()) {
        delete iter->second;
        iter++;
    }
    sentDataQueue.clear();
}

void NdpSendQueue::init(int numPacketsToSend, B mss)
{
    // filling the dataToSendQueue queue with (random data) packets based on the numPacketsToSend value that the application passes
    // TODO: I would update this to get  bytes stream from the application then packetise this data at the transport layer
    EV_TRACE << "NdpSendQueue::init" << endl;
    EV_INFO << "Filling Data to Send Queue with "<< numPacketsToSend << " packets!" << endl;
    for (int i = 1; i <= numPacketsToSend; i++) {
        const auto &payload = makeShared<GenericAppMsgNdp>();
        std::string packetName = "DATAPKT-" + std::to_string(i);
        Packet *packet = new Packet(packetName.c_str());
        payload->setSequenceNumber(i);
        payload->setChunkLength(mss);
        packet->insertAtBack(payload);
        dataToSendQueue.insert(packet);
    }
}

std::string NdpSendQueue::str() const
{
    std::stringstream out;
    out << "[" << begin << ".." << end << ")" << dataToSendQueue;
    return out.str();
}

uint32 NdpSendQueue::getBufferStartSeq()
{
    return begin;
}

uint32 NdpSendQueue::getBufferEndSeq()
{
    return end;
}

const std::tuple<Ptr<NdpHeader>, Packet*> NdpSendQueue::getNdpHeader()
{
    EV_TRACE << "NdpSendQueue::getNdpHeader()" << endl;
    EV_INFO << "Data Queue Length :" << dataToSendQueue.getLength() << std::endl;
    if (dataToSendQueue.getLength() > 0) {
        const auto &ndpseg = makeShared<NdpHeader>();
        Packet *queuePacket = check_and_cast<Packet*>(dataToSendQueue.pop());
        auto &appmsg = queuePacket->removeAtFront<GenericAppMsgNdp>();
        appmsg->setChunkLength(B(1453));
        EV_INFO << "Data Sequence Number :" << appmsg->getSequenceNumber() << std::endl;
        std::string packetName = "DATAPKT-" + std::to_string(appmsg->getSequenceNumber());
        Packet *packet = new Packet(packetName.c_str());
        packet->insertAtBack(appmsg);
        ndpseg->setDataSequenceNumber(appmsg->getSequenceNumber());
        Packet *dupPacket = packet->dup();
        //sentDataQueue.insert(dupPacket);
        sentDataQueue[appmsg->getSequenceNumber()] = dupPacket;
        delete queuePacket;
        ndpseg->addTag<CreationTimeTag>()->setCreationTime(simTime());
        return std::make_tuple(ndpseg, packet);
    }
    else {
        EV_WARN << " Nothing to send at NdpSendQueue!" << endl;
        return std::make_tuple(nullptr, nullptr);
    }
}

void NdpSendQueue::moveFrontDataQueue(unsigned int sequenceNumber)
{
    std::string packetName = "NACK DATAPKT-" + std::to_string(sequenceNumber);
    const auto &payload = makeShared<GenericAppMsgNdp>();
    Packet *newPacket = new Packet(packetName.c_str());
    payload->setSequenceNumber(sequenceNumber);
    payload->setChunkLength(B(1453));
    newPacket->insertAtBack(payload);
    if (dataToSendQueue.getLength() > 0) {
        dataToSendQueue.insertBefore(dataToSendQueue.front(), newPacket);
    }
    else {
        dataToSendQueue.insert(newPacket);
    }

}

void NdpSendQueue::ackArrived(unsigned int ackNum)
{
    EV_INFO << "NdpSendQueue::ackArrived: " << ackNum << endl;
//    for (int i = 0; i <= sentDataQueue.getLength(); i++) {
//        Packet *packet = check_and_cast<Packet*>(sentDataQueue.get(i));
//        auto &appmsg = packet->peekData<GenericAppMsgNdp>();
//        if (appmsg->getSequenceNumber() == ackNum) {
//            sentDataQueue.remove(sentDataQueue.get(i));
//            delete packet;
//            break;
//        }
//    }
    Packet *packet = check_and_cast<Packet*>(sentDataQueue[ackNum]);
    //auto &appmsg = packet->peekData<GenericAppMsgNdp>();
   // if (appmsg->getSequenceNumber() == ackNum) {
    sentDataQueue.erase(ackNum);
    delete packet;
    //}
}

void NdpSendQueue::nackArrived(unsigned int nackNum)
{
//    bool found = false;
//    for (int i = 0; i <= sentDataQueue.getLength(); i++) {
//        Packet *packet = check_and_cast<Packet*>(sentDataQueue.get(i));
//        auto &appmsg = packet->peekData<GenericAppMsgNdp>();
//        if (appmsg->getSequenceNumber() == nackNum) {
//            moveFrontDataQueue(nackNum);
//            sentDataQueue.remove(packet);
//            delete packet;
//            found = true;
//            break;
//        }
//    }
//    ASSERT(found == true);
    Packet *packet = check_and_cast<Packet*>(sentDataQueue[nackNum]);
    //auto &appmsg = packet->peekData<GenericAppMsgNdp>();
    //if (appmsg->getSequenceNumber() == nackNum) {
    moveFrontDataQueue(nackNum);
    sentDataQueue.erase(nackNum);
    delete packet;
    //}
}
}            // namespace ndp

} // namespace inet


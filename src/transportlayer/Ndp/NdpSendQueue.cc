#include "inet/common/TimeTag_m.h"

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
    sentDataQueue.clear();
}

void NdpSendQueue::init(unsigned int numPacketsToSend, B mss)
{
    // filling the dataToSendQueue queue with (random data) packets based on the numPacketsToSend value that the application passes
    // TODO: I would update this to get  bytes stream from the application then packetise this data at the transport layer
    EV_INFO << "\ngenerateSymbolsList " << "\n";
    char msgname[16];
    for (int i = 1; i <= numPacketsToSend; i++) {
        const auto &payload = makeShared<GenericAppMsgNdp>();
        std::string packetName = "DATAPKT-" + std::to_string(i);
        Packet *packet = new Packet(packetName.c_str());
        payload->setSequenceNumber(i);
        payload->setChunkLength(mss);
        payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
        packet->insertAtBack(payload);
        dataToSendQueue.insert(packet);
        EV_INFO << "\nSQN: " << i << " msgName " << packet->str() << "\n";
    }
}

std::string NdpSendQueue::str() const
{
    std::stringstream out;
    out << "[" << begin << ".." << end << ")" << dataToSendQueue;
    return out.str();
}

void NdpSendQueue::enqueueAppData(Packet *msg)
{
    auto &appmsg = msg->removeAtFront<GenericAppMsgNdp>();
    appmsg->setSequenceNumber(0);
    msg->insertAtFront(appmsg);
    dataToSendQueue.insert(msg);
    end += msg->getByteLength();
    if (seqLess(end, begin))
        throw cRuntimeError("Send queue is full");
    delete msg;
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
{ //TODO
    EV_INFO << "\n\n\nDATA QUEUE LENGTH :" << dataToSendQueue.getLength() << std::endl;
    if (dataToSendQueue.getLength() > 0) {
        const auto &ndpseg = makeShared<NdpHeader>();
        Packet *queuePacket = check_and_cast<Packet*>(dataToSendQueue.pop());
        auto &appmsg = queuePacket->removeAtFront<GenericAppMsgNdp>();
        appmsg->setChunkLength(B(1453));
        EV_INFO << "\nData Sequence Number :" << appmsg->getSequenceNumber() << std::endl;
        std::string packetName = "DATAPKT-" + std::to_string(appmsg->getSequenceNumber());
        Packet *packet = new Packet(packetName.c_str());
        packet->insertAtBack(appmsg);
        ndpseg->setDataSequenceNumber(appmsg->getSequenceNumber());
        Packet *dupPacket = packet->dup();
        sentDataQueue.insert(dupPacket);
        delete queuePacket;
        return std::make_tuple(ndpseg, packet);
    }
    else {
        EV_INFO << " Nothing to send !! \n";
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
    EV_INFO << "\n ackArrived: " << ackNum << "\n";
    for (int i = 0; i <= sentDataQueue.getLength(); i++) {
        Packet *packet = check_and_cast<Packet*>(sentDataQueue.get(i));
        auto &appmsg = packet->peekData<GenericAppMsgNdp>();
        if (appmsg->getSequenceNumber() == ackNum) {
            sentDataQueue.remove(sentDataQueue.get(i));
            delete packet;
            break;
        }
    }
}

void NdpSendQueue::nackArrived(unsigned int nackNum)
{
    bool found = false;
    for (int i = 0; i <= sentDataQueue.getLength(); i++) {
        Packet *packet = check_and_cast<Packet*>(sentDataQueue.get(i));
        auto &appmsg = packet->peekData<GenericAppMsgNdp>();
        if (appmsg->getSequenceNumber() == nackNum) {
            moveFrontDataQueue(nackNum);
            sentDataQueue.remove(packet);
            delete packet;
            found = true;
            break;
        }
    }
    assert(found == false);
}

}            // namespace ndp

} // namespace inet


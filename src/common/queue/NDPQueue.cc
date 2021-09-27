//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "inet/common/INETDefs.h"

#include "NDPQueue.h"
//#include "inet/networklayer/ipv4/IPv4Datagram_m.h"

#include <omnetpp.h>
// #include "inet/raptorqimplementation/rqtransportlayer/RaptorQ/raptorq_common/RQSegment.h"

//using namespace inet::raptorq;
#include "inet/common/ModuleAccess.h"
#include "inet/common/Simsignals.h"
#include "inet/queueing/function/PacketComparatorFunction.h"
#include "inet/queueing/function/PacketDropperFunction.h"
#include "inet/queueing/queue/CompoundPacketQueue.h"
#include "../../transportlayer/Ndp/ndp_common/NdpHeader.h"
#include "../../networklayer/ipv4/Ipv4Ndp.h"
#include "../../networklayer/ipv4/Ipv4HeaderNdp_m.h"

#include "../../common/ProtocolNdp.h"
#include "inet/networklayer/common/L3Tools.h"
#include "inet/transportlayer/common/L4Tools.h"
namespace inet {
namespace queueing {

Define_Module(NDPQueue);

simsignal_t NDPQueue::packetPushedDataQueueSignal = registerSignal("packetPushedDataQueue");
simsignal_t NDPQueue::packetPoppedDataQueueSignal = registerSignal("packetPoppedDataQueue");

simsignal_t NDPQueue::packetPushedHeadersQueueSignal = registerSignal("packetPushedHeadersQueue");
simsignal_t NDPQueue::packetPoppedHeadersQueueSignal = registerSignal("packetPoppedHeadersQueue");

simsignal_t NDPQueue::packetPushedSynAckQueueSignal = registerSignal("packetPushedSynAckQueue");
simsignal_t NDPQueue::packetPoppedSynAckQueueSignal = registerSignal("packetPoppedSynAckQueue");
//simsignal_t NDPQueue::packetRemovedSignal = registerSignal("synAckQueueLength");
//simsignal_t NDPQueue::numTrimmedPktSig = registerSignal("numTrimmedPkt");

//simsignal_t NDPQueue::dataQueueLengthSignal = registerSignal("dataQueueLength");
//simsignal_t NDPQueue::headersQueueLengthSignal = registerSignal("headersQueueLength");
//simsignal_t NDPQueue::synAckQueueLengthSignal = registerSignal("synAckQueueLength");
//simsignal_t NDPQueue::numTrimmedPktSig = registerSignal("numTrimmedPkt");

void NDPQueue::initialize(int stage)
{
    PacketQueueBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        numTrimmedPacketsVec.setName("numTrimmedPacketsVec");
        weight=10;
        dataQueueLength = 0 ;
        headersQueueLength = 0;
        synAckQueueLength=0;
        numTrimmedPkt=0;

        inputGate = gate("in");
        producer = findConnectedModule<IActivePacketSource>(inputGate);
        outputGate = gate("out");
        collector = findConnectedModule<IActivePacketSink>(outputGate);

        WATCH(dataQueueLength);
        WATCH(headersQueueLength);
        WATCH(synAckQueueLength);
        WATCH(numTrimmedPkt);

        dataQueue.setName("dataQueue");
        headersQueue.setName("headerQueue");
        synAckQueue.setName("synAckQueue");
        // configuration
        packetCapacity = par("packetCapacity");
        // moh added
        recordScalar("packetCapacity= ", packetCapacity);
    }
    else if (stage == INITSTAGE_QUEUEING) {
            checkPushPacketSupport(inputGate);
            checkPopPacketSupport(outputGate);
            if (producer != nullptr)
                producer->handleCanPushPacket(inputGate);
        }
    else if (stage == INITSTAGE_LAST)
        updateDisplayString();
    //emit()
    //statistics
    //emit(dataQueueLengthSignal, dataQueue.getLength());
    //emit(headersQueueLengthSignal, headersQueue.getLength());
    //emit(numTrimmedPktSig, numTrimmedPkt);
}

void NDPQueue::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    pushPacket(packet, packet->getArrivalGate());
}

bool NDPQueue::isOverloaded() const
{
    return dataQueue.getLength() >= packetCapacity;
}

int NDPQueue::getNumPackets() const
{
    return dataQueue.getLength();
}

Packet *NDPQueue::getPacket(int index) const
{
    if (index < 0 || index >= dataQueue.getLength())
        throw cRuntimeError("index %i out of range", index);
    return check_and_cast<Packet *>(dataQueue.get(index));
}

void NDPQueue::dropPacket(Packet *packet, PacketDropReason reason, int limit)
{
    PacketDropDetails details;
    details.setReason(reason);
    details.setLimit(limit);
    emit(packetDroppedSignal, packet, &details);
    delete packet;
}

void NDPQueue::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacket");
    EV_INFO << "\nPACKET STRING" << packet->str() << std::endl;
    auto ipv4Header = packet->removeAtFront<Ipv4HeaderNdp>();
    auto ndpHeader = packet->removeAtFront<ndp::NdpHeader>();
    //auto& ipv4Header = removeNetworkProtocolHeader<Ipv4HeaderNdp>(packet);
    //auto& ndpHeader = removeTransportProtocolHeader<ndp::NdpHeader>(packet);
    //EV_INFO << "\nENCAPSULATED PACKET STRING" << ipv4Header->str() << std::endl;
    //EV_INFO << "\nENCAPSULATED PACKET STRING" << ndpHeader->str() << std::endl;
    //auto ipv4Header = Ipv4::removeNetworkProtocolHeader<Ipv4Header>(packet);
    EV_INFO << "Pushing packet " << packet->getName() << " into the queue." << endl;
    if ( ndpHeader->getAckBit()==true || ndpHeader->getSynBit()==true || ndpHeader->getNackBit()==true) {
       //insertTransportProtocolHeader(packet, ProtocolNdp::ndp, ndpHeader);
       //insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
       packet->insertAtFront(ndpHeader);
       packet->insertAtFront(ipv4Header);
       synAckQueue.insert(packet);
       synAckQueueLength=synAckQueue.getLength();
       //emit(packetPushedSynAckQueueSignal, packet);
       //emit(synAckQueueLengthSignal, cPar(synAckQueue.getLength()));
    }
    else if (ndpHeader->isHeader() == true ) {
        //insertTransportProtocolHeader(packet, ProtocolNdp::ndp, ndpHeader);
        //insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
        headersQueue.insert(packet);
        headersQueueLength = headersQueue.getLength();
        emit(packetPushedHeadersQueueSignal, packet);
    }
    else if (ndpHeader->isPullPacket() == true ) {
        //insertTransportProtocolHeader(packet, ProtocolNdp::ndp, ndpHeader);
        //insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
        packet->insertAtFront(ndpHeader);
        packet->insertAtFront(ipv4Header);
        headersQueue.insert(packet);
        headersQueueLength = headersQueue.getLength();
        //emit(packetPushedHeadersQueueSignal, packet);
    }
    else if (isOverloaded()) {
        std::string header="Header-";
        if (ndpHeader != nullptr) {
            std::string name=packet->getName();
            std::string rename=header+name;
            //ndpHeader->setName(rename.c_str());
            packet->setName(rename.c_str());
            ndpHeader->setIsHeader(true);
            ndpHeader->setIsDataPacket(false);

            unsigned short srcPort = ndpHeader->getSrcPort();
            unsigned short destPort = ndpHeader->getDestPort();
            EV << "   hhh   " << srcPort << "\n\n\n\n";
            EV << "   hhh   " << destPort << "\n\n\n\n";
            EV << "   hhh   " << ndpHeader->getFullName() << "\n\n\n\n";
        }
        //insertTransportProtocolHeader(packet, ProtocolNdp::ndp, ndpHeader);
        //insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
        packet->insertAtFront(ndpHeader);
        packet->insertAtFront(ipv4Header);
        headersQueue.insert(packet);
        headersQueueLength=headersQueue.getLength();
        //emit(packetPushedHeadersQueueSignal, packet);
        ++numTrimmedPkt;
        numTrimmedPacketsVec.record(numTrimmedPkt);
        //emit(numTrimmedPktSig, numTrimmedPkt);       TODO EMIT
        }
    else {
        //insertTransportProtocolHeader(packet, ProtocolNdp::ndp, ndpHeader);
        //insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
        packet->insertAtFront(ndpHeader);
        packet->insertAtFront(ipv4Header);
       // dataQueue is not full ==> insert the incoming packet in the dataQueue
        dataQueue.insert(packet);
        //emit(packetPushedDataQueueSignal, packet);
        dataQueueLength=dataQueue.getLength();
    }
}


Packet *NDPQueue::popPacket(cGate *gate) {
    Enter_Method("popPacket");
    if (dataQueue.isEmpty() && headersQueue.isEmpty() && synAckQueue.isEmpty())
        return nullptr;
    else if (synAckQueue.getLength()!=0){
        auto packet = check_and_cast<Packet *>(synAckQueue.front());
        synAckQueue.pop();
        //emit(packetPoppedSynAckQueueSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() == 0 && dataQueue.getLength() != 0) {
        auto packet = check_and_cast<Packet *>(dataQueue.front());
        dataQueue.pop();
        //emit(packetPoppedDataQueueSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() != 0 && dataQueue.getLength() == 0) {
        auto packet = check_and_cast<Packet *>(headersQueue.front());
        headersQueue.pop();
        //emit(packetPoppedHeadersQueueSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if ( headersQueue.getLength() != 0 && dataQueue.getLength() != 0 && weight%10 == 0) {
        auto packet = check_and_cast<Packet *>(dataQueue.front());
        dataQueue.pop();
        //emit(packetPoppedDataQueueSignal, packet);
        ++weight;
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() != 0 && dataQueue.getLength() != 0 ) {
        auto packet = check_and_cast<Packet *>(headersQueue.front());
        headersQueue.pop();
        EV_INFO << " get from header queue- size = " << packet->getByteLength() << "\n\n\n\n\n\n";
        //emit(packetPoppedHeadersQueueSignal, packet);
        ++weight;
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    return nullptr;
}

void NDPQueue::removePacket(Packet *packet)
{
    Enter_Method("removePacket");
    EV_INFO << "Removing packet " << packet->getName() << " from the queue." << endl;
    dataQueue.remove(packet);
    //emit(packetRemovedSignal, packet);
    updateDisplayString();
}

bool NDPQueue::isEmpty() const
{
    bool a = headersQueue.isEmpty();
    bool b = synAckQueue.isEmpty();
    bool c = dataQueue.isEmpty();
    bool d;
    if (a == true && b == true && c == true) {
        d = true;
    }
    else {
        d = false;
    }

    return d;
//    return  dataQueue.isEmpty();
}


//void NDPQueue::refreshDisplay() const
//{
//     char buf[100];
//    sprintf(buf, "q dataLen: %d\nq headersLen: %d\nq rcvd: %d\nq dropped: %d", dataQueueLength, headersQueueLength,numQueueReceived,numQueueDropped );
//    getDisplayString().setTagArg("t", 0, buf);
//}

void NDPQueue::handlePacketRemoved(Packet *packet)
{
    Enter_Method("handlePacketRemoved");
    if (dataQueue.contains(packet)) {
        EV_INFO << "Removing packet " << packet->getName() << " from the queue." << endl;
        dataQueue.remove(packet);
        //emit(packetRemovedSignal, packet);
        updateDisplayString();
    }
}

void NDPQueue::finish(){
    recordScalar("numTrimmedPkt ",numTrimmedPkt );
    //emit(numTrimmedPktSig, numTrimmedPkt);
    if (numTrimmedPkt>0)
      std::cout << " mmmmmmmmmmmmmmmmmmmmmm " << numTrimmedPkt << "\n\n";
}


}
} // namespace inet


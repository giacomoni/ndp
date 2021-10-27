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

#include <inet/common/INETDefs.h>
#include <inet/common/ModuleAccess.h>
#include <inet/common/Simsignals.h>
#include <inet/queueing/function/PacketComparatorFunction.h>
#include <inet/queueing/function/PacketDropperFunction.h>
#include <inet/networklayer/ipv4/Ipv4Header_m.h>
#include <inet/queueing/base/PacketQueueBase.h>

#include "../../application/ndpapp/GenericAppMsgNdp_m.h"
#include "../../transportlayer/Ndp/ndp_common/NdpHeader.h"
#include "NdpSwitchQueue.h"

namespace inet {
namespace queueing {
Define_Module(NdpSwitchQueue);

simsignal_t NdpSwitchQueue::queueingTimeSignal = registerSignal("queueingTime");
simsignal_t NdpSwitchQueue::dataQueueLengthSignal = registerSignal("dataQueueLength");
simsignal_t NdpSwitchQueue::headersQueueLengthSignal = registerSignal("headersQueueLength");
simsignal_t NdpSwitchQueue::numTrimmedPktSig = registerSignal("numTrimmedPkt");

void NdpSwitchQueue::initialize(int stage)
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

        subscribe(packetPushedSignal, this);
        subscribe(packetPoppedSignal, this);
        subscribe(packetRemovedSignal, this);
        subscribe(packetDroppedSignal, this);
        subscribe(packetCreatedSignal, this);

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
    cSimpleModule::emit(dataQueueLengthSignal, dataQueue.getLength());
    cSimpleModule::emit(headersQueueLengthSignal, headersQueue.getLength());
    cSimpleModule::emit(numTrimmedPktSig, numTrimmedPkt);
}

void NdpSwitchQueue::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    pushPacket(packet, packet->getArrivalGate());
}

bool NdpSwitchQueue::isOverloaded() const
{
    return dataQueue.getLength() >= packetCapacity;
}

int NdpSwitchQueue::getNumPackets() const
{
    return dataQueue.getLength();
}

Packet *NdpSwitchQueue::getPacket(int index) const
{
    if (index < 0 || index >= dataQueue.getLength())
        throw cRuntimeError("index %i out of range", index);
    return check_and_cast<Packet *>(dataQueue.get(index));
}

void NdpSwitchQueue::dropPacket(Packet *packet, PacketDropReason reason, int limit)
{
    PacketDropDetails details;
    details.setReason(reason);
    details.setLimit(limit);
    cSimpleModule::emit(packetDroppedSignal, packet, &details);
    delete packet;
}

void NdpSwitchQueue::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacket");
    emit(packetPushedSignal, packet);
    EV_INFO << "PACKET STRING" << packet->str() << endl;
    EV_INFO << "Pushing packet " << packet->getName() << " into the queue." << endl;
    const auto& ipv4Datagram = packet->peekAtFront<Ipv4Header>();
    const auto& ndpHeaderPeek = packet->peekDataAt<ndp::NdpHeader>(ipv4Datagram->getChunkLength());
    if ( ndpHeaderPeek->getAckBit()==true || ndpHeaderPeek->getSynBit()==true || ndpHeaderPeek->getNackBit()==true) {
       synAckQueue.insert(packet);
       synAckQueueLength=synAckQueue.getLength();
       return;
    }
    else if (ndpHeaderPeek->isHeader() == true ) {
        headersQueue.insert(packet);
        headersQueueLength = headersQueue.getLength();
        return;
    }
    else if (ndpHeaderPeek->isPullPacket() == true ) {
        headersQueue.insert(packet);
        headersQueueLength = headersQueue.getLength();
        return;
    }
    else if (isOverloaded()) {
        std::string header="Header-";
        auto ipv4Header = packet->removeAtFront<Ipv4Header>();
        ASSERT(B(ipv4Header->getTotalLengthField()) >= ipv4Header->getChunkLength());
        if (ipv4Header->getTotalLengthField() < packet->getDataLength())
            packet->setBackOffset(B(ipv4Header->getTotalLengthField()) - ipv4Header->getChunkLength());
        auto ndpHeader = packet->removeAtFront<ndp::NdpHeader>();
        packet->removeAtFront<GenericAppMsgNdp>();
        if (ndpHeader != nullptr) {
            std::string name=packet->getName();
            std::string rename=header+name;
            packet->setName(rename.c_str());
            ndpHeader->setIsHeader(true);
            ndpHeader->setIsDataPacket(false);

            unsigned short srcPort = ndpHeader->getSrcPort();
            unsigned short destPort = ndpHeader->getDestPort();
            EV << "NdpSwitchQueue srcPort:" << srcPort << endl;
            EV << "NdpSwitchQueue destPort:" << destPort << endl;
            EV << "NdpSwitchQueue Header Full Name:" << ndpHeader->getFullName() << endl;
        }
        packet->insertAtFront(ndpHeader);
        ipv4Header->setTotalLengthField(ipv4Header->getChunkLength() + packet->getDataLength());
        packet->insertAtFront(ipv4Header);
        headersQueue.insert(packet);
        headersQueueLength=headersQueue.getLength();
        //emit(packetPushedHeadersQueueSignal, packet);
        ++numTrimmedPkt;
        numTrimmedPacketsVec.record(numTrimmedPkt);
        cSimpleModule::emit(numTrimmedPktSig, numTrimmedPkt);
        return;
    }
    else {
        dataQueue.insert(packet);
        dataQueueLength=dataQueue.getLength();
        return;
    }
}


Packet *NdpSwitchQueue::popPacket(cGate *gate) {
    Enter_Method("popPacket");
    if (dataQueue.isEmpty() && headersQueue.isEmpty() && synAckQueue.isEmpty()){
        return nullptr;
    }
    else if (synAckQueue.getLength()!=0){  //syn/ack pop
        auto packet = check_and_cast<Packet *>(synAckQueue.pop());
        cSimpleModule::emit(packetRemovedSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() == 0 && dataQueue.getLength() != 0) { //dataQueue pop
        auto packet = check_and_cast<Packet *>(dataQueue.pop());
        cSimpleModule::emit(dataQueueLengthSignal, dataQueue.getLength());
        emit(packetRemovedSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() != 0 && dataQueue.getLength() == 0) { //header/pull pop
        auto packet = check_and_cast<Packet *>(headersQueue.pop());
        cSimpleModule::emit(headersQueueLengthSignal, headersQueue.getLength());
        emit(packetRemovedSignal, packet);
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    else if ( headersQueue.getLength() != 0 && dataQueue.getLength() != 0 && weight%10 == 0) { //round robin dataQueue pop
        auto packet = check_and_cast<Packet *>(dataQueue.pop());
        cSimpleModule::emit(dataQueueLengthSignal, dataQueue.getLength());
        emit(packetRemovedSignal, packet);
        ++weight;
        animateSend(packet, outputGate);
        return packet;
    }
    else if (headersQueue.getLength() != 0 && dataQueue.getLength() != 0 ) {
        auto packet = check_and_cast<Packet *>(headersQueue.pop());
        emit(packetRemovedSignal, packet);
        EV_INFO << " get from header queue- size = " << packet->getByteLength() << endl;
        cSimpleModule::emit(headersQueueLengthSignal, headersQueue.getLength());
        ++weight;
        updateDisplayString();
        animateSend(packet, outputGate);
        return packet;
    }
    return nullptr;
}

void NdpSwitchQueue::removePacket(Packet *packet)
{
    Enter_Method("removePacket");
    EV_INFO << "Removing packet " << packet->getName() << " from the queue." << endl;
    dataQueue.remove(packet);
    emit(packetRemovedSignal, packet);
    updateDisplayString();
}

bool NdpSwitchQueue::isEmpty() const
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
}

void NdpSwitchQueue::receiveSignal(cComponent *source, simsignal_t signal, cObject *object, cObject *details)
{
    Enter_Method("receiveSignal");
    if (signal == packetPushedSignal || signal == packetPoppedSignal || signal == packetRemovedSignal)
        ;
    else if (signal == packetDroppedSignal)
        numDroppedPackets++;
    else if (signal == packetCreatedSignal)
        numCreatedPackets++;
    else
        throw cRuntimeError("Unknown signal");
    updateDisplayString();
}

void NdpSwitchQueue::finish(){
    recordScalar("numTrimmedPkt ",numTrimmedPkt );
    cSimpleModule::emit(numTrimmedPktSig, numTrimmedPkt);
}

}
} // namespace inet


//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/applications/common/SocketTag_m.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "../common/L4ToolsNdp.h"
#include "inet/common/checksum/TcpIpChecksum.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/common/EcnTag_m.h"
#include "inet/networklayer/common/IpProtocolId_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "../../common/ProtocolNdp.h"
#ifdef WITH_IPv4
#include "inet/networklayer/ipv4/IcmpHeader_m.h"
#endif // ifdef WITH_IPv4

#ifdef WITH_IPv6
#include "inet/networklayer/icmpv6/Icmpv6Header_m.h"
#endif // ifdef WITH_IPv6

#define PACING_TIME 12  //    MTU/linkRate

#include "inet/transportlayer/common/TransportPseudoHeader_m.h"
#include "../contract/ndp/NDPCommand_m.h"
#include "Ndp.h"
#include "NDPConnection.h"
#include "NDPReceiveQueue.h"
#include "NDPSendQueue.h"
#include "ndp_common/NdpHeader.h"
#include "../../networklayer/ipv4/Ipv4HeaderNdp_m.h"
namespace inet {
namespace ndp {

Define_Module(Ndp);

simsignal_t Ndp::numRequestsRTOs = registerSignal("numRequestsRTOs");

Ndp::~Ndp()
{
    while (!ndpAppConnMap.empty()) {
       auto i = ndpAppConnMap.begin();
       i->second->deleteModule();
       ndpAppConnMap.erase(i);
    }
}

void Ndp::initialize(int stage)
{
    OperationalBase::initialize(stage);
    //delete getModuleByPath("myexample.client.ndp.conn-10");
    if (stage == INITSTAGE_LOCAL) {

        lastEphemeralPort = EPHEMERAL_PORTRANGE_START;

        requestTimerStamps.setName("requestTimerStamps");
        msl = par("msl");
        useDataNotification = par("useDataNotification");

        WATCH(lastEphemeralPort);
        WATCH_PTRMAP(ndpConnMap);
        WATCH_PTRMAP(ndpAppConnMap);
    }
    else if (stage == INITSTAGE_TRANSPORT_LAYER) {
        requestTimerMsg = new cMessage("requestTimerMsg");
        requestTimerMsg->setContextPointer(this);

        registerService(ProtocolNdp::ndp, gate("appIn"), gate("ipIn"));
        registerProtocol(ProtocolNdp::ndp, gate("ipOut"), gate("appOut"));
    }
}

void Ndp::finish()
{
    if (requestTimerMsg->isScheduled())
            cancelEvent(requestTimerMsg);
            delete requestTimerMsg;
    EV_INFO << getFullPath() << ": finishing with " << ndpConnMap.size() << " connections open.\n";
}

void Ndp::handleSelfMessage(cMessage *msg)
{
    //throw cRuntimeError("model error: should schedule timers on connection");
    if (msg == requestTimerMsg) {
        process_REQUEST_TIMER();
    }
    else{
        NDPConnection *conn = (NDPConnection *) msg->getContextPointer();
        bool ret = conn->processTimer(msg);
    }
}

void Ndp::handleUpperCommand(cMessage *msg)
{
    int socketId = getTags(msg).getTag<SocketReq>()->getSocketId();
    NDPConnection *conn = findConnForApp(socketId);

    if (!conn) {
        conn = createConnection(socketId);

        // add into appConnMap here; it'll be added to connMap during processing
        // the OPEN command in TcpConnection's processAppCommand().
        ndpAppConnMap[socketId] = conn;

        EV_INFO << "Ndp connection created for " << msg << "\n";
    }

    if (!conn->processAppCommand(msg))
        removeConnection(conn);
}

void Ndp::sendFromConn(cMessage *msg, const char *gatename, int gateindex)
{
    Enter_Method_Silent();
    take(msg);
    send(msg, gatename, gateindex);
}

void Ndp::handleUpperPacket(Packet *packet)
{
    handleUpperCommand(packet);
}
NDPConnection *Ndp::findConnForApp(int socketId)
{
    auto i = ndpAppConnMap.find(socketId);
    return i == ndpAppConnMap.end() ? nullptr : i->second;
}

void Ndp::handleLowerPacket(Packet *packet)
{
    EV_INFO << "\n\n\n\nLOWER PACKET DETAILS: " << packet->str() << std::endl;
    // must be a NdpHeader
    auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
    if (protocol == &ProtocolNdp::ndp) {
        auto ndpHeader = packet->peekAtFront<NdpHeader>();
        //TODO Packet does not appear to have NdpHeader at front?
        //auto ipv4Header = packet->removeAtFront<Ipv4HeaderNdp>();
        //auto ndpHeader = packet->removeAtFront<ndp::NdpHeader>();
        //inet::Ptr<NdpHeader> header = makeShared<NdpHeader>();
        //header->copy(ndpHeader);
        //header->setPriorityValue(10);   //FIX THIS
        //ndpHeader->setPriorityValue(10);
        // get src/dest addresses
        //packet->insertAtFront(ndpHeader);
        //packet->insertAtFront(ipv4Header);
        L3Address srcAddr, destAddr;
        srcAddr = packet->getTag<L3AddressInd>()->getSrcAddress();
        destAddr = packet->getTag<L3AddressInd>()->getDestAddress();
        int ecn = 0;
        if (auto ecnTag = packet->findTag<EcnInd>())
            ecn = ecnTag->getExplicitCongestionNotification();
        ASSERT(ecn != -1);

        // process segment
        NDPConnection *conn = nullptr;
        conn = findConnForSegment(ndpHeader, srcAddr, destAddr);
        if (conn) {
            bool ret = conn->processNDPSegment(packet, ndpHeader, srcAddr, destAddr);
            if (!ret)
                removeConnection(conn);
        }
        else {
            segmentArrivalWhileClosed(packet, ndpHeader, srcAddr, destAddr);
        }
    }
    else if (protocol == &Protocol::icmpv4 || protocol == &Protocol::icmpv6)  {
        EV_DETAIL << "ICMP error received -- discarding\n";    // FIXME can ICMP packets really make it up to Tcp???
        delete packet;
    }
    else
        throw cRuntimeError("Unknown protocol: '%s'", (protocol != nullptr ? protocol->getName() : "<nullptr>"));
}

NDPConnection *Ndp::createConnection(int socketId)
{
    auto moduleType = cModuleType::get("ndp.transportlayer.Ndp.NDPConnection");
    char submoduleName[24];
    sprintf(submoduleName, "conn-%d", socketId);
    auto module = check_and_cast<NDPConnection *>(moduleType->createScheduleInit(submoduleName, this));
    module->initConnection(this, socketId);
    return module;
}

void Ndp::removeConnection(NDPConnection *conn)
{
    EV_INFO << "Deleting Ndp connection\n";

    ndpAppConnMap.erase(conn->socketId);

    SockPair key2;
    key2.localAddr = conn->localAddr;
    key2.remoteAddr = conn->remoteAddr;
    key2.localPort = conn->localPort;
    key2.remotePort = conn->remotePort;
    ndpConnMap.erase(key2);

    // IMPORTANT: usedEphemeralPorts.erase(conn->localPort) is NOT GOOD because it
    // deletes ALL occurrences of the port from the multiset.
    auto it = usedEphemeralPorts.find(conn->localPort);

    if (it != usedEphemeralPorts.end())
        usedEphemeralPorts.erase(it);

    //emit(ndpConnectionRemovedSignal, conn);
    conn->deleteModule();
}

NDPConnection *Ndp::findConnForSegment(const Ptr<const NdpHeader>& ndpseg, L3Address srcAddr, L3Address destAddr)
{
    SockPair key;
    key.localAddr = destAddr;
    key.remoteAddr = srcAddr;
    key.localPort = ndpseg->getDestPort();
    key.remotePort = ndpseg->getSrcPort();
    SockPair save = key;

    EV_INFO << "\n   eeee localPort   " <<  key.localPort  << " \n";
    EV_INFO << "\n eee localAddr  " <<  destAddr  << " \n";
    EV_INFO << "\n eee destAddr " <<  srcAddr << " \n";
    EV_INFO << "\n eee remotePort  " <<  key.remotePort  << " \n";

    // try with fully qualified SockPair
    auto i = ndpConnMap.find(key);
    if (i != ndpConnMap.end())
        return i->second;

    // try with localAddr missing (only localPort specified in passive/active open)
    key.localAddr = L3Address();
    i = ndpConnMap.find(key);

    if (i != ndpConnMap.end())
        return i->second;

    // try fully qualified local socket + blank remote socket (for incoming SYN)
    key = save;
    key.remoteAddr = L3Address();
    key.remotePort = -1;
    i = ndpConnMap.find(key);

    if (i != ndpConnMap.end())
        return i->second;

    // try with blank remote socket, and localAddr missing (for incoming SYN)
    key.localAddr = L3Address();
    i = ndpConnMap.find(key);

    if (i != ndpConnMap.end())
        return i->second;

    // given up
    return nullptr;
}

void Ndp::segmentArrivalWhileClosed(Packet *packet, const Ptr<const NdpHeader>& ndpseg, L3Address srcAddr, L3Address destAddr)
{
    auto moduleType = cModuleType::get("ndp.transportlayer.Ndp.NDPConnection");
    const char *submoduleName = "conn-temp";
    auto module = check_and_cast<NDPConnection *>(moduleType->createScheduleInit(submoduleName, this));
    module->initConnection(this, -1);
    module->segmentArrivalWhileClosed(packet, ndpseg, srcAddr, destAddr);
    module->deleteModule();
    delete packet;
}

ushort Ndp::getEphemeralPort()
{
    // start at the last allocated port number + 1, and search for an unused one
    ushort searchUntil = lastEphemeralPort++;
    if (lastEphemeralPort == EPHEMERAL_PORTRANGE_END) // wrap
        lastEphemeralPort = EPHEMERAL_PORTRANGE_START;

    while (usedEphemeralPorts.find(lastEphemeralPort) != usedEphemeralPorts.end()) {
        if (lastEphemeralPort == searchUntil) // got back to starting point?
            throw cRuntimeError("Ephemeral port range %d..%d exhausted, all ports occupied", EPHEMERAL_PORTRANGE_START, EPHEMERAL_PORTRANGE_END);

        lastEphemeralPort++;

        if (lastEphemeralPort == EPHEMERAL_PORTRANGE_END) // wrap
            lastEphemeralPort = EPHEMERAL_PORTRANGE_START;
    }

    // found a free one, return it
    return lastEphemeralPort;
}

void Ndp::addForkedConnection(NDPConnection *conn, NDPConnection *newConn, L3Address localAddr, L3Address remoteAddr, int localPort, int remotePort)
{
    // update conn's socket pair, and register newConn
    addSockPair(newConn, localAddr, remoteAddr, localPort, remotePort);

    // newConn will live on with the new socketId
    ndpAppConnMap[newConn->socketId] = newConn;
}

void Ndp::addSockPair(NDPConnection *conn, L3Address localAddr, L3Address remoteAddr, int localPort, int remotePort)
{
    // update addresses/ports in TcpConnection
    SockPair key;
    key.localAddr = conn->localAddr = localAddr;
    key.remoteAddr = conn->remoteAddr = remoteAddr;
    key.localPort = conn->localPort = localPort;
    key.remotePort = conn->remotePort = remotePort;

    EV_INFO << "\naaaa  localAddr " <<  localAddr << " \n";
    EV_INFO << "\naaa remoteAddr   " <<  remoteAddr  << " \n";
    EV_INFO << "\naaa localPort  " <<  localPort  << " \n";
    EV_INFO << "\naaa remotePort  " <<  remotePort  << " \n";

    // make sure connection is unique
    auto it = ndpConnMap.find(key);
    if (it != ndpConnMap.end()) {
        // throw "address already in use" error
        if (remoteAddr.isUnspecified() && remotePort == -1)
            throw cRuntimeError("Address already in use: there is already a connection listening on %s:%d",
                    localAddr.str().c_str(), localPort);
        else
            throw cRuntimeError("Address already in use: there is already a connection %s:%d to %s:%d",
                    localAddr.str().c_str(), localPort, remoteAddr.str().c_str(), remotePort);
    }

    // then insert it into ncpConnMap
    ndpConnMap[key] = conn;

    // mark port as used
    if (localPort >= EPHEMERAL_PORTRANGE_START && localPort < EPHEMERAL_PORTRANGE_END)
        usedEphemeralPorts.insert(localPort);
}

void Ndp::updateSockPair(NDPConnection *conn, L3Address localAddr, L3Address remoteAddr, int localPort, int remotePort)
{
    // find with existing address/port pair...
    SockPair key;
    key.localAddr = conn->localAddr;
    key.remoteAddr = conn->remoteAddr;
    key.localPort = conn->localPort;
    key.remotePort = conn->remotePort;
    auto it = ndpConnMap.find(key);

    ASSERT(it != ndpConnMap.end() && it->second == conn);

    // ...and remove from the old place in ndpConnMap
    ndpConnMap.erase(it);

    // then update addresses/ports, and re-insert it with new key into tcpConnMap
    key.localAddr = conn->localAddr = localAddr;
    key.remoteAddr = conn->remoteAddr = remoteAddr;
    ASSERT(conn->localPort == localPort);
    key.remotePort = conn->remotePort = remotePort;
    ndpConnMap[key] = conn;

    EV_INFO << "\nbbbb updateSockPair localAddr " <<  localAddr << " \n";
    EV_INFO << "\nbbbb updateSockPair remoteAddr   " <<  remoteAddr  << " \n";
    EV_INFO << "\nbbbb updateSockPair localPort  " <<  localPort  << " \n";
    EV_INFO << "\nbbbb updateSockPair remotePort  " <<  remotePort  << " \n";
    // localPort doesn't change (see ASSERT above), so there's no need to update usedEphemeralPorts[].
}

NDPSendQueue *Ndp::createSendQueue()
{
    return new NDPSendQueue();
}

NDPReceiveQueue *Ndp::createReceiveQueue()
{
    return new NDPReceiveQueue();
}

void Ndp::handleStartOperation(LifecycleOperation *operation)
{
    //FIXME implementation
}

void Ndp::handleStopOperation(LifecycleOperation *operation)
{
    //FIXME close connections??? yes, because the applications may not close them!!!
    reset();
    delayActiveOperationFinish(par("stopOperationTimeout"));
    startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void Ndp::handleCrashOperation(LifecycleOperation *operation)
{
    reset();
}

void Ndp::reset()
{
    for (auto & elem : ndpAppConnMap)
        elem.second->deleteModule();
    ndpAppConnMap.clear();
    ndpConnMap.clear();
    usedEphemeralPorts.clear();
    lastEphemeralPort = EPHEMERAL_PORTRANGE_START;
}

void Ndp::refreshDisplay() const {
    OperationalBase::refreshDisplay();

   if (getEnvir()->isExpressMode()) {
       // in express mode, we don't bother to update the display
       // (std::map's iteration is not very fast if map is large)
       getDisplayString().setTagArg("t", 0, "");
       return;
   }
   int numINIT = 0, numCLOSED = 0, numLISTEN = 0, numSYN_SENT = 0, numSYN_RCVD = 0,
           numESTABLISHED = 0, numCLOSE_WAIT = 0, numLAST_ACK = 0, numFIN_WAIT_1 = 0,
           numFIN_WAIT_2 = 0, numCLOSING = 0, numTIME_WAIT = 0;

    for (auto & elem : ndpAppConnMap) {
        int state = (elem).second->getFsmState();

        switch (state) {
        case NDP_S_INIT:
            numINIT++;
            break;

        case NDP_S_CLOSED:
            numCLOSED++;
            break;

        case NDP_S_LISTEN:
            numLISTEN++;
            break;

        case NDP_S_SYN_SENT:
            numSYN_SENT++;
            break;

        case NDP_S_SYN_RCVD:
            numSYN_RCVD++;
            break;

        case NDP_S_ESTABLISHED:
            numESTABLISHED++;
            break;

        case NDP_S_CLOSE_WAIT:
            numCLOSE_WAIT++;
            break;

        case NDP_S_LAST_ACK:
            numLAST_ACK++;
            break;

        case NDP_S_FIN_WAIT_1:
            numFIN_WAIT_1++;
            break;

        case NDP_S_FIN_WAIT_2:
            numFIN_WAIT_2++;
            break;

        case NDP_S_CLOSING:
            numCLOSING++;
            break;

        case NDP_S_TIME_WAIT:
            numTIME_WAIT++;
            break;
        }
    }

    char buf2[200];
    buf2[0] = '\0';

    if (numINIT > 0)
        sprintf(buf2 + strlen(buf2), "init:%d ", numINIT);
    if (numCLOSED > 0)
        sprintf(buf2 + strlen(buf2), "closed:%d ", numCLOSED);
    if (numLISTEN > 0)
        sprintf(buf2 + strlen(buf2), "listen:%d ", numLISTEN);
    if (numSYN_SENT > 0)
        sprintf(buf2 + strlen(buf2), "syn_sent:%d ", numSYN_SENT);
    if (numSYN_RCVD > 0)
        sprintf(buf2 + strlen(buf2), "syn_rcvd:%d ", numSYN_RCVD);
    if (numESTABLISHED > 0)
        sprintf(buf2 + strlen(buf2), "estab:%d ", numESTABLISHED);
    if (numCLOSE_WAIT > 0)
        sprintf(buf2 + strlen(buf2), "close_wait:%d ", numCLOSE_WAIT);
    if (numLAST_ACK > 0)
        sprintf(buf2 + strlen(buf2), "last_ack:%d ", numLAST_ACK);
    if (numFIN_WAIT_1 > 0)
        sprintf(buf2 + strlen(buf2), "fin_wait_1:%d ", numFIN_WAIT_1);
    if (numFIN_WAIT_2 > 0)
        sprintf(buf2 + strlen(buf2), "fin_wait_2:%d ", numFIN_WAIT_2);
    if (numCLOSING > 0)
        sprintf(buf2 + strlen(buf2), "closing:%d ", numCLOSING);
    if (numTIME_WAIT > 0)
        sprintf(buf2 + strlen(buf2), "time_wait:%d ", numTIME_WAIT);

    getDisplayString().setTagArg("t", 0, buf2);
}

void Ndp::printConnRequestMap() {
//    std::cout << "   printConnRequestMap   "     << "\n";
    auto iterrr = requestCONNMap.begin();
    int index = 0;
    while (iterrr != requestCONNMap.end()) {
//          EV << index << " printConnRequestMap \n " ;
//          EV <<  " connIndex = " <<  iterrr->first << " \n " ;
//          EV << "  connId=  " << iterrr->second->connId  << "\n" ;
//          EV << " getPullsQueueLength()=  " << iterrr->second->getPullsQueueLength() << "\n" ;
//          EV << " rcvdSymbols =  " << iterrr->second->getNumRcvdSymbols() <<  "\n\n\n" ;
//          EV << " requestCONNMap.size() =  " << requestCONNMap.size() <<  "\n\n\n" ;

//          std::cout << " requestCONNMap.size() =  " << requestCONNMap.size() <<  "\n\n\n" ;

//        if (iterrr->second->getNumRcvdSymbols() > 0 && test == true) {
//            requestTimer();
//            test = false;
//        }
        index++;
        iterrr++;
    }

}

void Ndp::sendFirstRequest() {
//       std::cout << "  sendFirstRequest  \n";
    bool allEmpty = allPullQueuesEmpty();
//    if (allEmpty == false && test == true) {   // ?????? why test is here
    if (allEmpty == false ) {
         requestTimer();

    //    process_REQUEST_TIMER();
//        test = false;
    }
}

bool Ndp::allPullQueuesEmpty() {
//     std::cout << "  Ndp::allPullQueuesEmpty()    "  << this->getFullPath()   << "\n";
    int pullsQueueLength = 0;
    auto iter = requestCONNMap.begin();
    while (iter !=  requestCONNMap.end()){
//        std::cout << "   aaaaallPullQueuesEmpty   "     << "\n";
         pullsQueueLength = iter->second->getPullsQueueLength();
//         std::cout <<    this->getFullPath()   << " pullsQueueLength=   "  <<   pullsQueueLength<< "\n";

        if (pullsQueueLength > 0) return false;
        ++iter;
    }
      return true;
}

bool Ndp::allConnFinished() {
//     std::cout << "  allConnFinished ?   "     << "\n";
    bool connDone;

    auto iter = requestCONNMap.begin();
    int ii=0;
    while (iter != requestCONNMap.end()) {
        connDone = iter->second->isConnFinished();
//        std::cout << "  allConnFinished ssss  "    << requestCONNMap.size() << "\n";
      if (connDone == false) {
//            std::cout << "allConnFinished FALSE FFFFFFFFFFF, connIndex=  " << ii << " ,numConn = " << requestCONNMap.size() << "\n";
            return false;
        }
        ++iter;
        ++ii;
    }
    cancelRequestTimer();
    return true;
}

void Ndp::updateConnMap() {
    std::cout << "  updateConnMap updateConnMap   "     << "\n";
    a:
    bool connDone;
    auto iter = requestCONNMap.begin();

    while (iter != requestCONNMap.end()) {
        connDone = iter->second->isConnFinished();
        if (connDone == true)  {
            requestCONNMap.erase(iter);
            goto a;
        }
         ++iter;
   }
}

void Ndp::requestTimer() {
    Enter_Method_Silent("requestTimer");
//    std::cout << "  requestTimer  \n";
//  //  state->request_rexmit_count = 0;
//  //  state->request_rexmit_timeout = NDP_TIMEOUT_PULL_REXMIT;  // 3 sec
//    std::cout << " start requestTimer... \n ";
//    EV << " start requestTimer... \n ";
    cancelRequestTimer();
    simtime_t requestTime = (simTime() + SimTime( PACING_TIME , SIMTIME_US)); // pacing
//    if (allConnFinished() == false)
     scheduleAt(requestTime, requestTimerMsg); // 0.000009
//     requestTimerStamps.record(requestTime);

//    if (allConnFinished() == true)
//        cancelRequestTimer();
}

void Ndp::cancelRequestTimer() {
//    std::cout << " cancelRequestTimer  "   << "\n";
    if (requestTimerMsg->isScheduled())
        cancelEvent(requestTimerMsg);
//    delete requestTimerMsg;
}

bool Ndp::getNapState() {
    return nap;
}

void Ndp::process_REQUEST_TIMER() {
//   std::cout << "  \n process_REQUEST_TIMER " << this->getFullPath() << " \n";
    bool sendNewRequest = false;
    auto iter = requestCONNMap.begin();
    bool allEmpty = allPullQueuesEmpty();
    bool allDone = allConnFinished();

    if (allDone == true) {
        cancelRequestTimer();
    } else if (allDone == false && allEmpty == true) {
        ++times;
//         requestTimer(); // ?????????????????????
//        if (times == 50000) {
//            times=0;
//            cancelRequestTimer();
//        }
        nap = true;
    } else if (allDone == false && allEmpty == false) {
        times = 0;
        nap = false;
        while (sendNewRequest != true) {
            if (counter == requestCONNMap.size())
                counter = 0;
            auto iter = requestCONNMap.begin();
            std::advance(iter, counter);
            int pullsQueueLength = iter->second->getPullsQueueLength();
            if (pullsQueueLength > 0) {
                iter->second->sendRequestFromPullsQueue();
                requestTimer();
                sendNewRequest = true;
            }
            ++counter;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Ndp::SockPair& sp)
{
    os << "locSocket=" << sp.localAddr << ":"<< sp.localPort << " "
       << "remSocket=" << sp.remoteAddr << ":" << sp.remotePort;
    return os;
}

std::ostream& operator<<(std::ostream& os, const NDPConnection& conn)
{
    os << "socketId=" << conn.socketId << " ";
    os << "fsmState=" << NDPConnection::stateName(conn.getFsmState()) << " ";
    //os << "connection=" << (conn.getState() == nullptr ? "<empty>" : conn.getState()->str()) << " ";
    //os << "ttl=" << (conn.ttl == -1 ? "<default>" : std::to_string(conn.ttl)) << " ";
    return os;
}

} // namespace ncp
} // namespace inet



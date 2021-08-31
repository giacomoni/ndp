

#include "NdpSinkApp.h"
#include "GenericAppMsgNdp_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
//#include "inet/transportlayer/contract/tcp/TCPCommand_m.h"
#include "../../transportlayer/contract/ndp/NDPCommand_m.h"
//#include "/Volumes/LocalDataHD/m/ma/ma777/Desktop/omnetpp-5.2.1-hpc/omnetpp-5.2.1/samples/inet-myprojects/inet/src/inet/common/ResultFilters.h"
#include "../../transportlayer/contract/ndp/NDPCommand_m.h"

//Preprocessor directives
//#define  ShowOut
#ifdef ShowOut
#define MY_COUT std::cout
#else
#define MY_COUT if(false) std::cout
#endif


namespace inet {
#define SEND_INIT_REQUEST_TO_READ    0

//NdpSinkApp::~NdpSinkApp() {
//    cancelAndDelete(timeoutMsg);
//
//}
Define_Module(NdpSinkApp);
Define_Module(NdpSinkAppThread);

simsignal_t NdpSinkAppThread::rcvdPkSignalNDP = registerSignal("rcvdPk");

simsignal_t fctRecordv3 = NodeStatus::registerSignal("fctRecordv3");
simsignal_t multicastGroupIdSignal =  NodeStatus::registerSignal("multicastGroupIdSignal");
simsignal_t multisourceGroupIdSignal =  NodeStatus::registerSignal("multisourceGroupIdSignal");
simsignal_t numRcvTrimmedHeaderSigNdp = NodeStatus::registerSignal("numRcvTrimmedHeaderSigNdp");

// MOH ADDED
//simsignal_t throughputRecordv1eee = NodeStatus::registerSignal("throughputRecordv1eee");

NdpSinkApp::NdpSinkApp()
{
}

NdpSinkApp::~NdpSinkApp()
{
}

void NdpSinkApp::initialize(int stage)
{
     NdpServerHostApp::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
//    else if (stage == INITSTAGE_APPLICATION_LAYER) {
//        timeoutMsg = new cMessage("timer");
//
//        bool isOperational;
//        NodeStatus *nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
//        isOperational = (!nodeStatus) || nodeStatus->getState() == NodeStatus::UP;
//        if (!isOperational)
//            throw cRuntimeError("This module doesn't support starting in node DOWN state");
//
//        const char *localAddress = par("localAddress");
//        int localPort = par("localPort");
////        MY_COUT << "NdpSinkApp initialize -- localPort =   " << localPort << "\n";
////        MY_COUT << "NdpSinkApp initialize -- isLongFlow =   " << isLongFlow << "\n";
//        gateToNdp = gate("ndpOut"); // MOH for multi sourcing
//        socket.setOutputGate(gate("ndpOut"));
//
//        socket.bind(localAddress[0] ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
//        socket.listen();
//
//         timeoutMsg->setKind(SEND_INIT_REQUEST_TO_READ);
//        scheduleAt(simTime(), timeoutMsg);
//    }

}

void NdpSinkApp::finish()
{
    NdpServerHostApp::finish();
}

void NdpSinkApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes", socketMap.size(), bytesRcvd);
    getDisplayString().setTagArg("t", 0, buf);
} // namespace inet

void NdpSinkAppThread::sendRequest() {
    char msgname[16];
    //sprintf(msgname, "REQUEST-%d",++requestIndex);
    sprintf(msgname, "REQUEST-INIT_READ");

    auto packet = new Packet("REQUEST-INIT_READ");
    const auto& payload = makeShared<GenericAppMsgNdp>();
    payload->setChunkLength(B(10));
    payload->setServerClose(false);
    packet->insertAtFront(payload);
    sock->send(packet);

}

void NdpSinkAppThread::initialize(int stage)
{
    NdpServerThreadBase::initialize(stage);
    isLongFlow = par("isLongFlow");  // moh
//    multiCastGroupId = par("multiCastGroupId");
//    multiSrcGroupId = par("multiSrcGroupId");
    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
}

void NdpSinkAppThread::established()
{
    bytesRcvd = 0;
}

void NdpSinkAppThread::dataArrived(Packet *msg, bool urgent)
{
    if (msg->getKind() == NDP_I_PEER_CLOSED) {
        tEndAdded = simTime();
        NDPCommand *controlInfo = check_and_cast<NDPCommand *>( msg->getControlInfo());

        numRcvTrimmedHeader =  controlInfo->getNumRcvTrimmedHeader();



        std::string mod = "FatTreeNdp.centralSchedulerNdp";
        cModule* centralMod = getModuleByPath(mod.c_str());

//        if (centralMod && bytesRcvd==mm) { // for multi source   ZZZZZZZZZ  for multi-source  use this in the sink  mm =flowSize*1500*numReplicas
     if (centralMod && isLongFlow == false) {
            int   numFinishedFlows = centralMod->par("numCompletedShortFlows");
            int newNumFinishedFlows = numFinishedFlows +1 ;
            centralMod->par("numCompletedShortFlows").setDoubleValue(newNumFinishedFlows);
             MY_COUT << "NdpSinkAppThread::dataArrived  numCompletedShortFlows " << newNumFinishedFlows <<  "\n\n\n";
        }
        delete msg;

        // we close too
//        msg->setName("close");
//        msg->setKind(NDP_C_CLOSE);
      //  send(msg, "ndpOut");  // TODO    we need to use this one
    }
    else if (msg->getKind() == NDP_I_DATA || msg->getKind() == NDP_I_URGENT_DATA) {
        cPacket *pk = PK(msg);
        long packetLength = pk->getByteLength();
//        bytesRcvd += packetLength;
        ++bytesRcvd;
        emit(rcvdPkSignalNDP, pk);
        // Moh added: time stamp when receiving the first data packet (not the SYN, as the app wouldn't get that packet)
        if (firstDataReceived == true) {
             tStartAdded = simTime();
            firstDataReceived = false;
        }
        EV_INFO << "bytesRcvd  " << bytesRcvd <<  " " <<  this->getFullPath() << std::endl;
    } else if (msg->getKind() == NDP_I_ESTABLISHED ){
//        tStartAdded = simTime();
        delete msg;
//          sendRequest();
    }

    else {
        // must be data or some kind of indication -- can be dropped
        delete msg;
    }
}

void NdpSinkAppThread::refreshDisplay() const
{
    std::ostringstream os;
    //os << (sock ? NDPSocket::stateName(sock->getState()) : "NULL_SOCKET") << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

void NdpSinkAppThread::finish()
{
    NdpServerThreadBase::finish();
    // MOH Added
    double throughput = 8 * (double) bytesRcvd / (SIMTIME_DBL(tEndAdded - tStartAdded));
    double FCT = SIMTIME_DBL(tEndAdded - tStartAdded);
     MY_COUT << " FCT:=    " << FCT << "  \n";
     MY_COUT << " isLongFlow:=    " << isLongFlow << "\n";

    // don't emit the FCT of the longFlows(no need), we just observe the shortFlows
    if (isLongFlow == false) {
          emit(fctRecordv3, FCT);
//         emit(multicastGroupIdSignal, multiCastGroupId);
//         emit(multisourceGroupIdSignal, multiSrcGroupId);
         std::cout << " numRcvTrimmedHeader   sink  "   << numRcvTrimmedHeader <<  "\n";
         emit(numRcvTrimmedHeaderSigNdp,numRcvTrimmedHeader );

          MY_COUT << "mmmmmmmmmm NdpSinkApp::finish() bytesRcvd ";
          std::cout << "bytesRcvd: " << bytesRcvd << "  "   << this->getFullPath() <<   "\n\n\n";
    }
}
} // namespace inet

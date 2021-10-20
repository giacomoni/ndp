
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/common/ResultFilters.h"

#include "../../transportlayer/contract/ndp/NdpCommand_m.h"
#include "../../transportlayer/contract/ndp/NdpCommand_m.h"
#include "NdpSinkApp.h"
#include "GenericAppMsgNdp_m.h"

namespace inet {
#define SEND_INIT_REQUEST_TO_READ    0

Define_Module(NdpSinkApp);

simsignal_t NdpSinkApp::rcvdPkSignalNDP = registerSignal("packetReceived");

simsignal_t goodputSigNdp = NodeStatus::registerSignal("goodputSigNdp");
simsignal_t fctRecordv3 = NodeStatus::registerSignal("fctRecordv3");
simsignal_t multicastGroupIdSignal = NodeStatus::registerSignal(
        "multicastGroupIdSignal");
simsignal_t multisourceGroupIdSignal = NodeStatus::registerSignal(
        "multisourceGroupIdSignal");
simsignal_t numRcvTrimmedHeaderSigNdp = NodeStatus::registerSignal(
        "numRcvTrimmedHeaderSigNdp");

void NdpSinkApp::initialize(int stage) {
    cSimpleModule::initialize(stage);
    isBackroundFlow = par("isBackroundFlow");  // moh
    multiCastGroupId = par("multiCastGroupId");
    multiSrcGroupId = par("multiSrcGroupId");
    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    } else if (stage == INITSTAGE_APPLICATION_LAYER) {
        timeoutMsg = new cMessage("timer");

        bool isOperational;
        NodeStatus *nodeStatus = dynamic_cast<NodeStatus*>(findContainingNode(
                this)->getSubmodule("status"));
        isOperational = (!nodeStatus)
                || nodeStatus->getState() == NodeStatus::UP;
        if (!isOperational)
            throw cRuntimeError(
                    "This module doesn't support starting in node DOWN state");
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");
        gateToNdp = gate("socketOut"); // MOH for multi sourcing
        socket.setOutputGate(gate("socketOut"));
        socket.bind(
                localAddress[0] ?
                        L3AddressResolver().resolve(localAddress) : L3Address(),
                localPort);
        socket.listen();
        timeoutMsg->setKind(SEND_INIT_REQUEST_TO_READ);
        scheduleAt(simTime(), timeoutMsg);
    }
}

void NdpSinkApp::handleMessage(cMessage *msg) {
    EV_INFO << "\n\nMESSAGE KIND: " << msg->getKind() << "\n\n";
    if (msg->getKind() == NDP_I_PEER_CLOSED) {
        tEndAdded = simTime();
        NdpCommand *controlInfo = check_and_cast<NdpCommand*>(
                msg->getControlInfo());
        numRcvTrimmedHeader = controlInfo->getNumRcvTrimmedHeader();
        std::string mod = "FatTreeNdp.centralSchedulerNdp";
        cModule *centralMod = getModuleByPath(mod.c_str());
        if (centralMod && isBackroundFlow == false) {
            int numFinishedFlows = centralMod->par("numCompletedShortFlows");
            int newNumFinishedFlows = numFinishedFlows + 1;
            centralMod->par("numCompletedShortFlows").setIntValue(
                    newNumFinishedFlows);
            EV_INFO
                           << "\nNdpSinkApp::handleMessage  numCompletedShortFlows "
                           << newNumFinishedFlows << "\n\n\n";
        }
        delete msg;
    } else if (msg->getKind() == NDP_I_DATA
            || msg->getKind() == NDP_I_URGENT_DATA) {

        Packet *packet = check_and_cast<Packet*>(msg);
        bytesRcvd += packet->getByteLength();
        emit(rcvdPkSignalNDP, packet);
        // Moh added: time stamp when receiving the first data packet (not the SYN, as the app wouldn't get that packet)
        if (firstDataReceived == true) {
            tStartAdded = simTime();
            firstDataReceived = false;
        }
        EV_INFO << "bytesRcvd  " << bytesRcvd << " " << this->getFullPath()
                       << std::endl;
    } else if (msg->getKind() == NDP_I_ESTABLISHED) {
        delete msg;
    }

    else {
        // must be data or some kind of indication -- can be dropped
        delete msg;
    }
}

void NdpSinkApp::finish() {
    double throughput = 8 * (double) bytesRcvd
            / (tEndAdded - tStartAdded).dbl();
    std::cout << "\nTIME: " << (tEndAdded - tStartAdded).dbl();
    double FCT = SIMTIME_DBL(tEndAdded - tStartAdded);
    std::cout << " FCT:=    " << FCT << "  \n";
    std::cout << " isBackroundFlow:=    " << isBackroundFlow << "\n";

    // don't emit the FCT of the background flows(no need), we just observe the shorter length flows
    if (isBackroundFlow == false) {
        emit(fctRecordv3, FCT);
        emit(goodputSigNdp, throughput);
        emit(multicastGroupIdSignal, multiCastGroupId);
        emit(multisourceGroupIdSignal, multiSrcGroupId);
        std::cout << " numRcvTrimmedHeader   sink  " << numRcvTrimmedHeader
                << "\n";
        emit(numRcvTrimmedHeaderSigNdp, numRcvTrimmedHeader);
        std::cout << "mmmmmmmmmm NdpSinkApp::finish() bytesRcvd ";
        std::cout << "bytesRcvd: " << bytesRcvd << "  " << this->getFullPath()
                << "\n\n\n";
    }
}

void NdpSinkApp::refreshDisplay() const {
    std::ostringstream os;
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

#include <string.h>

#include "ndp_common/NdpHeader.h"
#include "Ndp.h"
#include "NdpAlgorithm.h"
#include "NdpConnection.h"
#include "NdpSendQueue.h"
#include "../contract/ndp/NdpCommand_m.h"

namespace inet {

namespace ndp {

//
// Event processing code
//
void NdpConnection::process_OPEN_ACTIVE(NdpEventCode &event, NdpCommand *ndpCommand, cMessage *msg)
{
    NdpOpenCommand *openCmd = check_and_cast<NdpOpenCommand*>(ndpCommand);
    L3Address localAddr, remoteAddr;
    int localPort, remotePort;
    switch (fsm.getState()) {
        case NDP_S_INIT:
            initConnection(openCmd);
            // store local/remote socket
            state->active = true;
            localAddr = openCmd->getLocalAddr();
            remoteAddr = openCmd->getRemoteAddr();
            localPort = openCmd->getLocalPort();
            remotePort = openCmd->getRemotePort();
            state->numPacketsToSend = openCmd->getNumPacketsToSend();
            if (remoteAddr.isUnspecified() || remotePort == -1){
                throw cRuntimeError(ndpMain, "Error processing command OPEN_ACTIVE: remote address and port must be specified");
            }
            if (localPort == -1) {
                localPort = ndpMain->getEphemeralPort();
                EV_DETAIL << "Assigned ephemeral port " << localPort << "\n";
            }
            EV_DETAIL << "process_OPEN_ACTIVE OPEN: " << localAddr << ":" << localPort << " --> " << remoteAddr << ":" << remotePort << endl;
            ndpMain->addSockPair(this, localAddr, remoteAddr, localPort, remotePort);
            sendEstabIndicationToApp();
            sendQueue->init(state->numPacketsToSend, B(1460)); //added B
            sendInitialWindow();
            break;
        default:
            throw cRuntimeError(ndpMain, "Error processing command OPEN_ACTIVE: connection already exists");
    }
    delete openCmd;
    delete msg;
}

void NdpConnection::process_OPEN_PASSIVE(NdpEventCode &event, NdpCommand *ndpCommand, cMessage *msg)
{
    NdpOpenCommand *openCmd = check_and_cast<NdpOpenCommand*>(ndpCommand);
    L3Address localAddr;
    int localPort;
    switch (fsm.getState()) {
        case NDP_S_INIT:
            initConnection(openCmd);
            state->active = false;
            localAddr = openCmd->getLocalAddr();
            localPort = openCmd->getLocalPort();
            if (localPort == -1)
                throw cRuntimeError(ndpMain, "Error processing command OPEN_PASSIVE: local port must be specified");
            EV_DETAIL << "Starting to listen on: " << localAddr << ":" << localPort << "\n";
            ndpMain->addSockPair(this, localAddr, L3Address(), localPort, -1);
            break;
        default:
            throw cRuntimeError(ndpMain, "Error processing command OPEN_PASSIVE: connection already exists");
    }

    delete openCmd;
    delete msg;
}

} // namespace ndp

} // namespace inet


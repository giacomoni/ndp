

import inet.common.INETDefs;
import inet.common.packet.ChunkBuffer;
import inet.common.packet.ChunkQueue;
import inet.common.packet.Packet;
import inet.networklayer.common.L3Address;

cplusplus {{
#include "Ndp.h"
#include "NdpAlgorithm.h"
#include "NdpConnection.h"
#include "NdpSendQueue.h"
#include "ndp_common/NdpHeader.h"
}}

namespace inet::ndp;

class NdpAlgorithm extends cObject { @existingClass; }

struct NdpStateVariables
{
    @existingClass;
    @descriptor(readonly);
    
    bool active;
    
    unsigned int request_id;
    unsigned int internal_request_id;
    bool isHeader;
    uint32 IW;
    bool connFinished;
    uint32 numPacketsToGet;
    uint32 numPacketsToSend;
    bool isSender;
    bool isReceiver;
    unsigned int  priorityValue;


    unsigned int numRcvdPkt;
    unsigned int numRcvTrimmedHeader;


    uint32 numberReceivedPackets;
    uint32 numberSentPackets;

    bool connNotAddedYet;
    bool isfinalReceivedPrintedOut;
};

class NdpSendQueue extends cObject
{
    @existingClass;
    @descriptor(readonly);
    cPacketQueue dataToSendQueue;      // dataBuffer
    cPacketQueue sentDataQueue;
}

class NdpConnection extends cObject
{
    @existingClass;
    @descriptor(readonly);

    int socketId;    // identifies connection within the app
    int listeningSocketId;    // identifies listening connection within the app

    // socket pair
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;

    NdpStateVariables *state;

    // NDP queues
    NdpSendQueue *sendQueue;

    NdpAlgorithm *ndpAlgorithm;
    int fsmState;
};


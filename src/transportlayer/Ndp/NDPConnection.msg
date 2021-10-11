

import inet.common.INETDefs;
import inet.common.packet.ChunkBuffer;
import inet.common.packet.ChunkQueue;
import inet.common.packet.Packet;
import inet.networklayer.common.L3Address;

cplusplus {{
#include "Ndp.h"
#include "NDPAlgorithm.h"
#include "NDPConnection.h"
#include "NDPReceiveQueue.h"
#include "NDPSendQueue.h"
#include "ndp_common/NdpHeader.h"
}}

namespace inet::ndp;

class NDPAlgorithm extends cObject { @existingClass; }

struct NdpStateVariables
{
    @existingClass;
    @descriptor(readonly);
    
    bool active;
    //bool fork;
    
    unsigned int request_id;
    unsigned int internal_request_id;
    bool isLongFlow;
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

    int request_rexmit_count;

    simtime_t request_rexmit_timeout;
    uint32 numPullsTimeOuts;
    bool connNotAddedYet;
    bool isfinalReceivedPrintedOut;

    uint32 snd_mss; 
    uint32 iss;
    uint32 irs;

    int syn_rexmit_count; 
    simtime_t syn_rexmit_timeout;
};

class NDPSendQueue extends cObject
{
    @existingClass;
    @descriptor(readonly);
    cPacketQueue dataToSendQueue;      // dataBuffer
    cPacketQueue sentDataQueue;
}

class NDPReceiveQueue extends cObject
{
    @existingClass;
    @descriptor(readonly);
    ReorderBuffer reorderBuffer;
}

class NDPConnection extends cObject
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

    // TCP queues
    NDPSendQueue *sendQueue;
    NDPReceiveQueue *receiveQueue;

    NDPAlgorithm *ndpAlgorithm;
    int fsmState;
};




import inet.common.INETDefs;
import inet.networklayer.common.IpProtocolId;
import inet.networklayer.common.L3Address;

namespace inet;
//
// NDPR command codes, sent by the application to NDPR. These constants
// should be set as message kind on a message sent to the NDPR entity.
//
// @see ~NDPRCommand, ~NDPROpenCommand, ~IRaptoNDP
//
enum NdpCommandCode
{
    NDP_C_OPEN_ACTIVE = 1;   // active open (must carry ~NDPOpenCommand)
    NDP_C_OPEN_PASSIVE = 2;  // passive open (must carry ~NDPOpenCommand)
    NDP_C_ACCEPT = 3;
    NDP_C_SEND = 4;          // send data (set on data packet)
    NDP_C_CLOSE = 5;         // "I have no more data to send"
    NDP_C_ABORT = 6;         // abort connection
}

//
// NDP indications, sent by NDP to the application. NDP will set these
// constants as message kind on messages it sends to the application.
//
// @see ~NDPCommand, ~NDPStatusInfo, ~INDP
//
enum NdpStatusInd
{
    NDP_I_DATA = 1;              // data packet (set on data packet)
    NDP_I_AVAILABLE = 3;         // conncetion available
    NDP_I_ESTABLISHED = 4;       // connection established
    NDP_I_PEER_CLOSED = 5;       // FIN received from remote NDP
    NDP_I_CLOSED = 6;            // connection closed normally (via FIN exchange)
}

class NdpCommand extends cObject
{
   int userId = -1;	// id than can be freely used by the app
   unsigned int  numRcvTrimmedHeader = 0;   
}

class NdpOpenCommand extends NdpCommand
{
    L3Address localAddr; 
    L3Address remoteAddr;
    int localPort = -1;      
    int remotePort = -1;      
    string ndpAlgorithmClass;
    unsigned int numPacketsToSend;
}

class NdpAvailableInfo extends NdpCommand
{
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
    int newSocketId;
}

class NdpConnectInfo extends NdpCommand
{
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
}

class NdpStatusInfo extends NdpCommand
{
    int state;
    string stateName;
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
}

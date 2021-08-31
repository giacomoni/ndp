

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
enum NDPCommandCode
{
    NDP_C_OPEN_ACTIVE = 1;   // active open (must carry ~NDPOpenCommand)
    NDP_C_OPEN_PASSIVE = 2;  // passive open (must carry ~NDPOpenCommand)
    NDP_C_ACCEPT = 3;
    NDP_C_SEND = 4;          // send data (set on data packet)
    NDP_C_CLOSE = 5;         // "I have no more data to send"
    NDP_C_ABORT = 6;         // abort connection
    NDP_C_STATUS = 7;        // request status info (NDP_I_STATUS) from NDP
    NDP_C_QUEUE_BYTES_LIMIT = 8; // set send queue limit (in bytes)
    NDP_C_READ = 9;       // send request to NDP to deliver data
    NDP_C_DESTROY = 10;      // send request to NDP to destroy the socket descriptor
    NDP_SETOPTION = 11;    // setting NDP socket options
}


//
// NDP indications, sent by NDP to the application. NDP will set these
// constants as message kind on messages it sends to the application.
//
// @see ~NDPCommand, ~NDPStatusInfo, ~INDP
//
enum NDPStatusInd
{
    NDP_I_DATA = 1;              // data packet (set on data packet)
    NDP_I_URGENT_DATA = 2;       // urgent data (set on data packet)
    NDP_I_AVAILABLE = 3;         // conncetion available
    NDP_I_ESTABLISHED = 4;       // connection established
    NDP_I_PEER_CLOSED = 5;       // FIN received from remote NDP
    NDP_I_CLOSED = 6;            // connection closed normally (via FIN exchange)
    NDP_I_CONNECTION_REFUSED = 7; // connection refused
    NDP_I_CONNECTION_RESET = 8;  // connection reset
    NDP_I_TIMED_OUT = 9;         // conn-estab timer went off, or max retransm. count reached
    NDP_I_STATUS = 10;            // status info (will carry ~NDPStatusInfo)
    NDP_I_SEND_MSG = 11;         // send queue abated, send more messages
    NDP_I_DATA_NOTIFICATION = 12; // notify the upper layer that data has arrived
}


//
// Currently not in use.
//
enum NDPErrorCode
{
}


class NDPCommand extends cObject
{
    int connId = -1;   // identifies the socket within the application
    int userId = -1;   // id than can be freely used by the app
 
   unsigned int  numRcvTrimmedHeader = 0;   
}


class NDPErrorInfo extends NDPCommand
{
    int errorCode @enum(NDPErrorCode);
    string messageText;
}


class NDPOpenCommand extends NDPCommand
{
    L3Address localAddr; 
    L3Address remoteAddr;
    int localPort = -1;      
    int remotePort = -1;      

    string ndpAlgorithmClass; 
    
    unsigned int priorityValue;
    unsigned int numPacketsToSend;
    bool    isLongFlow;
    bool isSender;
    bool isReceiver;
}

class NDPAcceptCommand extends NDPCommand
{
}


class NDPSendCommand extends NDPCommand
{
}

class NDPAvailableInfo extends NDPCommand
{
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
    int newSocketId;
}

class NDPConnectInfo extends NDPCommand
{
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
}


class NDPStatusInfo extends NDPCommand
{
    int state;
    string stateName;

    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;

    unsigned int snd_mss;
  
}


#ifndef __INET_NDPCONNECTION_H
#define __INET_NDPCONNECTION_H

#include "../../transportlayer/Ndp/Ndp.h"
#include "ndp_common/NdpHeader.h"
#include "inet/common/INETDefs.h"
#include <queue>
#include "inet/networklayer/common/L3Address.h"
#include "inet/common/packet/ChunkQueue.h"
namespace inet {

class NDPCommand;
class NDPOpenCommand;

namespace ndp {

class NdpHeader;
class NDPSendQueue;
class NDPReceiveQueue;
class NDPAlgorithm;

enum NDPState {
    NDP_S_INIT = 0,
    NDP_S_CLOSED = FSM_Steady(1),
    NDP_S_LISTEN = FSM_Steady(2),
    NDP_S_SYN_SENT = FSM_Steady(3),
    NDP_S_SYN_RCVD = FSM_Steady(4),
    NDP_S_ESTABLISHED = FSM_Steady(5),
    NDP_S_CLOSE_WAIT = FSM_Steady(6),
    NDP_S_LAST_ACK = FSM_Steady(7),
    NDP_S_FIN_WAIT_1 = FSM_Steady(8),
    NDP_S_FIN_WAIT_2 = FSM_Steady(9),
    NDP_S_CLOSING = FSM_Steady(10),
    NDP_S_TIME_WAIT = FSM_Steady(11)
};

//
// Event, strictly for the FSM state transition purposes.
// DO NOT USE outside performStateTransition()!
//
enum NDPEventCode {
    NDP_E_IGNORE,

    // app commands
    // (Note: no RECEIVE command, data are automatically passed up)
    NDP_E_OPEN_ACTIVE,
    NDP_E_OPEN_PASSIVE,
    NDP_E_SEND,
    NDP_E_CLOSE,
    NDP_E_ABORT,
    NDP_E_DESTROY,
    NDP_E_STATUS,
    NDP_E_QUEUE_BYTES_LIMIT,
    NDP_E_READ,
    NDP_E_SETOPTION,

    // TPDU types
    NDP_E_RCV_DATA,
    NDP_E_RCV_ACK,
    NDP_E_RCV_SYN,
    NDP_E_RCV_SYN_ACK,
    NDP_E_RCV_FIN,
    NDP_E_RCV_FIN_ACK,
    NDP_E_RCV_RST,    // covers RST+ACK too

    NDP_E_RCV_UNEXP_SYN,    // unexpected SYN

    // timers
    NDP_E_TIMEOUT_2MSL,    // RFC 793, a.k.a. TIME-WAIT timer
    NDP_E_TIMEOUT_CONN_ESTAB,
    NDP_E_TIMEOUT_FIN_WAIT_2,

// All other timers (REXMT, PERSIST, DELAYED-ACK, KEEP-ALIVE, etc.),
// are handled in NDPAlgorithm.
};

/** @name Timeout values */
//@{
#define NDP_TIMEOUT_CONN_ESTAB        75  // 75 seconds
#define NDP_TIMEOUT_FIN_WAIT_2        600  // 10 minutes
#define NDP_TIMEOUT_2MSL              240  // 2 * 2 minutes
#define NDP_TIMEOUT_SYN_REXMIT        3  // initially 3 seconds

#define NDP_TIMEOUT_PULL_REXMIT        0.5  // initially 500 msec  MOH

#define NDP_TIMEOUT_SYN_REXMIT_MAX    240  // 4 mins (will only be used with SYN+ACK: with SYN CONN_ESTAB occurs sooner)
//@}

#define MAX_SYN_REXMIT_COUNT          12  // will only be used with SYN+ACK: with SYN CONN_ESTAB occurs sooner
#define NDP_MAX_WIN                   65535  // 65535 bytes, largest value (16 bit) for (unscaled) window size
#define DUPTHRESH                     3  // used for NDPTahoe, NDPReno and SACK (RFC 3517)
#define PAWS_IDLE_TIME_THRESH         (24 * 24 * 3600)  // 24 days in seconds (RFC 1323)

//typedef std::list<Sack> SackList;

/**
 * Contains state variables ("TCB") for NDP.
 *
 * NDPStateVariables is effectively a "struct" -- it only contains
 * public data members. (Only declared as a class so that we can use
 * cObject as base class and make it possible to inspect
 * it in Tkenv.)
 *
 * NDPStateVariables only contains variables needed to implement
 * the "base" (RFC 793) NDP. More advanced NDP variants are encapsulated
 * into NDPAlgorithm subclasses which can have their own state blocks,
 * subclassed from NDPStateVariables. See NDPAlgorithm::createStateVariables().
 */
class INET_API NdpStateVariables: public cObject {
public:
    NdpStateVariables();
    virtual std::string str() const override;
    virtual std::string detailedInfo() const OMNETPP5_CODE(override);

public:
    bool active;    // set if the connection was initiated by an active open

    unsigned int request_id;
    unsigned int internal_request_id;
    bool isLongFlow;
    bool isHeader;

    uint32 IW;  //initial window size
    bool connFinished;
    uint32 numPacketsToGet;
    uint32 numPacketsToSend;
    bool isSender;
    bool isReceiver;
    unsigned int priorityValue;

    unsigned int numRcvdPkt;
    unsigned int numRcvTrimmedHeader;

    uint32 numberReceivedPackets;
    uint32 numberSentPackets;

    int request_rexmit_count; // number of SYN/SYN+ACK retransmissions (=1 after first rexmit)

    simtime_t request_rexmit_timeout;  // current request retransmission timeout
    uint32 numPullsTimeOuts;
    bool connNotAddedYet;
    bool isfinalReceivedPrintedOut;

    uint32 snd_mss; // sender maximum segment size (without headers, i.e. only segment text); see RFC 2581, page 1.
                    // This will be set to the minimum of the local smss parameter and the value specified in the
                    // MSS option received during connection setup.

                    // send sequence number variables (see RFC 793, "3.2. Terminology")

    uint32 iss;    // initial sequence number (ISS)
    uint32 irs;        // initial receive sequence number

    // SYN, SYN+ACK retransmission variables (handled separately
    // because normal rexmit belongs to NDPAlgorithm)
    int syn_rexmit_count; // number of SYN/SYN+ACK retransmissions (=1 after first rexmit)
    simtime_t syn_rexmit_timeout;  // current SYN/SYN+ACK retransmission timeout
};

class INET_API NDPConnection: public cSimpleModule {
public:

    struct PacketsToSend {
        unsigned int pktId;
        Packet *msg;
    };
    typedef std::list<PacketsToSend> PacketsList;
//    PacketsList sentPacketsList;
    PacketsList receivedPacketsList;

    // connection identification by apps: socketId
    int socketId = -1;    // identifies connection within the app
    int getSocketId() const {
        return socketId;
    }
    void setSocketId(int newSocketId) {
        ASSERT(socketId == -1);
        socketId = newSocketId;
    }

    int listeningSocketId = -1; // identifies listening connection within the app
    int getListeningSocketId() const {
        return listeningSocketId;
    }

    // socket pair
    L3Address localAddr;
    const L3Address& getLocalAddr() const {
        return localAddr;
    }
    L3Address remoteAddr;
    const L3Address& getRemoteAddr() const {
        return remoteAddr;
    }
    int localPort = -1;
    int remotePort = -1;

    //NDP options for this connection
    int ttl = -1;
//    int ClientOrServerSel=10;
protected:
    Ndp *ndpMain = nullptr;    // NDP module

    // NDP state machine
    cFSM fsm;

    // variables associated with NDP state
    NdpStateVariables *state = nullptr;

    // NDP queues
    NDPSendQueue *sendQueue = nullptr;
    NDPSendQueue* getSendQueue() const {
        return sendQueue;
    }
    NDPReceiveQueue *receiveQueue = nullptr;
    NDPReceiveQueue* getReceiveQueue() const {
        return receiveQueue;
    }

public:
    // NDPSACKRexmitQueue *rexmitQueue = nullptr;
    virtual int getNumRcvdPackets();
    virtual bool isConnFinished();
    virtual void setConnFinished();

protected:
    //cQueue pullQueue;
    cPacketQueue pullQueue;
    // NDP behavior in data transfer state
    NDPAlgorithm *ndpAlgorithm = nullptr;
    NDPAlgorithm* getNdpAlgorithm() const {
        return ndpAlgorithm;
    }
    // timers
    cMessage *requestInternalTimer = nullptr;

    cMessage *the2MSLTimer = nullptr;
    cMessage *connEstabTimer = nullptr;
    cMessage *finWait2Timer = nullptr;
    cMessage *synRexmitTimer = nullptr;    // for retransmitting SYN and SYN+ACK

    // statistics

protected:
    /** @name FSM transitions: analysing events and executing state transitions */
    //@{
    /** Maps app command codes (msg kind of app command msgs) to NDP_E_xxx event codes */
    virtual NDPEventCode preanalyseAppCommandEvent(int commandCode);
    /** Implemements the pure NDP state machine */
    virtual bool performStateTransition(const NDPEventCode &event);
    /** Perform cleanup necessary when entering a new state, e.g. cancelling timers */
    virtual void stateEntered(int state, int oldState, NDPEventCode event);
    //@}

    /** @name Processing app commands. Invoked from processAppCommand(). */
    //@{
    virtual void process_OPEN_ACTIVE(NDPEventCode &event,
            NDPCommand *NDPCommand, cMessage *msg);
    virtual void process_OPEN_PASSIVE(NDPEventCode &event,
            NDPCommand *NDPCommand, cMessage *msg);

    /**
     * Process incoming NDP segment. Returns a specific event code (e.g. NDP_E_RCV_SYN)
     * which will drive the state machine.
     */
    virtual NDPEventCode process_RCV_SEGMENT(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);
    virtual NDPEventCode processSegmentInListen(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);

    virtual NDPEventCode processSegment1stThru8th(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg);

    //@}

    /** @name Processing timeouts. Invoked from processTimer(). */
    //@{
    virtual void process_TIMEOUT_2MSL();
    virtual void process_TIMEOUT_CONN_ESTAB();
    virtual void process_TIMEOUT_FIN_WAIT_2();
    //@}

    /** Utility: clone a listening connection. Used for forking. */
    //virtual NDPConnection *cloneListeningConnection();
    //virtual void initClonedConnection(NDPConnection *listenerConn);
    /** Utility: creates send/receive queues and NDPAlgorithm */
    virtual void initConnection(NDPOpenCommand *openCmd);

    /** Utility: set snd_mss, rcv_wnd and sack in newly created state variables block */
    virtual void configureStateVariables();

    /** Utility: generates ISS and initializes corresponding state variables */
    virtual void selectInitialSeqNum();

    /** Utility: returns true if the connection is not yet accepted by the application */
    virtual bool isToBeAccepted() const {
        return listeningSocketId != -1;
    }
public:
    virtual void sendAckNdp(unsigned int AckNum); // MOH: HAS BEEN ADDED

    virtual void sendNackNdp(unsigned int nackNum); // MOH: HAS BEEN ADDED
    virtual void sendInitialWindow();

    /** Utility: sends RST; does not use connection state */
    virtual void sendRst(uint32 seq, L3Address src, L3Address dest, int srcPort,
            int destPort);
    /** Utility: sends RST+ACK; does not use connection state */
    virtual void sendRstAck(uint32 seq, uint32 ack, L3Address src,
            L3Address dest, int srcPort, int destPort);

    /** Utility: adds control info to segment and sends it to IP */
    virtual void sendToIP(Packet *packet, const Ptr<NdpHeader> &ndpseg);
    virtual void addRequestToPullsQueue();
    virtual void sendRequestFromPullsQueue();

    virtual int getPullsQueueLength();
    /** Utility: signal to user that connection timed out */
    virtual void signalConnectionTimeout();

    /** Utility: start a timer */
    void scheduleTimeout(cMessage *msg, simtime_t timeout) {
        ndpMain->scheduleAt(simTime() + timeout, msg);
    }

protected:
    /** Utility: cancel a timer */
    cMessage* cancelEvent(cMessage *msg) {
        return ndpMain->cancelEvent(msg);
    }

    /** Utility: send IP packet */
    virtual void sendToIP(Packet *pkt, const Ptr<NdpHeader> &ndpseg,
            L3Address src, L3Address dest);

    /** Utility: sends packet to application */
    virtual void sendToApp(cMessage *msg);

    /** Utility: sends status indication (NDP_I_xxx) to application */
    virtual void sendIndicationToApp(int code, const int id = 0);

    /** Utility: sends NDP_I_ESTABLISHED indication with NDPConnectInfo to application */
    virtual void sendEstabIndicationToApp();

public:
    /** Utility: prints local/remote addr/port and app gate index/connId */
    virtual void printConnBrief() const;
    /** Utility: prints important header fields */
    static void printSegmentBrief(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg);
    /** Utility: returns name of NDP_S_xxx constants */
    static const char* stateName(int state);
    /** Utility: returns name of NDP_E_xxx constants */
    static const char* eventName(int event);
    /** Utility: returns name of NDP_I_xxx constants */
    static const char* indicationName(int code);

public:
    NDPConnection() {
    }
    NDPConnection(const NDPConnection &other) {
    }    //FIXME kludge
    void initialize() {
    }

    /**
     * The "normal" constructor.
     */
    void initConnection(Ndp *mod, int socketId);

    /**
     * Destructor.
     */
    virtual ~NDPConnection();

    int getLocalPort() const {
        return localPort;
    }
    L3Address getLocalAddress() const {
        return localAddr;
    }

    int getRemotePort() const {
        return remotePort;
    }
    L3Address getRemoteAddress() const {
        return remoteAddr;
    }

    virtual void segmentArrivalWhileClosed(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);

    /** @name Various getters **/
    //@{
    int getFsmState() const {
        return fsm.getState();
    }
    NdpStateVariables* getState() {
        return state;
    }
    NDPSendQueue* getSendQueue() {
        return sendQueue;
    }
    // NDPSACKRexmitQueue *getRexmitQueue() { return rexmitQueue; }
    NDPReceiveQueue* getReceiveQueue() {
        return receiveQueue;
    }
    NDPAlgorithm* getNdpAlgorithm() {
        return ndpAlgorithm;
    }
    Ndp* getNDPMain() {
        return ndpMain;
    }

    virtual bool processTimer(cMessage *msg);

    virtual bool processNDPSegment(Packet *packet,
            const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr,
            L3Address destAddr);

    virtual bool processAppCommand(cMessage *msg);

    virtual void handleMessage(cMessage *msg);

    /**
     * Utility: converts a given simtime to a timestamp (TS).
     */
    static uint32 convertSimtimeToTS(simtime_t simtime);

    /**
     * Utility: converts a given timestamp (TS) to a simtime.
     */
    static simtime_t convertTSToSimtime(uint32 timestamp);

};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_NDPCONNECTION_H


#ifndef __INET_NdpConnection_H
#define __INET_NdpConnection_H

#include <inet/common/INETDefs.h>
#include <inet/networklayer/common/L3Address.h>
#include <inet/common/packet/ChunkQueue.h>
#include <queue>

#include "ndp_common/NdpHeader.h"
#include "../../transportlayer/Ndp/Ndp.h"

namespace inet {

class NdpCommand;
class NdpOpenCommand;

namespace ndp {

class NdpHeader;
class NdpSendQueue;
class NdpAlgorithm;

enum NdpState
{
    NDP_S_INIT = 0, NDP_S_CLOSED = FSM_Steady(1), NDP_S_LISTEN = FSM_Steady(2), NDP_S_SYN_SENT = FSM_Steady(3), NDP_S_SYN_RCVD = FSM_Steady(4), NDP_S_ESTABLISHED = FSM_Steady(5),
};

//
// Event, strictly for the FSM state transition purposes.
// DO NOT USE outside performStateTransition()!
//
enum NdpEventCode
{
    NDP_E_IGNORE,

    // app commands
    NDP_E_OPEN_ACTIVE,
    NDP_E_OPEN_PASSIVE,
    NDP_E_RCV_DATA,
    NDP_E_RCV_SYN,
};

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
 * into NdpAlgorithm subclasses which can have their own state blocks,
 * subclassed from NDPStateVariables. See NdpAlgorithm::createStateVariables().
 */
class INET_API NdpStateVariables : public cObject
{
public:
    NdpStateVariables();
    virtual std::string str() const override;
    virtual std::string detailedInfo() const OMNETPP5_CODE(override);

public:
    bool active;    // set if the connection was initiated by an active open
    bool delayedNack;
    unsigned int request_id;
    unsigned int internal_request_id;

    int IW;  //initial window size
    bool connFinished;
    int numPacketsToGet;
    int numPacketsToSend;

    unsigned int numRcvdPkt;
    unsigned int numRcvTrimmedHeader;

    int numberReceivedPackets;
    int numberSentPackets;

    bool connNotAddedYet;
    bool isfinalReceivedPrintedOut;
};

class INET_API NdpConnection : public cSimpleModule
{
public:

    struct PacketsToSend
    {
        unsigned int pktId;
        Packet *msg;
    };
    typedef std::list<PacketsToSend> PacketsList;
    PacketsList receivedPacketsList;
    // connection identification by apps: socketId
    int socketId = -1;    // identifies connection within the app
    int getSocketId() const
    {
        return socketId;
    }
    void setSocketId(int newSocketId)
    {
        ASSERT(socketId == -1);
        socketId = newSocketId;
    }

    int listeningSocketId = -1; // identifies listening connection within the app
    int getListeningSocketId() const
    {
        return listeningSocketId;
    }

    // socket pair
    L3Address localAddr;
    const L3Address& getLocalAddr() const
    {
        return localAddr;
    }
    L3Address remoteAddr;
    const L3Address& getRemoteAddr() const
    {
        return remoteAddr;
    }
    int localPort = -1;
    int remotePort = -1;
protected:
    Ndp *ndpMain = nullptr;    // NDP module

    // NDP state machine
    cFSM fsm;

    // variables associated with NDP state
    NdpStateVariables *state = nullptr;

    // NDP queues
    NdpSendQueue *sendQueue = nullptr;
    NdpSendQueue* getSendQueue() const
    {
        return sendQueue;
    }

public:
    virtual int getNumRcvdPackets();
    virtual bool isConnFinished();
    virtual void setConnFinished();

protected:
    //cQueue pullQueue;
    cPacketQueue pullQueue;
    // NDP behavior in data transfer state
    NdpAlgorithm *ndpAlgorithm = nullptr;
    NdpAlgorithm* getNdpAlgorithm() const
    {
        return ndpAlgorithm;
    }

protected:
    /** @name FSM transitions: analysing events and executing state transitions */
    //@{
    /** Maps app command codes (msg kind of app command msgs) to NDP_E_xxx event codes */
    virtual NdpEventCode preanalyseAppCommandEvent(int commandCode);
    /** Implemements the pure NDP state machine */
    virtual bool performStateTransition(const NdpEventCode &event);
    /** Perform cleanup necessary when entering a new state, e.g. cancelling timers */
    virtual void stateEntered(int state, int oldState, NdpEventCode event);
    //@}

    /** @name Processing app commands. Invoked from processAppCommand(). */
    //@{
    virtual void process_OPEN_ACTIVE(NdpEventCode &event, NdpCommand *NdpCommand, cMessage *msg);
    virtual void process_OPEN_PASSIVE(NdpEventCode &event, NdpCommand *NdpCommand, cMessage *msg);

    /**
     * Process incoming NDP segment. Returns a specific event code (e.g. NDP_E_RCV_SYN)
     * which will drive the state machine.
     */
    virtual NdpEventCode process_RCV_SEGMENT(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);
    virtual NdpEventCode processSegmentInListen(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);

    virtual NdpEventCode processSegment1stThru8th(Packet *packet, const Ptr<const NdpHeader> &ndpseg);

    //@}
    /** Utility: clone a listening connection. Used for forking. */
    //virtual NdpConnection *cloneListeningConnection();
    //virtual void initClonedConnection(NdpConnection *listenerConn);
    /** Utility: creates send/receive queues and NdpAlgorithm */
    virtual void initConnection(NdpOpenCommand *openCmd);

    /** Utility: set snd_mss, rcv_wnd and sack in newly created state variables block */
    virtual void configureStateVariables();

    /** Utility: returns true if the connection is not yet accepted by the application */
    virtual bool isToBeAccepted() const
    {
        return listeningSocketId != -1;
    }
public:
    virtual void sendAckNdp(unsigned int AckNum); // MOH: HAS BEEN ADDED

    virtual void sendNackNdp(unsigned int nackNum); // MOH: HAS BEEN ADDED
    virtual void sendInitialWindow();

    /** Utility: adds control info to segment and sends it to IP */
    virtual void sendToIP(Packet *packet, const Ptr<NdpHeader> &ndpseg);
    virtual void addRequestToPullsQueue();
    virtual void sendRequestFromPullsQueue();

    virtual int getPullsQueueLength();

    /** Utility: start a timer */
    void scheduleTimeout(cMessage *msg, simtime_t timeout)
    {
        ndpMain->scheduleAt(simTime() + timeout, msg);
    }

protected:
    /** Utility: cancel a timer */
    cMessage* cancelEvent(cMessage *msg)
    {
        return ndpMain->cancelEvent(msg);
    }

    /** Utility: send IP packet */
    virtual void sendToIP(Packet *pkt, const Ptr<NdpHeader> &ndpseg, L3Address src, L3Address dest);

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
    static void printSegmentBrief(Packet *packet, const Ptr<const NdpHeader> &ndpseg);
    /** Utility: returns name of NDP_S_xxx constants */
    static const char* stateName(int state);
    /** Utility: returns name of NDP_E_xxx constants */
    static const char* eventName(int event);
    /** Utility: returns name of NDP_I_xxx constants */
    static const char* indicationName(int code);

public:
    NdpConnection()
    {
    }
    NdpConnection(const NdpConnection &other)
    {
    }
    void initialize()
    {
    }

    /**
     * The "normal" constructor.
     */
    void initConnection(Ndp *mod, int socketId);

    /**
     * Destructor.
     */
    virtual ~NdpConnection();

    int getLocalPort() const
    {
        return localPort;
    }
    L3Address getLocalAddress() const
    {
        return localAddr;
    }

    int getRemotePort() const
    {
        return remotePort;
    }
    L3Address getRemoteAddress() const
    {
        return remoteAddr;
    }

    virtual void segmentArrivalWhileClosed(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address src, L3Address dest);

    /** @name Various getters **/
    //@{
    int getFsmState() const
    {
        return fsm.getState();
    }
    NdpStateVariables* getState()
    {
        return state;
    }
    NdpSendQueue* getSendQueue()
    {
        return sendQueue;
    }
    NdpAlgorithm* getNdpAlgorithm()
    {
        return ndpAlgorithm;
    }
    Ndp* getNDPMain()
    {
        return ndpMain;
    }

    virtual bool processTimer(cMessage *msg);

    virtual bool processNDPSegment(Packet *packet, const Ptr<const NdpHeader> &ndpseg, L3Address srcAddr, L3Address destAddr);

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

#endif // ifndef __INET_NdpConnection_H


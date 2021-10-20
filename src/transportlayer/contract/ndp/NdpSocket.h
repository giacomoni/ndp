#ifndef __NDP_NdpSocket_H
#define __NDP_NdpSocket_H

#include "inet/common/INETDefs.h"
#include "inet/common/packet/ChunkQueue.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/common/socket/ISocket.h"
#include "NdpCommand_m.h"

namespace inet {

class NdpStatusInfo;

class INET_API NdpSocket: public ISocket {
public:
    /**
     * Abstract base class for your callback objects. See setCallbackObject()
     * and processMessage() for more info.
     *
     * Note: this class is not subclassed from cObject, because
     * classes may have both this class and cSimpleModule as base class,
     * and cSimpleModule is already a cObject.
     */
    class INET_API ICallback {
    public:
        virtual ~ICallback() {
        }
        /**
         * Notifies about data arrival, packet ownership is transferred to the callee.
         */
        virtual void socketDataArrived(NdpSocket *socket, Packet *packet,
                bool urgent) = 0;
        virtual void socketAvailable(NdpSocket *socket,
                NdpAvailableInfo *availableInfo) = 0;
        virtual void socketEstablished(NdpSocket *socket) = 0;
        virtual void socketPeerClosed(NdpSocket *socket) = 0;
        virtual void socketClosed(NdpSocket *socket) = 0;
        virtual void socketFailure(NdpSocket *socket, int code) = 0;
        virtual void socketStatusArrived(NdpSocket *socket,
                NdpStatusInfo *status) = 0;
        virtual void socketDeleted(NdpSocket *socket) = 0;
    };

    class INET_API ReceiveQueueBasedCallback: public ICallback {
    public:
        virtual void socketDataArrived(NdpSocket *socket) = 0;

        virtual void socketDataArrived(NdpSocket *socket, Packet *packet,
                bool urgent) override {
            socket->getReceiveQueue()->push(packet->peekData());
            delete packet;
            socketDataArrived(socket);
        }
    };

    enum State {
        NOT_BOUND,
        BOUND,
        LISTENING,
        CONNECTING,
        CONNECTED,
        PEER_CLOSED,
        LOCALLY_CLOSED,
        CLOSED,
        SOCKERROR
    };

protected:
    int connId = -1;
    State sockstate = NOT_BOUND;

    L3Address localAddr;
    int localPrt = -1;
    L3Address remoteAddr;
    int remotePrt = -1;

    ICallback *cb = nullptr;
    void *userData = nullptr;
    cGate *gateToNdp = nullptr;
    std::string ndpAlgorithmClass;

    ChunkQueue *receiveQueue = nullptr;
protected:
    void sendToNDP(cMessage *msg, int c = -1);

    // internal: implementation behind listen() and listenOnce()
    void listen(bool fork);

public:
    /**
     * Constructor. The getConnectionId() method returns a valid Id right after
     * constructor call.
     */
    NdpSocket();

    /**
     * Constructor, to be used with forked sockets (see listen()).
     * The new connId will be picked up from the message: it should have
     * arrived from NDP and contain NDPCommmand control info.
     */
    NdpSocket(cMessage *msg);

    /**
     * Constructor, to be used with forked sockets (see listen()).
     */
    NdpSocket(NdpAvailableInfo *availableInfo);

    /**
     * Destructor
     */
    ~NdpSocket();

    /**
     * Returns the internal connection Id. NDP uses the (gate index, connId) pair
     * to identify the connection when it receives a command from the application
     * (or NdpSocket).
     */
    int getSocketId() const override {
        return connId;
    }

    ChunkQueue* getReceiveQueue() {
        if (receiveQueue == nullptr)
            receiveQueue = new ChunkQueue();
        return receiveQueue;
    }

    void* getUserData() const {
        return userData;
    }
    void setUserData(void *userData) {
        this->userData = userData;
    }
    /**
     * Returns the socket state, one of NOT_BOUND, CLOSED, LISTENING, CONNECTING,
     * CONNECTED, etc. Messages received from NDP must be routed through
     * processMessage() in order to keep socket state up-to-date.
     */
    NdpSocket::State getState() {
        return sockstate;
    }

    /**
     * Returns name of socket state code returned by getState().
     */
    static const char* stateName(NdpSocket::State state);

    void setState(NdpSocket::State state) {
        sockstate = state;
    }
    ;

    /** @name Getter functions */
    //@{
    L3Address getLocalAddress() {
        return localAddr;
    }
    int getLocalPort() {
        return localPrt;
    }
    L3Address getRemoteAddress() {
        return remoteAddr;
    }
    int getRemotePort() {
        return remotePrt;
    }
    //@}

    /** @name Opening and closing connections, sending data */
    //@{
    /**
     * Sets the gate on which to send to NDP. Must be invoked before socket
     * can be used. Example: <tt>socket.setOutputGate(gate("raptondpOut"));</tt>
     */
    void setOutputGate(cGate *toNdp) {
        gateToNdp = toNdp;
    }

    /**
     * Bind the socket to a local port number.
     */
    void bind(int localPort);

    /**
     * Bind the socket to a local port number and IP address (useful with
     * multi-homing).
     */
    void bind(L3Address localAddr, int localPort);

    /**
     * Returns the current ndpAlgorithmClass parameter.
     */
    const char* getNdpAlgorithmClass() const {
        return ndpAlgorithmClass.c_str();
    }

    /**
     * Sets the ndpAlgorithmClass parameter of the next connect() or listen() call.
     */
    void setNdpAlgorithmClass(const char *ndpAlgorithmClass) {
        this->ndpAlgorithmClass = ndpAlgorithmClass;
    }

    /**
     * Initiates passive OPEN, creating a "forking" connection that will listen
     * on the port you bound the socket to. Every incoming connection will
     * get a new connId (and thus, must be handled with a new NdpSocket object),
     * while the original connection (original connId) will keep listening on
     * the port. The new NdpSocket object must be created with the
     * NdpSocket(cMessage *msg) constructor.
     *
     * If you need to handle multiple incoming connections, the NdpSocketMap
     * class can also be useful, and NDPSrvHostApp shows how to put it all
     * together. See also NDPOpenCommand documentation (neddoc) for more info.
     */
    void listen() {
        listen(true);
    }

    /**
     * Initiates passive OPEN to create a non-forking listening connection.
     * Non-forking means that NDP will accept the first incoming
     * connection, and refuse subsequent ones.
     *
     * See NDPOpenCommand documentation (neddoc) for more info.
     */
    void listenOnce() {
        listen(false);
    }

    /**
     * Accepts a new incoming connection reported as available.
     */
    void accept(int socketId);
    /**
     * Active OPEN to the given remote socket.
     */
    void connect(L3Address localAddress, L3Address remoteAddr, int remotePort,
            bool isSender, bool isReceiver, unsigned int numPacketsToSend,
            bool isLongFlow, unsigned int priorityValue);

    /**
     * Sends data packet.
     */
    void send(Packet *msg);

    /**
     * Sends command.
     */
    void sendCommand(Request *msg);

    /**
     * Closes the local end of the connection. With NDP, a CLOSE operation
     * means "I have no more data to send", and thus results in a one-way
     * connection until the remote NDP closes too (or the FIN_WAIT_1 timeout
     * expires)
     */
    void close() override;

    /**
     * Aborts the connection.
     */
    void abort();

    /**
     * Destroy the connection.
     */
    virtual void destroy() override;

    /**
     * Causes NDP to reply with a fresh NDPStatusInfo, attached to a dummy
     * message as getControlInfo(). The reply message can be recognized by its
     * message kind NDP_I_STATUS, or (if a callback object is used)
     * the socketStatusArrived() method of the callback object will be
     * called.
     */
    void requestStatus();

    /**
     * Required to re-connect with a "used" NdpSocket object.
     * By default, a NdpSocket object is tied to a single NDP connection,
     * via the connectionId. When the connection gets closed or aborted,
     * you cannot use the socket to connect again (by connect() or listen())
     * unless you obtain a new connectionId by calling this method.
     *
     * BEWARE if you use NdpSocketMap! NdpSocketMap uses connectionId
     * to find NdpSockets, so after calling this method you have to remove
     * the socket from your NdpSocketMap, and re-add it. Otherwise NdpSocketMap
     * will get confused.
     *
     * The reason why one must obtain a new connectionId is that NDP still
     * has to maintain the connection data structure (identified by the old
     * connectionId) internally for a while (2 maximum segment lifetimes = 240s)
     * after it reported "connection closed" to us.
     */
    void renewSocket();

    virtual bool isOpen() const override;
    //@}

    /** @name Handling of messages arriving from NDP */
    //@{
    /**
     * Returns true if the message belongs to this socket instance (message
     * has a NDPCommand as getControlInfo(), and the connId in it matches
     * that of the socket.)
     */
    bool belongsToSocket(cMessage *msg) const override;

    /**
     * Sets a callback object, to be used with processMessage().
     * This callback object may be your simple module itself (if it
     * multiply inherits from CallbackInterface too, that is you
     * declared it as
     * <pre>
     * class MyAppModule : public cSimpleModule, public NdpSocket::CallbackInterface
     * </pre>
     * and redefined the necessary virtual functions; or you may use
     * dedicated class (and objects) for this purpose.
     *
     * NdpSocket doesn't delete the callback object in the destructor
     * or on any other occasion.
     *
     * YourPtr is an optional pointer. It may contain any value you wish --
     * NdpSocket will not look at it or do anything with it except passing
     * it back to you in the CallbackInterface calls. You may find it
     * useful if you maintain additional per-connection information:
     * in that case you don't have to look it up by connId in the callbacks,
     * you can have it passed to you as yourPtr.
     */
    void setCallback(ICallback *cb);

    /**
     * Examines the message (which should have arrived from NDP),
     * updates socket state, and if there is a callback object installed
     * (see setCallbackObject(), class CallbackInterface), dispatches
     * to the appropriate method of it with the same yourPtr that
     * you gave in the setCallbackObject() call.
     *
     * The method deletes the message, unless (1) there is a callback object
     * installed AND (2) the message is payload (message kind NDP_I_DATA or
     * NDP_I_URGENT_DATA) when the responsibility of destruction is on the
     * socketDataArrived() callback method.
     *
     * IMPORTANT: for performance reasons, this method doesn't check that
     * the message belongs to this socket, i.e. belongsToSocket(msg) would
     * return true!
     */
    void processMessage(cMessage *msg) override;
    //@}
};

} // namespace inet

#endif // ifndef __INET_NdpSocket_H


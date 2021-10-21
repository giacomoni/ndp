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

class INET_API NdpSocket : public ISocket
{
public:
    /**
     * Abstract base class for your callback objects. See setCallbackObject()
     * and processMessage() for more info.
     *
     * Note: this class is not subclassed from cObject, because
     * classes may have both this class and cSimpleModule as base class,
     * and cSimpleModule is already a cObject.
     */
    class INET_API ICallback
    {
    public:
        virtual ~ICallback()
        {
        }
        /**
         * Notifies about data arrival, packet ownership is transferred to the callee.
         */
        virtual void socketDataArrived(NdpSocket *socket, Packet *packet, bool urgent) = 0;
        virtual void socketAvailable(NdpSocket *socket, NdpAvailableInfo *availableInfo) = 0;
        virtual void socketEstablished(NdpSocket *socket) = 0;
        virtual void socketPeerClosed(NdpSocket *socket) = 0;
        virtual void socketClosed(NdpSocket *socket) = 0;
        virtual void socketFailure(NdpSocket *socket, int code) = 0;
        virtual void socketStatusArrived(NdpSocket *socket, NdpStatusInfo *status) = 0;
        virtual void socketDeleted(NdpSocket *socket) = 0;
    };

    enum State
    {
        NOT_BOUND, BOUND, LISTENING, CONNECTING, CONNECTED, PEER_CLOSED, LOCALLY_CLOSED, CLOSED, SOCKERROR
    };

protected:
    int connId = -1;
    State sockstate = NOT_BOUND;

    L3Address localAddr;
    int localPrt = -1;
    L3Address remoteAddr;
    int remotePrt = -1;

    ICallback *cb = nullptr;
    cGate *gateToNdp = nullptr;
    std::string ndpAlgorithmClass;

protected:
    void sendToNDP(cMessage *msg, int c = -1);

    // TODO: in the future to support apps with multiple incoming connections
    void listen(bool fork);

public:
    /**
     * Constructor. The getConnectionId() method returns a valid Id right after
     * constructor call.
     */
    NdpSocket();

    /**
     * Destructor
     */
    ~NdpSocket();

    /**
     * Returns the internal connection Id. NDP uses the (gate index, connId) pair
     * to identify the connection when it receives a command from the application
     * (or NdpSocket).
     */
    int getSocketId() const override
    {
        return connId;
    }
    /**
     * Returns the socket state, one of NOT_BOUND, CLOSED, LISTENING, CONNECTING,
     * CONNECTED, etc. Messages received from NDP must be routed through
     * processMessage() in order to keep socket state up-to-date.
     */
    NdpSocket::State getState()
    {
        return sockstate;
    }

    /**
     * Returns name of socket state code returned by getState().
     */
    static const char* stateName(NdpSocket::State state);

    void setState(NdpSocket::State state)
    {
        sockstate = state;
    }
    ;

    /** @name Getter functions */
    //@{
    L3Address getLocalAddress()
    {
        return localAddr;
    }
    int getLocalPort()
    {
        return localPrt;
    }
    L3Address getRemoteAddress()
    {
        return remoteAddr;
    }
    int getRemotePort()
    {
        return remotePrt;
    }
    //@}

    /** @name Opening and closing connections, sending data */
    //@{
    /**
     * Sets the gate on which to send to NDP. Must be invoked before socket
     * can be used. Example: <tt>socket.setOutputGate(gate("raptondpOut"));</tt>
     */
    void setOutputGate(cGate *toNdp)
    {
        gateToNdp = toNdp;
    }

    /**
     * TODO: add an NDP specific comment here
     */
    void bind(L3Address localAddr, int localPort);

    /**
     * Returns the current ndpAlgorithmClass parameter.
     */
    const char* getNdpAlgorithmClass() const
    {
        return ndpAlgorithmClass.c_str();
    }

    /**
     * Sets the ndpAlgorithmClass parameter of the next connect() or listen() call.
     */
    void setNdpAlgorithmClass(const char *ndpAlgorithmClass)
    {
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
    void listen()
    {
        listen(true);
    }

    /**
     * Initiates passive OPEN to create a non-forking listening connection.
     * Non-forking means that NDP will accept the first incoming
     * connection, and refuse subsequent ones.
     *
     * See NDPOpenCommand documentation (neddoc) for more info.
     */
    void listenOnce()
    {
        listen(false);
    }

    /**
     * TODO: not used, add comment explaining why
     * TODO: maybe create in the future applications that can accept multiple incoming NDP connections
     */
    void accept(int socketId);

    /**
     * TODO: eliminate unnecessary stuff and explain what's done here
     */
    void connect(L3Address localAddress, L3Address remoteAddr, int remotePort, bool isSender, bool isReceiver, unsigned int numPacketsToSend, unsigned int priorityValue);

    /**
     * TODO: not implemented - explain
     */
    void send(Packet *msg);

    /**
     * TODO: NDP sender does it - explain
     */
    void close() override;

    /**
     * TODO: not implemented - explain
     */
    void abort();

    /**
     * TODO: not implemented - explain
     */
    virtual void destroy() override;

    /**
     * TODO: figure out why it is needed - look but not copy TCP code
     */
    void renewSocket();

    // TODO: not called - add comment
    virtual bool isOpen() const override;

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


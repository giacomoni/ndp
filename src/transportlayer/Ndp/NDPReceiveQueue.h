
#ifndef __INET_NDPRECEIVEQUEUE_H
#define __INET_NDPRECEIVEQUEUE_H

#include <list>
#include <string>

#include "inet/common/INETDefs.h"
#include "inet/common/packet/ChunkQueue.h"
#include "inet/common/packet/ReorderBuffer.h"
#include "inet/common/packet/chunk/SequenceChunk.h"
#include "NDPConnection.h"
#include "ndp_common/NdpHeader.h"


namespace inet {

class NDPCommand;

namespace ndp {

class NdpHeader;

/**
 * Abstract base class for NDP receive queues. This class represents
 * data received by NDP but not yet passed up to the application.
 * The class also accommodates for selective retransmission, i.e.
 * also acts as a segment buffer.
 *
 * This class goes hand-in-hand with NDPSendQueue.
 *
 * This class is poly-morphic because depending on where and how you
 * use the NDP model you might have different ideas about "sending data"
 * on a simulated connection: you might want to transmit real bytes,
 * "dummy" (byte count only), cMessage objects, etc; see discussion
 * at NDPSendQueue. Different subclasses can be written to accommodate
 * different needs.
 *
 * @see NDPSendQueue
 */
class INET_API NDPReceiveQueue : public cObject
{
  protected:
    NDPConnection *conn = nullptr;    // the connection that owns this queue
    uint32 rcv_nxt = 0;
    ReorderBuffer reorderBuffer;

  protected:
      uint32_t offsetToSeq(B offs) const { return (uint32_t)offs.get(); }

      B seqToOffset(uint32_t seq) const
      {
          B expOffs = reorderBuffer.getExpectedOffset();
          uint32_t expSeq = offsetToSeq(expOffs);
          return B((seqGE(seq, expSeq)) ? B(expOffs).get() + (seq - expSeq) : B(expOffs).get() - (expSeq - seq));
      }

  public:
    /**
     * Ctor.
     */
    NDPReceiveQueue();

    /**
     * Virtual dtor.
     */
    virtual ~NDPReceiveQueue() {}

    virtual ReorderBuffer& getReorderBuffer() { return reorderBuffer; }
    /**
     * Set the connection that owns this queue.
     */
//    virtual void setConnection(NDPConnection *_conn) { conn = _conn; }

    /**
     * Set initial receive sequence number.
     */
    virtual void init(uint32 startSeq);

    virtual std::string str() const override;
    /**
     * Called when a NDP segment arrives, it should extract the payload
     * from the segment and store it in the receive queue. The segment
     * object should *not* be deleted.
     *
     * The method should return the sequence number to be ACKed.
     */
//    virtual uint32 insertBytesFromSegment(NDPSegment *NDPseg) = 0;

    /**
     * Should create a packet to be passed up to the app, up to (but NOT
     * including) the given sequence no (usually rcv_nxt).
     * It should return nullptr if there's no more data to be passed up --
     * this method is called several times until it returns nullptr.
     */
//    virtual cPacket *extractBytesUpTo(uint32 seq) = 0;

    /**
     * Returns the number of bytes (out-of-order-segments) currently buffered in queue.
     */
//    virtual uint32 getAmountOfBufferedBytes() = 0;

    /**
     * Returns the number of bytes currently free (=available) in queue. freeRcvBuffer = maxRcvBuffer - usedRcvBuffer
     */
//    virtual uint32 getAmountOfFreeBytes(uint32 maxRcvBuffer) = 0;

    /**
     * Returns the number of blocks currently buffered in queue.
     */
//    virtual uint32 getQueueLength() = 0;

    /**
     * Shows current queue status.
     */
//    virtual void getQueueStatus() = 0;

    /**
     * Returns left edge of enqueued region.
     */
//    virtual uint32 getLE(uint32 fromSeqNum) = 0;

    /**
     * Returns right edge of enqueued region.
     */
//    virtual uint32 getRE(uint32 toSeqNum) = 0;

    /** Returns the minimum of first byte seq.no. in queue and rcv_nxt */
//    virtual uint32 getFirstSeqNo() = 0;
};

} // namespace ndp

} // namespace inet

#endif // ifndef __INET_NDPRECEIVEQUEUE_H


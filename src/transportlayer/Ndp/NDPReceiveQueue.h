
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
    virtual ~NDPReceiveQueue();

    virtual ReorderBuffer& getReorderBuffer() { return reorderBuffer; }

    virtual void init(uint32 startSeq);

    virtual std::string str() const override;
};

} // namespace ndp

} // namespace inet

#endif // ifndef __INET_NDPRECEIVEQUEUE_H


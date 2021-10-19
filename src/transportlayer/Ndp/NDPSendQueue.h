//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_NDPSENDQUEUE_H
#define __INET_NDPSENDQUEUE_H

#include "inet/common/INETDefs.h"
#include "inet/common/packet/ChunkQueue.h"
#include "inet/common/packet/Packet.h"
#include "NDPConnection.h"
#include "ndp_common/NdpHeader.h"
#include "../../application/ndpapp/GenericAppMsgNdp_m.h"


namespace inet {

namespace ndp {

class INET_API NDPSendQueue : public cObject
{
  protected:
    NDPConnection *conn = nullptr;    // the connection that owns this queue
    uint32 begin = 0;    // 1st sequence number stored
    uint32 end = 0;    // last sequence number stored +1

    cPacketQueue dataToSendQueue;      // dataBuffer
    cPacketQueue sentDataQueue;

  public:
    /**
     * Ctor.
     */
    NDPSendQueue();

    /**
     * Virtual dtor.
     */
    virtual ~NDPSendQueue();

    virtual cPacketQueue& getDataToSendQueue() { return dataToSendQueue; }
    virtual cPacketQueue& getSentDataQueue() { return sentDataQueue; }
    /**
     * Set the connection that owns this queue.
     */
    virtual void setConnection(NDPConnection *_conn) { conn = _conn; }

    /**
     * Initialize the object. The startSeq parameter tells what sequence number the first
     * byte of app data should get. This is usually ISS + 1 because SYN consumes
     * one byte in the sequence number space.
     *
     * init() may be called more than once; every call flushes the existing contents
     * of the queue.
     */
    virtual void init(unsigned int numPacketsToSend , B mss);

    /**
     * Returns a string with the region stored.
     */
    virtual std::string str() const override;

    /**
     * Called on SEND app command, it inserts in the queue the data the user
     * wants to send. Implementations of this abstract class will decide
     * what this means: copying actual bytes, just increasing the
     * "last byte queued" variable, or storing cMessage object(s).
     * The msg object should not be referenced after this point (sendQueue may
     * delete it.)
     */
    virtual void enqueueAppData(Packet *msg);

    /**
     * Returns the sequence number of the first byte stored in the buffer.
     */
    virtual uint32 getBufferStartSeq();

    /**
     * Returns the sequence number of the last byte stored in the buffer plus one.
     * (The first byte of the next send operation would get this sequence number.)
     */
    virtual uint32 getBufferEndSeq();

    virtual const std::tuple<Ptr<NdpHeader>, Packet*> getNdpHeader();

    virtual void ackArrivedFreeBuffer(unsigned int ackNum);
    virtual void nackArrivedMoveFront(unsigned int nackNum);


    /**
     * Utility function: returns how many bytes are available in the queue, from
     * (and including) the given sequence number.
     */
    inline ulong getBytesAvailable(uint32 fromSeq)
    {
        uint32 bufEndSeq = getBufferEndSeq();
        return seqLess(fromSeq, bufEndSeq) ? bufEndSeq - fromSeq : 0;
    }

//    void removeFromDataQueueToSentQueue(Chunk::Iterator iter);
    void moveFrontDataQueue(unsigned int sequenceNumber);
};

} // namespace raptoNDP

} // namespace inet

#endif // ifndef __INET_NDPSENDQUEUE_H


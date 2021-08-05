import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.transportlayer.contract.TransportHeaderBase;

namespace inet::ndp;

cplusplus {{
const B NDP_MIN_HEADER_LENGTH = B(20);  // default NDP header length: 20 bytes without options
const B NDP_MAX_HEADER_LENGTH = B(60);  // maximum NDP header length (base + options): 60 = 15 * 4 bytes

const B NDP_OPTIONS_MAX_SIZE     = B(40);  // 40 bytes, 15 * 4 bytes (15 is the largest number in 4 bits length data offset field), TCP_MAX_HEADER_OCTETS - TCP_HEADER_OCTETS = 40
const B NDP_OPTION_HEAD_SIZE = B(2);       // 2 bytes, type and length
const B NDP_OPTION_SACK_MIN_SIZE = B(10);  // 10 bytes, option length = 8 * n + 2 bytes (NOP)
const B NDP_OPTION_SACK_ENTRY_SIZE = B(8); // sack entry size
const B NDP_OPTION_TS_SIZE       = B(12);  // 12 bytes, option length = 10 bytes + 2 bytes (NOP)

}}

enum NdpConstants {
    // maximum allowed sack entry number, if no other options are used
    NDP_MAX_SACK_ENTRIES = 4;
}

//
// NDP Option Numbers
// Reference: http://www.iana.org/assignments/tcp-parameters/
// Date: 2011-07-02
//
// Note: Options not yet implemented should stay commented out
//
enum NdpOptionNumbers
{
    NDPOPTION_END_OF_OPTION_LIST = 0;                   // RFC 793, LENGTH: 1 Byte
    NDPOPTION_NO_OPERATION = 1;                         // RFC 793, LENGTH: 1 Byte
    NDPOPTION_MAXIMUM_SEGMENT_SIZE = 2;                 // RFC 793, LENGTH: 4 Bytes
    NDPOPTION_WINDOW_SCALE = 3;                         // RFC 1323, LENGTH: 3 Bytes
    NDPOPTION_SACK_PERMITTED = 4;                       // RFC 2018, LENGTH: 2 Bytes
    NDPOPTION_SACK = 5;                                 // RFC 2018, LENGTH: N (max. N = 4) 8 * n + 2 Bytes  => 32 + 2 + 2 * NOP = 36 Bytes; If TIMESTAMP option is used with SACK: max. n = 3 => 12 Bytes (for Timestamp) + 28 Bytes (for SACK) = 40 Bytes
    NDPOPTION_TIMESTAMP = 8;                            // RFC 1323, LENGTH: 10 Bytes
};

//
// This structure represents a single SACK (selective acknowledgment):
//
class SackItem extends cObject
{
    unsigned int start;     // start seq no. of sack block
    unsigned int end;       // end seq no. of sack block
}

class Sack extends SackItem
{
}

cplusplus(Sack) {{
  public:
    Sack(unsigned int start_par, unsigned int end_par) { setSegment(start_par, end_par); }
    virtual bool empty() const;
    virtual bool contains(const Sack& other) const;
    virtual void clear();
    virtual void setSegment(unsigned int start_par, unsigned int end_par);
    virtual std::string str() const override;
}}

// Header Options (optional):
class NdpOption extends cObject
{
    @packetData;
    NdpOptionNumbers kind;            // option kind
    unsigned short length = 1;                    // option length
}

class NdpOptionEnd extends NdpOption
{
    kind = NDPOPTION_END_OF_OPTION_LIST;
    length = 1;
}

class NdpOptionNop extends NdpOption
{
    kind = NDPOPTION_NO_OPERATION;
    length = 1;
}

class NdpOptionMaxSegmentSize extends NdpOption
{
    kind = NDPOPTION_MAXIMUM_SEGMENT_SIZE;
    length = 4;
    uint16_t maxSegmentSize;   // uint16_t
}

class NdpOptionWindowScale extends NdpOption
{
    kind = NDPOPTION_WINDOW_SCALE;
    length = 3;
    unsigned short windowScale;   // uint8_t
}

class NdpOptionSackPermitted extends NdpOption
{
    kind = NDPOPTION_SACK_PERMITTED;
    length = 2;
}

class NdpOptionSack extends NdpOption
{
    kind = NDPOPTION_SACK;
    length = 2;     // 2 + getSackArraySize() * 8
    SackItem sackItem[];
}

class NdpOptionTimestamp extends NdpOption
{
    kind = NDPOPTION_TIMESTAMP;
    length = 10;
    uint32_t   senderTimestamp;
    uint32_t   echoedTimestamp;
}

class NdpOptionUnknown extends NdpOption
{
    kind = static_cast<NdpOptionNumbers>(-1);
    uint8_t bytes[];
}

//
// Represents a NDP segment, to be used with the ~NDP module.
//
// NDP header fields not explicitly modelled: work on going
// - Data Offset (number of 32 bit words in the header): represented
//   by cMessage::length().
// - Reserved (reserved for future use)
// - Checksum (header checksum): modelled by cMessage::hasBitError()
// - Header Options: Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented
// - Padding
//
// cMessage::getKind() may be set to an arbitrary value: NDP entities will
// ignore it and use only the header fields (synBit, ackBit, rstBit).
//
class NdpHeader extends TransportHeaderBase
{
    chunkLength = NDP_MIN_HEADER_LENGTH;

    // Source Port
    unsigned short srcPort;

    // Destination Port
    unsigned short destPort;

    // Sequence Number: first sequence number of the first data octet
    // in the respective segment (except if SYN is set; then the the
    // seq. number is the initial seq. number (ISS) and the first data
    // octet is ISS + 1)
    //unsigned int sequenceNo;

    // Acknowledgement Number: if ACK flag is set, this field contains
    // the next sequence number the sender of this segment is expecting
    // to receive
    unsigned int ackNo;
	unsigned int nackNo;
	
	bool isHeader;
	bool isPullPacket;
	bool isDataPacket;
	bool isLongFlow;
	unsigned int priorityValue;
	unsigned int numPacketsToSend;
	unsigned int pullSequenceNumber;
	unsigned int dataSequenceNumber;
	bool isLastPktToSend;
	bool ackBit;
	bool nackBit;
    // NDP Header Length - default: 20 bytes
    // if header options are used the headerLength is greater than 20 bytes (default)
    B headerLength = NDP_MIN_HEADER_LENGTH; // NDP_MIN_HEADER_LENGTH = 20 bytes

  	bool urgBit; // URG: urgent pointer field significant if set
    bool pshBit; // PSH: push function
    bool rstBit; // RST: reset the connection
    bool synBit; // SYN: synchronize seq. numbers
    bool finBit; // FIN: finish - no more data from sender

    // Window Size: the number of data octets beginning with the one indicated
    // in the acknowledgement field which the sender of this segment is
    // willing to accept
    unsigned short window;

    // Urgent Pointer: communicates the current value of the urgent pointer
    // as a positive offset from the sequence number in this segment. The
    // urgent pointer points to the sequence number of the octet following
    // the urgent data. This field is only be interpreted in segments with
    // the URG control bit set.
    unsigned short urgentPointer;

    // Header options (optional)
    // Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented
    NdpOption *headerOption[] @owned;
}

cplusplus(NdpHeader) {{
  public:
    /**
     * Returns RFC 793 specified SEG.LEN:
     *     SEG.LEN = the number of octets occupied by the data in the segment
     *               (counting SYN and FIN)
     *
     */
    uint32_t getSynFinLen() const { return (finBit ? 1 : 0) + (synBit ? 1 : 0); }

    /** Calculate Length of NDP Options Array in bytes */
    virtual B getHeaderOptionArrayLength();

    /** Drops all NDP options of the NDP segment */
    virtual void dropHeaderOptions();

    // implements TransportHeaderBase functions:
    virtual unsigned int getSourcePort() const override { return getSrcPort(); }
    virtual void setSourcePort(unsigned int port) override { setSrcPort(port); }
    virtual unsigned int getDestinationPort() const override { return getDestPort(); }
    virtual void setDestinationPort(unsigned int port) override { setDestPort(port); }

    virtual std::string str() const override;
}}


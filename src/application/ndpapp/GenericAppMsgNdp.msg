

import inet.common.INETDefs;
import inet.common.Units;
import inet.common.packet.chunk.Chunk;

namespace inet;

 
class GenericAppMsgNdp extends FieldsChunk
{
  
    int numPacketsToSend;  //  if this is a reader(receiver)
    bool isSender;  // receiver 
    bool isReceiver;  // receiver 
   	bool isLongFlow;
    bool serverClose;        // if true, server should close the
    uint32_t sequenceNumber; //new TODO
 }




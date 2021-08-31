

import inet.common.INETDefs;
import inet.common.Units;
import inet.common.packet.chunk.Chunk;

namespace inet;

 
class GenericAppMsgNdp extends FieldsChunk
{
  
    int numPaketToSend;  //  if this is a reader(receiver)
    bool isSender;  // receiver 
    bool isReceiver;  // receiver 
   	bool isLongFlow;
    bool serverClose;        // if true, server should close the
 }




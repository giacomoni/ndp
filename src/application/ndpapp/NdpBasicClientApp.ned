
package ndp.application.ndpapp;

import ndp.application.contract.INdpApp;
import inet.applications.contract.IApp;

simple NdpBasicClientApp like IApp
{
    parameters:
        @class("inet::NdpBasicClientApp");
        string localAddress = default(""); // may be left empty ("")
        int localPort = default(-1); // port number to listen on
        string connectAddress = default("");  // server address (may be symbolic)
        int connectPort = default(1000); // port number to connect to
//        string dataTransferMode @enum("bytecount","object","bytestream","rqrequests") = default("bytecount");
        double startTime @unit(s) = default(1s); // time first session begins
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, negative values mean forever

       
        volatile int sendBytes @unit(B) =  default(1MiB); 
        int numPacketsToSend;  // if this is a sender
        bool isLongFlow = default(false);  // 
        int priorityValue = default(0);
        bool isSender = default(true); 
        bool isReceiver = default(false);  
        

//         volatile int replyLength @unit(B) = default(1MiB); // length of a reply

        volatile double reconnectInterval @unit(s) = default(30s);  // if connection breaks, waits this much before trying to reconnect
 
		@lifecycleSupport;
		double stopOperationExtraTime @unit(s) = default(-1s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation
        
        //@signal[rcvdPacketSignal](type=cPacket);
        //@statistic[rcvdPacketSignal](title="packets received"; source=rcvdPacketSignal; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        //@signal[packetReceived](type=inet::Packet);
        //@statistic[packetReceived](title="packets received test"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        //MOH: method2 instantaneous throughputs, see ResultFilter.cc
        //@statistic[ndpThroughput](title="ndpThroughput"; source="throughput(packetReceived)"; unit=bps; record=mean);

        @display("i=msg/mail;i2=status/down");
    gates:
        input socketIn @labels(NDPCommand/up);
        output socketOut @labels(NDPCommand/down);
}



package ndp.application.ndpapp;
import ndp.application.contract.INdpApp;
import ndp.application.ndpapp.NdpServerHostApp;

simple NdpSinkApp extends NdpServerHostApp
{
    parameters:
        serverThreadModuleType = default("ndp.application.ndpapp.NdpSinkAppThread");
        @class("inet::NdpSinkApp");
         @display("i=block/sink");
        int multiCastGroupId = default(-1);
        int multiSrcGroupId = default(-1);
 		serverThreadModuleType = default("ndp.application.ndpapp.NdpSinkAppThread"); // module type of "thread" module to launch on incoming connections
        // moh
        bool isLongFlow = default(false);
        
        @signal[numRcvTrimmedHeaderSigNdp](type=double);
        @statistic[numRcvTrimmedHeaderSigNdp](title="numRcvTrimmedHeaderNdp"; source=numRcvTrimmedHeaderSigNdp; unit=s; record=last);
           
        @signal[multicastGroupIdSignal](type=double);
        @statistic[multicastGroupIdSignal](title="multicastGroupIdSignal "; source=multicastGroupIdSignal; unit=s; record=last);

        @signal[multisourceGroupIdSignal](type=double);
        @statistic[multisourceGroupIdSignal](title="multisourceGroupIdSignal "; source=multisourceGroupIdSignal; unit=s; record=last);


        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="NDP Sesssion's flow completion time"; source=fctRecordv3; unit=s; record=last);

        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets (symbols) received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

         // MOH: FCT using ResultFilter.cc (messageAge)
//       @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);

        @statistic[mohThroughputNDP](title="mohThroughputNDP"; source="throughput(rcvdPk)"; unit=bps; record=mean);
}

simple NdpSinkAppThread
{
     @display("i=block/sink");
}    


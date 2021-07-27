

package ndp;

import ndp.transportlayer.contract.INdp;
import inet.ndp.application.contract.INdpApp;

import inet.transportlayer.contract.ITcp;

import inet.applications.contract.IApp;
//import inet.applications.contract.IPingApp;
//import inet.applications.contract.ISCTPApp;
//import inet.applications.contract.ITCPApp;
//import inet.applications.contract.IUDPApp;
import inet.transportlayer.contract.ISctp;
import inet.transportlayer.contract.ITcp;
import inet.transportlayer.contract.IUdp;
import inet.applications.tunapp.TunnelApp;

module StandardHostNdp extends NodeBase
{
    parameters:
        @display("i=device/pc2;bgb=939,470");
        int numTcpApps = default(0);  // no of TCP apps. Specify the app types in INI file with tcpApp[0..1].typename="TCPEchoApp" syntax
        int numUdpApps = default(0);  // no of UDP apps. Specify the app types in INI file with udpApp[0..1].typename="UDPVideoStreamCli" syntax
        int numSctpApps = default(0); // no of SCTP apps. Specify the app types in INI file with sctpApp[0..1].typename="SCTPServer" syntax
        int numPingApps = default(0);  // no of PING apps. Specify the app types in INI file with pingApp[0..1].typename="PingApp" syntax
        bool hasTcp = default(numTcpApps > 0);
        bool hasUdp = default(numUdpApps > 0);
        bool hasSctp = default(numSctpApps > 0);
        bool hasTun = default(numTunInterfaces > 0);
        string tcpType = default(firstAvailableOrEmpty("TCP", "TCP_lwIP", "TCP_NSC"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
        string udpType = default(firstAvailableOrEmpty("UDP"));
        string sctpType = default(firstAvailableOrEmpty("SCTP"));
        forwarding = default(false);  // disable routing by default
        networkLayer.proxyARP = default(false);

        ///////////// ndp  
        int numNdpApps = default(0);
        bool hasNdp = default(numNdpApps > 0);
        string ndpType = default(firstAvailableOrEmpty("Ndp"));
        /////////////  
 
    submodules:
        tunApp[numTunInterfaces]: <> like IApp {
            parameters:
                @display("p=168,42");
        }
        tcpApp[numTcpApps]: <> like IApp {
            parameters:
                @display("p=319,42,row,60");
        }
        tcp: <tcpType> like ITcp if hasTcp {
            parameters:
                @display("p=291,141");
        }
        udpApp[numUdpApps]: <> like IApp {
            parameters:
                @display("p=463,42,row,60");
        }
        udp: <udpType> like IUdp if hasUdp {
            parameters:
                @display("p=393,141");
        }
        sctpApp[numSctpApps]: <> like IApp {
            parameters:
                @display("p=840,42,row,60");
        }
        sctp: <sctpType> like ISctp if hasSctp {
            @display("p=738,178");
        }
        pingApp[numPingApps]: <default("PingApp")> like IApp {
            parameters:
                @display("p=651,269,row,60");
        }

        ///////////// ndp
        ndp: <ndpType> like INdp if hasNdp {
            @display("p=573,140;i=abstract/penguin");
        }

        ndpApp[numNdpApps]: <> like INdpApp {
            @display("p=651,42,r,30");
        }
        /////////////  

    connections allowunconnected:
        for i=0..numTcpApps-1 {
            tcpApp[i].socketOut --> tcp.appIn;
            tcpApp[i].socketIn <-- tcp.appOut;
        }

        tcp.ipOut --> networkLayer.transportIn if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut if hasTcp;

        for i=0..numUdpApps-1 {
            udpApp[i].socketOut --> udp.appIn;
            udpApp[i].socketIn <-- udp.appOut;
        }

        udp.ipOut --> networkLayer.transportIn if hasUdp;
        udp.ipIn <-- networkLayer.transportOut if hasUdp;

        for i=0..numSctpApps-1 {
            sctpApp[i].socketOut --> sctp.appIn;
            sctp.appOut --> sctpApp[i].socketIn;
        }
        sctp.ipOut --> networkLayer.transportIn if hasSctp;
        networkLayer.transportOut --> sctp.ipIn if hasSctp;

        for i=0..numPingApps-1 {
            networkLayer.ifOut --> pingApp[i].socketIn;
            networkLayer.ifIn <-- pingApp[i].socketOut;
        }

        for i=0..numTunInterfaces-1 {
            tunApp[i].socketOut --> tun[i].upperLayerIn if hasTun;
            tunApp[i].socketIn <-- tun[i].upperLayerOut if hasTun;
        }


        ///////////// 
        for i=0..numNdpApps-1 {
            ndpApp[i].ndpOut --> ndp.appIn++;
            ndpApp[i].ndpIn <-- ndp.appOut++;
        }

        ndp.ipOut --> networkLayer.transportIn if hasNdp;
        ndp.ipIn <-- networkLayer.transportOut if hasNdp;

}

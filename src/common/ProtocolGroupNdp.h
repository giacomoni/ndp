//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef COMMON_PROTOCOLGROUPNDP_H_
#define COMMON_PROTOCOLGROUPNDP_H_

#include "inet/common/Protocol.h"
#include "ProtocolNdp.h"

namespace inet {

class INET_API ProtocolGroupNdp
{
  protected:
    const char *name;
    std::map<int, const Protocol *> protocolNumberToProtocol;
    std::map<const Protocol *, int> protocolToProtocolNumber;

  public:
    ProtocolGroupNdp(const char *name, std::map<int, const Protocol *> protocolNumberToProtocol);

    const char *getName() const { return name; }

    const Protocol *findProtocol(int protocolNumber) const;
    const Protocol *getProtocol(int protocolNumber) const;
    int findProtocolNumber(const Protocol *protocol) const;
    int getProtocolNumber(const Protocol *protocol) const;
    void addProtocol(int protocolId, const Protocol *protocol);

  public:
    // in alphanumeric order
    static ProtocolGroupNdp ethertype;
    static ProtocolGroupNdp pppprotocol;
    static ProtocolGroupNdp ipprotocol;
    static ProtocolGroupNdp ieee8022protocol;
    static ProtocolGroupNdp snapOui;
    static ProtocolGroupNdp udpprotocol;
    static ProtocolGroupNdp tcpprotocol;
    static ProtocolGroupNdp ndpprotocol;
};

} // namespace inet

#endif // ifndef __INET_PROTOCOLGROUP_H


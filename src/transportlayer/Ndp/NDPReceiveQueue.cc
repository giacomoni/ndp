//
// Copyright (C) 2004 Andras Varga
// Copyright (C) 2009 Thomas Reschka
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

#include "NDPReceiveQueue.h"

namespace inet {

namespace ndp {

Register_Class(NDPReceiveQueue);

NDPReceiveQueue::NDPReceiveQueue() :
        rcv_nxt(-1) {
}

NDPReceiveQueue::~NDPReceiveQueue() {
}

void NDPReceiveQueue::init(uint32 startSeq) {
    rcv_nxt = startSeq;

    reorderBuffer.clear();
    reorderBuffer.setExpectedOffset(B(startSeq));
}

std::string NDPReceiveQueue::str() const {
    std::ostringstream buf;
    buf << "rcv_nxt=" << rcv_nxt;

    for (int i = 0; i < reorderBuffer.getNumRegions(); i++) {
        buf << " [" << offsetToSeq(reorderBuffer.getRegionStartOffset(i))
                << ".." << offsetToSeq(reorderBuffer.getRegionEndOffset(i))
                << ")";
    }
    return buf.str();
}

} // namespace tcp

} // namespace inet


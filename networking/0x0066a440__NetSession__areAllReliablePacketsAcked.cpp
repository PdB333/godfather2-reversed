// FUNC_NAME: NetSession::areAllReliablePacketsAcked
// Address: 0x0066a440
// Role: Checks whether all reliable packets from a certain index (0x1C) up to the current acknowledged count have been received.
// Returns 1 (true) if all required ack bits are set, 0 otherwise.
// Uses state variable from object (0 for disconnected, 1 for connected but possibly incomplete, >1 for active).

int __thiscall NetSession::areAllReliablePacketsAcked()
{
    int state = *(int*)this; // +0x00: connection state (0=disconnected, 1=init, >1=active)
    if (state == 0) {
        return 0;
    }
    if (state == 1) {
        return 1;
    }
    // state > 1: active connection
    int ackCount = this->getAckedPacketCount(); // calls FUN_00665d40, returns number of acknowledged packets
    uint bitMask = 1;
    int packetIndex = 0x1c; // start at index 28 (likely first user packet or window offset)
    if (ackCount > 0x1c) {
        // bitmask array: at offset +0x0C there's a pointer to a bitmask structure, +0x04 is start of uint array
        uint* maskPtr = *(uint**)((char*)this + 0x0C) + 1; // &(this->bitmaskArray[0])
        do {
            if ((*maskPtr & bitMask) == 0) {
                return 0; // missing ack for packetIndex
            }
            bitMask <<= 1;
            if (bitMask > 0xfffffff) { // overflow for 28-bit mask? (might be 0xfffffff = 28-bit mask)
                maskPtr++;
                bitMask = 1;
            }
            packetIndex++;
        } while (packetIndex < ackCount);
    }
    return 1; // all required ack bits are set
}
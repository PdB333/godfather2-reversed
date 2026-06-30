// FUNC_NAME: TNLConnection::freeSequencedPacket
int __thiscall TNLConnection::freeSequencedPacket(uint packetIndex)
{
    int result = 0;
    // Check if packet slot array exists and index is valid (max 0x200 entries)
    if ((*(int *)(this + 0x603c) != 0) && (packetIndex < 0x200)) {
        int *slotPtr = (int *)(packetIndex * 0x74 + *(int *)(this + 0x603c));
        if (slotPtr != (int *)0x0) {
            // If packet holds a secondary data buffer (at offset +8), free it first
            if (slotPtr[2] != 0) {
                FUN_005f1ef0(slotPtr[2]);  // likely releaseBuffer or destructor
            }
            // If the primary packet data pointer (offset +0) is non-null, release it
            if ((int *)*slotPtr != (int *)0x0) {
                FUN_005dbc10(packetIndex, *(int *)*slotPtr); // likely freePacketData
                FUN_005e5200(0); // possibly decrement an active count or notify
                *slotPtr = 0;    // clear the pointer
                return 1;
            }
            // No primary data, just release index with null
            FUN_005dbc10(packetIndex, 0);
            result = 1;
        }
    }
    return result;
}
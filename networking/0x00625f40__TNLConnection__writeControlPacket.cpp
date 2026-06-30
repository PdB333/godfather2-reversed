// FUNC_NAME: TNLConnection::writeControlPacket
// Address: 0x00625f40
// Writes a control packet (type 5) with a sequence number into the send buffer.
void __thiscall TNLConnection::writeControlPacket(void)
{
    // +0x10: Pointer to packet buffer manager (contains write position and size)
    uint32_t* bufferMeta = *(uint32_t**)(this + 0x10);
    // +0x20: Current write position (offset in buffer) ?
    // +0x24: Buffer size limit (max bytes) ?
    // If write position is within buffer bounds (i.e., there is space left), ensure buffer space.
    if (bufferMeta[0x20 / 4] <= bufferMeta[0x24 / 4]) {
        FUN_00627360(); // Likely flushOrAllocateBuffer()
    }

    // +0x8: Pointer to the buffer write pointer (next free byte in buffer)
    uint32_t* writePtr = *(uint32_t**)(this + 8);
    *writePtr = 5; // Packet type identifier (e.g., ControlPacket)
    writePtr[1] = FUN_00637c50(0, 0); // Sequence number (generated from two zero params)
    // Advance the write pointer by 8 bytes (one packet header)
    *(int*)(this + 8) += 8;
}
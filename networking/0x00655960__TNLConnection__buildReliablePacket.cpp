// FUNC_NAME: TNLConnection::buildReliablePacket
void __thiscall TNLConnection::buildReliablePacket(void* this, Packet* packet) {
    // Stack-allocated bitstream writer with capacity 8*8=64 bits? (local buffer of 1024 bytes)
    char bitstreamBuffer[1024];                  // local_404
    BitStream writer;                            // local_53d (structure)
    writer.setCapacity(8 * 8);                   // FUN_0064b810(8, &local_53d) — presumably 8 bytes = 64 bits
    writer.writeInt(0x40, this + 0x133);         // FUN_0064b810(0x40, this+0x133) — write 64-bit value? Actually 0x40 = 64 bits?
    writer.writeBool(*(uint8*)((char*)this + 0x160)); // FUN_0064bb50 — write a boolean
    writer.writeBool(*(uint8*)((char*)this + 0x161)); // another boolean
    // Increment packet sequence counter
    *(uint32*)((char*)this + 0x19C) += 1;       // packetSendCount
    // Store timestamp from packet
    *(uint32*)((char*)this + 0x1A0) = *(uint32*)((char*)packet + 100); // +0x64 = packet->timestamp
    // Copy the bitstream data into the packet's payload buffer (offset 0x5C)
    // local_524 is the number of bits written; initially 0? Might be set by bitstream operations.
    uint32 bitCount = 0;                         // local_524
    uint32 byteCount = (bitCount + 7) >> 3;     // convert bits to bytes
    FUN_00658230((char*)packet + 0x5C, bitstreamBuffer, byteCount, 0); // memcpy/queue?
    // Flush or finalize
    FUN_0064b440();                              // likely flushNetBuffer or similar
}
// FUNC_NAME: TNLConnection::finalizePacket
// Function at 0x00471eb0: Finalizes sending a packet. Calls serialization flush and optionally records 
// the packet into a global pool for retransmission or acknowledgment tracking.
void __fastcall TNLConnection::finalizePacket(TNLConnection* this)
{
    // +0x130: pointer to a serialization object (e.g., BitStream, PacketWriter)
    if (this->serializer != nullptr)
    {
        // Call virtual function at vtable offset 0x28 (typically "flush" or "finalizeWrite")
        // This ensures any buffered data is written to the underlying stream.
        (this->serializer->vtable[0x28 / 4])();
    }

    // +0x164: flag indicating whether to record this packet for later use (e.g., sent packet history)
    if (this->recordPacketFlag != 0)
    {
        // gPacketPool is a global pool structure for building packet records.
        // +0x14 holds a write pointer that advances through a pre-allocated buffer.
        uint* writePtr = (uint*)(gPacketPool + 0x14);
        // Write vtable pointer for a packet record node (PACKET_NODE)
        *(void**)(*writePtr) = &gPacketNodeVTable;
        *writePtr += 4;
        // Write pointer to the packet data (at this+0x54, likely the raw packet buffer or start of data)
        *(int*)*writePtr = (int)(this + 0x54);
        *writePtr += 4;
        // Write a zero byte (terminator or null flag)
        *(char*)*writePtr = 0;
        *writePtr += 4;
        // Align to DWORD boundary for subsequent writes
        *writePtr = (uint)(*writePtr & 0xFFFFFFFC);
    }
}
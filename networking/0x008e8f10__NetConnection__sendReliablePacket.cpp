// FUNC_NAME: NetConnection::sendReliablePacket
void __thiscall NetConnection::sendReliablePacket(uint32_t messageId)
{
    // offsets:
    // +0x3c: flag byte, bit0 indicates pending outgoing packet
    // +0x34: pointer to pending packet data (if any)
    // +0x58-0x64: 128-bit GUID (4 ints) for the connection
    byte* flag = (byte*)(this + 0x3c);
    int* pendingPacket = (int*)(this + 0x34);
    int* guid = (int*)(this + 0x58);
    const int MAGIC0 = 0xBBADBABA; // -0x45245246
    const int MAGIC1 = 0xBEEFBEEF; // -0x41104111
    const int MAGIC2 = 0xEAC15A55; // -0x153ea5ab
    const int MAGIC3 = 0x91100911; // -0x6eeff6ef

    int* packet;
    int localBuf[2]; // temporary buffer
    byte localByte;  // unused padding

    // If a pending packet exists (flag bit0 set and pointer non-null), reset the local buffer and return early
    if ((*flag & 1) != 0 && *pendingPacket != 0)
    {
        localBuf[0] = *pendingPacket;
        localBuf[1] = 0;
        localByte = 0;
        // Clear the local buffer (probably to indicate no pending send)
        FUN_00408a00(localBuf, 0);
        return;
    }

    // Allocate a new reliable packet (type 1)
    packet = (int*)FUN_008e63b0(1);
    if (packet != 0)
    {
        // Check if the current GUID is neither the invalid magic marker nor all zeros
        if ( (guid[0] != MAGIC0 || guid[1] != MAGIC1 || guid[2] != MAGIC2 || guid[3] != MAGIC3) &&
             (guid[0] != 0    || guid[1] != 0    || guid[2] != 0    || guid[3] != 0) )
        {
            // Free/destroy the old GUID payload before reusing the slot
            FUN_008e24f0(guid);
        }
        // Send the packet with the given message ID and two zero flags (ack? sequence?)
        FUN_008e6780(packet, messageId, 0, 0);
    }
}
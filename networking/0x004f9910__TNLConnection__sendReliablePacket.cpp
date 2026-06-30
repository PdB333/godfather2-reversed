// FUNC_NAME: TNLConnection::sendReliablePacket
void TNLConnection::sendReliablePacket(int thisPtr, uint32_t packetFlags)
{
    // Local buffer for packet header or serialization scratch space (12 bytes)
    char tempBuffer[12];
    // Unused global read – likely a static pointer to a resource manager or allocator
    uint32_t globalValue = DAT_00e2b1a4;

    // Initialize internal state (e.g., lock mutex, acquire sequence number)
    initSequence();

    // Build the reliable packet into the internal buffer at offset 0x40
    // +0x40 is probably the packet assembly area within the connection object
    buildReliablePacket(thisPtr + 0x40, tempBuffer, packetFlags);
}
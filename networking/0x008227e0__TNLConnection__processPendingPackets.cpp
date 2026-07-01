// FUNC_NAME: TNLConnection::processPendingPackets
void __thiscall TNLConnection::processPendingPackets(void* pStream) {
    // +0x3c: mPendingPacketCount (uint)
    uint packetCount = *(uint*)((char*)this + 0x3c);
    if (packetCount == 0) return;

    // Buffer for deserializing a single packet (size 0x13C = 316 bytes)
    char packetBuffer[316];

    for (uint i = 0; i < packetCount; i++) {
        // Deserialize next packet from stream into buffer
        uint packetHandle = readPacket(packetBuffer, pStream, 0);
        // Process the deserialized packet
        processPacket(packetHandle);
        // Advance stream to next packet (e.g., skip padding/header)
        advanceStream();
    }
}
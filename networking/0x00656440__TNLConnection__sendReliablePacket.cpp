// FUNC_NAME: TNLConnection::sendReliablePacket
void TNLConnection::sendReliablePacket(void)
{
    // Stack buffer for packet data (1024 bytes)
    uint8_t packetBuffer[1024];
    uint8_t* packetBufferPtr = packetBuffer;

    // Packet size limits
    uint32_t maxPacketSize = 0x2000; // 8192 bytes
    uint32_t maxPacketSize2 = 0x2000;
    uint32_t headerSize = 0x400; // 1024 bytes

    // Bit count for serialization (masked to align)
    uint32_t bitCount = bitCount & 0xffffff00;
    uint32_t somethingZero = 0;
    uint8_t flag1 = 0;
    uint8_t flag2 = 0;
    uint8_t packetBufferEnd = 0;
    uint32_t unknownField = 0;

    // Pointer to a global vtable or static data (likely packet header template)
    void** headerTemplate = &PTR_LAB_00e42f38;
    uint8_t templateType = 4;

    // Write template type (8 bytes) into bitstream
    FUN_0064b810(8, &templateType);

    // Read field at this+0xA4 (likely sequence number or connection state)
    uint32_t sequenceField = this->field_0xA4;
    // Write 32-bit field into bitstream
    FUN_0064b810(0x20, &sequenceField);

    // Call virtual method at vtable+0x28 (likely writePacketHeader)
    // Pass pointer to headerTemplate
    (this->vtable[0x28])(&headerTemplate);

    // Send the packet: unaff_retaddr+0x5c is probably a socket or connection handle,
    // auStack_404 is a 4-byte buffer (maybe address), bitCount/8 is byte length, 1 is flags
    FUN_00658230(unaff_retaddr + 0x5c, auStack_404, (bitCount + 7) >> 3, 1);

    // Cleanup or finalize
    FUN_0064b440();
}
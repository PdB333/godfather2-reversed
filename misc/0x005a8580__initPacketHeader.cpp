//FUNC_NAME: initPacketHeader
void __fastcall initPacketHeader(uint32_t* packetHeader, uint32_t sequenceNumber)
{
    // Initialize packet header flags:
    // - Keep bits 0,2,15-31 from existing flags (though typically called on uninitialized memory)
    // - Set bits 0 and 2 (0x5) to indicate packet type (e.g., reliable + sequenced)
    // - Clear bits 1,3-14 (low 16 bits) and high 16 bits via the word write
    // - Set bit 15 (0x8000) as a marker (e.g., "has sequence" or "ack requested")
    // - Store sequence number at offset +0x04
    *packetHeader = (*packetHeader & 0xFFFF8005) | 5;
    *(uint16_t*)((uint8_t*)packetHeader + 2) = 0;   // Clear high 16 bits (offset +0x02)
    *packetHeader |= 0x8000;                        // Set bit 15
    packetHeader[1] = sequenceNumber;               // Sequence number at +0x04
}
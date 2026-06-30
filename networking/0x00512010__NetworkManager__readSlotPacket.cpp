// FUNC_NAME: NetworkManager::readSlotPacket
void __fastcall NetworkManager::readSlotPacket(uint32_t *outData, int slotIndex)
{
    // Get the network manager base pointer from Thread Local Storage (TLS)
    // FS:0x2c contains a pointer to a pointer to the manager singleton
    int **tlsPtr = (int **)__readfsdword(0x2c);
    int *managerBase = *tlsPtr;                       // NetworkManager singleton

    // Slot table starts at managerBase+0x08
    uint8_t *slotTable = (uint8_t *)(managerBase[2]); // +0x08: array of 0x50-byte slot structures

    // Global offset into each slot where the packet data begins (register variable from caller)
    int packetOffset = g_packetDataOffset;            // replaced *unaff_EDI

    // Calculate the base address of the packet data for the given slot
    uint8_t *slotBase = slotTable + slotIndex * 0x50;
    uint8_t *packetBase = slotBase + 0x20 + packetOffset;

    // Copy the first 12 DWORDs (0x30 bytes) sequentially from packetBase
    outData[0]  = *(uint32_t *)(packetBase + 0x00);
    outData[1]  = *(uint32_t *)(packetBase + 0x04);
    outData[2]  = *(uint32_t *)(packetBase + 0x08);
    outData[3]  = *(uint32_t *)(packetBase + 0x0C);
    outData[4]  = *(uint32_t *)(packetBase + 0x10);
    outData[5]  = *(uint32_t *)(packetBase + 0x14);
    outData[6]  = *(uint32_t *)(packetBase + 0x18);
    outData[7]  = *(uint32_t *)(packetBase + 0x1C);
    outData[8]  = *(uint32_t *)(packetBase + 0x20);
    outData[9]  = *(uint32_t *)(packetBase + 0x24);
    outData[10] = *(uint32_t *)(packetBase + 0x28);
    outData[11] = *(uint32_t *)(packetBase + 0x2C);

    // Additional fields at fixed offsets from packetBase
    outData[12] = *(uint32_t *)(packetBase + 0x38);   // +0x38
    outData[14] = *(uint32_t *)(packetBase + 0x4C);   // +0x4C

    // Read from a separate integer array indexed by slotIndex*4 + packetOffset
    // This array is located at the beginning of slotTable (same base as slotTable)
    outData[13] = *(uint32_t *)(slotTable + slotIndex * 4 + packetOffset);

    // Read a 32-bit value at packetBase+0x3C and a byte at +0x3F, combine with byte swap
    uint32_t raw = *(uint32_t *)(packetBase + 0x3C);
    uint8_t lastByte = *(uint8_t *)(packetBase + 0x3F);
    uint32_t swapped = ( (raw << 16) | (raw & 0xFF00) | ((raw >> 16) & 0xFF) ) << 8 | lastByte;
    outData[15] = swapped;
}
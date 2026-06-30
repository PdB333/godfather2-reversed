// FUNC_NAME: DataSlot::resolve
uint32_t* __thiscall DataSlot::resolve(DataSlot* this, ContextManager* context) {
    uint32_t slotIndex = *(uint32_t*)this; // +0x00: slot index
    uint32_t* defaultBuffer = (uint32_t*)DAT_01205584;

    if (slotIndex == 0) {
        // Slot 0: copy entire 64-byte data block from this to default buffer
        defaultBuffer[0] = ((uint32_t*)this)[0];
        defaultBuffer[1] = ((uint32_t*)this)[1];
        defaultBuffer[2] = ((uint32_t*)this)[2];
        defaultBuffer[3] = ((uint32_t*)this)[3];
        defaultBuffer[4] = ((uint32_t*)this)[4];
        defaultBuffer[5] = ((uint32_t*)this)[5];
        defaultBuffer[6] = ((uint32_t*)this)[6];
        defaultBuffer[7] = ((uint32_t*)this)[7];
        defaultBuffer[8] = ((uint32_t*)this)[8];
        defaultBuffer[9] = ((uint32_t*)this)[9];
        defaultBuffer[10] = ((uint32_t*)this)[10];
        defaultBuffer[11] = ((uint32_t*)this)[11];
        defaultBuffer[12] = ((uint32_t*)this)[12];
        defaultBuffer[13] = ((uint32_t*)this)[13];
        defaultBuffer[14] = ((uint32_t*)this)[14];
        defaultBuffer[15] = ((uint32_t*)this)[15];
        return defaultBuffer;
    }

    // Check context's slot-to-table mapping
    uint8_t* slotMap = (uint8_t*)*(uint32_t*)((uint8_t*)context + 0xB4); // +0xB4: pointer to 256-byte byte array mapping slot indices
    if (slotMap != NULL) {
        uint8_t tableIndex = slotMap[slotIndex & 0xFF]; // mask? likely slotIndex is within 0..255
        if (tableIndex != 0xFF) {
            // Return pointer into global table (each entry is 0x40 bytes)
            return (uint32_t*)((uint8_t*)_DAT_01205580 + tableIndex * 0x40);
        }
    }

    // Fallback: return offset into default buffer
    return (uint32_t*)((uint8_t*)defaultBuffer + slotIndex * 0x10); // 16 bytes per slot?
}
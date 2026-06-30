// FUNC_NAME: DataSyncManager::ApplyMaskedUpdate
void __thiscall DataSyncManager::ApplyMaskedUpdate(int numSlots, char* maskData, uint32_t* sourceData) {
    uint32_t* currentSlot = reinterpret_cast<uint32_t*>(this);  // "this" points to an array of slots, each 8 uint32s (32 bytes)
    uint32_t* endSlot = currentSlot + numSlots * 8;              // End pointer for the slot array
    if (currentSlot == endSlot) {                                // Empty slot list – nothing to do
        return;
    }
    do {
        // Copy only if mask is null (meaning all slots are considered dirty) or the current mask byte is 0x02
        if (maskData == nullptr || *maskData == '\x02') {
            // Transfer one slot (8 uint32s) from the source stream into the current slot
            currentSlot[0] = sourceData[0];
            currentSlot[1] = sourceData[1];
            currentSlot[2] = sourceData[2];
            currentSlot[3] = sourceData[3];
            currentSlot[4] = sourceData[4];
            currentSlot[5] = sourceData[5];
            currentSlot[6] = sourceData[6];
            currentSlot[7] = sourceData[7];
            sourceData += 8;   // Advance source only when data is copied
        }
        currentSlot += 8;      // Always move to the next slot
        maskData++;            // Advance the mask pointer
    } while (currentSlot != endSlot);
}
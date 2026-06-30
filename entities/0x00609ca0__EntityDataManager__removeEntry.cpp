// FUNC_NAME: EntityDataManager::removeEntry

// Global array of 12-byte structures (3 dwords each) for entity data slots.
// kEntitySlotArray: base address of the array (starts at DAT_01222328)
// g_entitySlotCount: current number of valid slots (at DAT_012224a8)
// Each slot: 8 bytes (likely a pointer) + 4 bytes (likely flags or ID)

static unsigned int g_entitySlotCount;          // Address 0x012224a8
static unsigned int* kEntitySlotArray;          // Address 0x01222328 (treated as dword array for index arithmetic)

void __fastcall EntityDataManager::removeEntry(int unusedParam, unsigned int slotIndex)
{
    unsigned int slotCount = g_entitySlotCount;
    if (slotIndex < slotCount)
    {
        // Shift all following slots left by one (each slot is 12 bytes = 3 dwords)
        if (slotIndex < slotCount - 1)
        {
            // Pointer to the start of the slot to remove
            unsigned int* currentSlotDwords = &kEntitySlotArray[slotIndex * 3];
            // 8 bytes (first two dwords of slot) are copied from the next slot's first 8 bytes
            // Actually, we copy two dwords: from offset 3 dwords ahead (12 bytes) and then the third dword from offset 5 dwords ahead (20 bytes)
            // The loop moves each slot's 3 dwords down
            do
            {
                currentSlotDwords[0] = currentSlotDwords[3]; // copy dword0 of next slot
                currentSlotDwords[1] = currentSlotDwords[4]; // copy dword1 of next slot
                currentSlotDwords[2] = currentSlotDwords[5]; // copy dword2 of next slot
                slotIndex++;
                currentSlotDwords += 3;
            } while (slotIndex < slotCount - 1);
        }
        // Decrement count and clear the now-empty last slot
        g_entitySlotCount = slotCount - 1;
        unsigned int lastSlotIndex = g_entitySlotCount;
        // Zero out the last slot (three dwords)
        kEntitySlotArray[lastSlotIndex * 3] = 0;       // dword0
        kEntitySlotArray[lastSlotIndex * 3 + 1] = 0;   // dword1
        kEntitySlotArray[lastSlotIndex * 3 + 2] = 0;   // dword2
    }
}
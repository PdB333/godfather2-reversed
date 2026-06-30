// FUN_NAME: SlotManager::releaseSlot
void __thiscall SlotManager::releaseSlot(void* slotTable, uint slotIndex)
{
    // slotIndex must be < 64 (max slots)
    if (slotIndex >= 64)
        return;

    // 64-bit bit mask representing allocated slots
    uint64_t bitMask = 1ULL << slotIndex;

    uint32_t* lowMaskPtr = (uint32_t*)((uint8_t*)this + 0x148);   // +0x148: low 32 bits of allocated slots
    uint32_t* highMaskPtr = (uint32_t*)((uint8_t*)this + 0x14c); // +0x14c: high 32 bits of allocated slots

    uint32_t lowMask = *lowMaskPtr;
    uint32_t highMask = *highMaskPtr;

    // Check if the slot bit is set (in either low or high part)
    if ((lowMask & (uint32_t)bitMask) != 0 ||
        (highMask & (uint32_t)(bitMask >> 32)) != 0)
    {
        // Clear the slot bit
        *lowMaskPtr = lowMask & ~(uint32_t)bitMask;
        *highMaskPtr = highMask & ~(uint32_t)(bitMask >> 32);

        // slotTable + 4 points to the beginning of the slot array (each slot 0x1c bytes)
        uint8_t* slotArray = *(uint8_t**)((uint8_t*)slotTable + 4); // +0x4: pointer to slot array
        void* slot = slotArray + slotIndex * 0x1c;                  // each slot is 28 bytes

        // Call cleanup / destructor for this slot
        FUN_0043c960(slot);

        // If the slot's refcount or type fields are zero, mark it as freed
        uint32_t field4  = *(uint32_t*)((uint8_t*)slot + 0x04);  // +0x4: some field
        uint32_t field10 = *(uint32_t*)((uint8_t*)slot + 0x10);  // +0x10: some field
        if (field10 == 0 && field4 == 0)
        {
            *(uint32_t*)slot = 0xFFFFFFFF;  // +0x0: mark as invalid
        }
    }
}
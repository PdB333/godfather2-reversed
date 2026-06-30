// FUNC_NAME: PoolAllocator::allocateSlot
uint32_t PoolAllocator::allocateSlot(uint32_t preferredIndex)
{
    // Global pool data (singleton)
    // DAT_011d917c: pointer to CRITICAL_SECTION for thread safety
    // DAT_011d9128: next group index to start search from (0-63)
    // DAT_011d8f28, DAT_011d8f2c: 64-bit bitmap per group (64 groups, each covering 64 slots)
    // DAT_011a0f28: base of slot array, each slot 0x38 bytes, first byte = 0 free, 1 used
    // Slot count: 0x1000 (4096) slots

    CRITICAL_SECTION* cs = (CRITICAL_SECTION*)DAT_011d917c;
    EnterCriticalSection(cs);
    LeaveCriticalSection(cs); // Note: This seems redundant; maybe a debug check?

    uint32_t groupIndex = DAT_011d9128;
    uint32_t index = preferredIndex;

    if (index == 0xFFFFFFFF)
    {
        // No preferred index: search for a free slot starting from current group
        while (groupIndex < 64)
        {
            uint32_t bitmapLow = DAT_011d8f28[groupIndex * 2];
            uint32_t bitmapHigh = DAT_011d8f2c[groupIndex * 2];
            if (bitmapLow == 0 && bitmapHigh == 0)
            {
                // Group is full (all bits set? Actually bits are 1 for free, 0 for used? Wait: code checks if both zero, meaning no free slots)
                // Actually the bitmap tracks free slots: 1 = free, 0 = used. So if both zero, group is full.
                groupIndex++;
                continue;
            }
            // Found a group with free slots; compute base index for this group
            index = groupIndex * 64;
            if (index >= 0x1000)
                break;

            // Scan slots in this group
            char* slotPtr = (char*)(DAT_011a0f28 + index * 0x38);
            for (uint32_t i = 0; i < 64; i++)
            {
                if (index >= 0x1000)
                    break;
                if (*slotPtr == '\0') // slot is free
                {
                    // Found free slot
                    break;
                }
                index++;
                slotPtr += 0x38;
            }
            if (index < 0x1000)
                break;
            groupIndex++;
        }
        if (index == 0x1000)
        {
            // No free slot found
            return 0xFFFFFFFF;
        }
    }

    if (index < 0x1000)
    {
        char* slotPtr = (char*)(DAT_011a0f28 + index * 0x38);
        if (slotPtr != nullptr && *slotPtr == '\0')
        {
            uint32_t group = index >> 6; // divide by 64
            uint32_t bitInGroup = index & 0x3F;

            // Clear the bit in the bitmap (mark slot as used)
            uint64_t bitMask = (uint64_t)1 << bitInGroup;
            uint32_t maskLow = (uint32_t)bitMask;
            uint32_t maskHigh = (uint32_t)(bitMask >> 32);

            EnterCriticalSection(cs);
            LeaveCriticalSection(cs); // Again redundant? Possibly for synchronization

            DAT_011d8f28[group * 2] &= ~maskLow;
            DAT_011d8f2c[group * 2] &= ~maskHigh;

            // If this group was the starting group and is now full, advance start
            if (group == DAT_011d9128 &&
                DAT_011d8f28[group * 2] == 0 &&
                DAT_011d8f2c[group * 2] == 0)
            {
                DAT_011d9128 = group + 1;
            }

            // Mark slot as used and clear additional field at offset 0x10
            *slotPtr = '\x01';
            *(uint32_t*)(slotPtr + 0x10) = 0;

            return index;
        }
    }
    return 0xFFFFFFFF;
}
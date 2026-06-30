// FUNC_NAME: ObjectPool::findNextFreeSlot

uint __thiscall ObjectPool::findNextFreeSlot(uint startIndex)
{
    // Global pool manager, provides maximum slot count at offset 0x0c
    // This pointer is checked for null before use
    extern PoolManager* g_poolManager;  // DAT_012233a0

    if (!g_poolManager)
        return 0xFFFFFFFF;

    uint maxSlots = *(uint*)((int)g_poolManager + 0x0C);  // +0x0C
    if (startIndex >= maxSlots)
        return 0xFFFFFFFF;

    // Free list: count and array stored in this object
    uint freeCount = *(uint*)(this + 0x154);   // +0x154
    uint* freeList = (uint*)(this + 0x158);    // +0x158

    do {
        uint i = 0;
        uint foundIndex = 4;  // sentinel value (invalid)

        if (freeCount != 0) {
            uint* current = freeList;
            do {
                foundIndex = i;
                if (*current == startIndex)
                    break;
                i++;
                current++;
                foundIndex = 4;  // reset to sentinel on each iteration?
            } while (i < freeCount);
        }

        if (foundIndex < freeCount) {
            // startIndex is in the free list -> return it as available
            return startIndex;
        }

        // Not found, try next slot
        startIndex++;
        if (startIndex >= maxSlots)
            return 0xFFFFFFFF;
    } while (true);
}
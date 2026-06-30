// FUNC_NAME: InputSlotManager::findSlotForDeviceId
uint __thiscall InputSlotManager::findSlotForDeviceId(uint deviceId)
{
    // Global mutex lock for thread safety (DAT_00e2cbe8)
    mutexLock(&g_globalMutex);

    uint slotCount = *(uint *)(this + 0x328); // Number of slots
    uint slotIndex = 0;
    uint result = 0xFFFFFFFF;

    if (slotCount == 0)
    {
        mutexUnlock();
        return result;
    }

    // Array of pointers to slot data structures at offset +0x228
    int *slotPtrArray = (int *)(this + 0x228);
    do
    {
        int *slotData = (int *)*slotPtrArray; // Each slot data structure
        uint entryCount = *(uint *)(slotData + 0x104 / 4); // +0x104: number of entries in this slot
        uint entryIndex = 0;
        if (entryCount != 0)
        {
            do
            {
                // Inner array starts at offset +4 from slotData (each entry is 4 bytes)
                if (*(int *)((int)slotData + 4 + entryIndex * 4) == (int)deviceId)
                {
                    result = slotIndex;
                    if ((int)entryIndex >= 0) // Always true; signals found
                    {
                        goto FOUND;
                    }
                    break;
                }
                entryIndex++;
            } while (entryIndex < entryCount);
        }
        slotIndex++;
        slotPtrArray++; // Move to next slot pointer
        if (slotIndex >= slotCount)
        {
            mutexUnlock();
            return 0xFFFFFFFF;
        }
    } while (true);

FOUND:
    mutexUnlock();
    return result;
}
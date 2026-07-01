// FUNC_NAME: EntityTimestampManager::updateTimestampEntry
void __thiscall EntityTimestampManager::updateTimestampEntry(int thisPtr, int objectPtr)
{
    uint currentCount;
    int id;
    uint idx;
    int *entryPtr;

    // Global timestamp value (likely current frame counter or time)
    int currentTimestamp = g_currentFrame; // DAT_01205228

    if (objectPtr != 0) {
        // Read ID from object at offset 0x50
        id = *(int *)(objectPtr + 0x50); // +0x50: object's unique ID

        currentCount = *(uint *)(thisPtr + 0x11C); // +0x11C: number of entries in the list
        idx = 0;

        // Search for existing entry with matching ID
        if (currentCount != 0) {
            entryPtr = (int *)(thisPtr + 0x5C); // +0x5C: start of entry array
            do {
                if (*entryPtr == id) {
                    // Update timestamp fields for existing entry
                    entryPtr[1] = currentTimestamp; // startTime
                    entryPtr[2] = currentTimestamp; // endTime
                    return;
                }
                idx = idx + 1;
                entryPtr = entryPtr + 3;
            } while (idx < currentCount);
        }

        // If list full (max 16 entries), report error
        if (currentCount > 0xF) {
            debugLogError(0); // FUN_0077d900 - likely asserts or logs overflow
        }

        // Add new entry at the end
        entryPtr = (int *)(thisPtr + 0x5C + currentCount * 0xC);
        *(int *)(thisPtr + 0x11C) = currentCount + 1;
        *entryPtr = id;
        entryPtr[1] = currentTimestamp;
        entryPtr[2] = currentTimestamp;
    }
}
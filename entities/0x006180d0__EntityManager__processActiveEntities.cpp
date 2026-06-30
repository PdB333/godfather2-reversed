// FUNC_NAME: EntityManager::processActiveEntities
void __fastcall EntityManager::processActiveEntities(int *thisPtr)
{
    int count;
    unsigned int index;
    int *entryPtr;
    unsigned int currentCount;

    // Check if the context pointer (offset +0x04) is non-null
    if (thisPtr[1] != 0) {
        index = 0;
        // Call virtual function at vtable+0x10 to get the number of active entries
        count = (**(code **)(*thisPtr + 0x10))();
        if (count != 0) {
            // Start of the entry array at offset +0x14 (thisPtr + 5 ints)
            entryPtr = thisPtr + 5;
            do {
                // If the entry pointer (first field of each 20-byte struct) is non-null
                if (*entryPtr != 0) {
                    // Call processing function with context, entry pointer, and global data
                    FUN_0060add0(thisPtr[1], *entryPtr, &DAT_01225db0);
                }
                index = index + 1;
                // Advance to next entry (each entry is 5 ints = 20 bytes)
                entryPtr = entryPtr + 5;
                // Re-fetch count in case it changed during processing
                currentCount = (**(code **)(*thisPtr + 0x10))();
            } while (index < currentCount);
        }
    }
    return;
}
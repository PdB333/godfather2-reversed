// FUN_0047c0e0: MissionObjectiveManager::processEntries
// Purpose: Iterates over a list of resource/hash entries, filters, and populates internal lists at +0x3c and +0x50.
// The iteration can be in two modes: linked-list mode (bUseArrayMode = false) or array-with-bitmap mode (bUseArrayMode = true).
// Entry tag at +6: if 0x25e3, data is stored as a short offset; else as a full pointer.
void __thiscall MissionObjectiveManager::processEntries(uint resourceId)
{
    const uint HASH_MAGIC = 0x18fcbf35; // CRC or string hash constant
    const uint TAG_SHORT = 0x25e3; // Identifier for short-offset entries

    int* pListPtr; // Temporary pointer to list at +0x50
    undefined4* dataPtr;
    undefined4 result;
    Entry** currentEntry; // Pointer to current entry in iteration
    uint index; // Current index in current iteration mode
    undefined4** entryIter; // General iteration variable

    // Context variables initialized by FUN_0043aff0 (likely global resource table iteration)
    Entry* iterContext = initializeResourceIteration(resourceId, HASH_MAGIC);
    // The decompiler shows these locals, but in reality FUN_0043aff0 sets up the iteration state.
    // (local_64, local_8, local_58, local_54, etc.) This is a simplification.
    // For readability, we directly use the iterContext's members.
    bool bUseArrayMode = iterContext->bArrayMode;
    Entry** currentEntryPtr = iterContext->startPtr;
    uint currentIndex = iterContext->currentIndex;
    uint count = iterContext->count;
    // Additional state for array mode:
    char* bitmapBase = iterContext->bitmap; // Used for bitmask iteration
    undefined4** dataArray = iterContext->dataArray; // Array of pointers
    Entry* entryData;
    undefined4 entryId;
    undefined2 shortIndex;

    while (true)
    {
        // Check if we've reached the end of the iteration
        bool endReached;
        if (!bUseArrayMode)
        {
            endReached = (*currentEntryPtr == nullptr);
        }
        else
        {
            endReached = (currentIndex == count);
        }
        if (endReached) break;

        // Determine the actual entry pointer
        Entry* entry;
        if (!bUseArrayMode)
        {
            entry = *currentEntryPtr;
        }
        else
        {
            entry = entryData; // Already set (see below)
        }

        // Check tag to decide how to fetch data pointer
        if (*(short*)((char*)entry + 6) == TAG_SHORT)
        {
            // Short offset: data is an offset packed as ushort
            dataPtr = (undefined4*)(uint)*(ushort*)((char*)entry + 2);
        }
        else
        {
            dataPtr = (undefined4*)entry[1]; // entry[1] is a pointer (if entry is array of undefined4)
        }

        if (dataPtr == nullptr)
        {
            // No data -> reset the list at +0x50 and optionally add a new item
            entry = (!bUseArrayMode) ? *currentEntryPtr : entryData;
            // Determine new data source for the reset operation
            const char* newData;
            if (*(short*)((char*)entry + 6) == TAG_SHORT)
            {
                if (*entry == nullptr)
                {
                    newData = (const char*)0x00e2a89b; // global empty string address
                }
                else
                {
                    newData = (const char*)((int)entry[2] + (int)*entry);
                }
            }
            else
            {
                newData = (const char*)(entry + 2);
            }

            int* listBegin = (int*)(this + 0x50);
            clearList(listBegin);         // FUN_004086d0
            resetList(listBegin);         // FUN_00408310

            // Reset iteration state (since we modified the list, the iteration context may change)
            currentEntryPtr = iterContext->startPtr;
            currentIndex = iterContext->currentIndex;

            if (newData != nullptr && *newData != '\0')
            {
                undefined4 converted = getHashFromString((void*)newData); // FUN_004dafd0
                addItemToList(listBegin, converted); // FUN_00408260
                currentEntryPtr = iterContext->startPtr; // reload (decompiler shows this)
                if (*listBegin != 0)
                {
                    // Insert the newly formed item into the main list at +0x3c
                    insertIntoMainList(this + 0x3c, listBegin); // FUN_00407e60
                    currentEntryPtr = iterContext->startPtr; // reload
                }
            }
        }
        else if (dataPtr == (undefined4*)0x1 && *(int*)(this + 0x58) == 0)
        {
            // Special case: first item of a particular type
            entry = (!bUseArrayMode) ? *currentEntryPtr : entryData;
            // Set the "current item" reference at +0x58
            if (*(short*)((char*)entry + 6) == TAG_SHORT)
            {
                if (*entry == nullptr)
                {
                    *(const char**)(this + 0x58) = (const char*)0x00e2a89b;
                }
                else
                {
                    *(int*)(this + 0x58) = (int)entry[2] + (int)*entry;
                }
            }
            else
            {
                *(undefined4***)(this + 0x58) = entry + 2;
            }
        }

        // Advance to next item
        if (!bUseArrayMode)
        {
            // Linked-list mode: entry points are chained via offsets
            if ((int)currentIndex < 0)
            {
                currentEntryPtr = (Entry**)((char*)currentEntryPtr + (int)*currentEntryPtr);
                // FUN_0043b140 is a placeholder (no-op?)
                currentEntryPtr = currentEntryPtr; // reload from local_8 (already updated)
                currentIndex = currentIndex; // keep
            }
            else if ((int)currentIndex < (int)(count - 1))
            {
                currentIndex++;
                currentEntryPtr = (Entry**)((char*)currentEntryPtr + (int)*currentEntryPtr);
            }
            else
            {
                currentEntryPtr = (Entry**)0x01163cf8; // sentinel end marker
            }
        }
        else
        {
            // Array mode: use bitmap to skip items
            currentIndex++;
            if (currentIndex != count)
            {
                shortIndex = (short)currentIndex;
                int byteIndex = currentIndex >> 3;
                int bitMask = 1 << (currentIndex & 7);
                if ((bitmapBase[byteIndex] & bitMask) == 0)
                {
                    // Present in array: read next entry from dataArray
                    entryId = *dataArray;
                    entryData = dataArray; // The entry is the pointer itself? Actually local_50 = dataArray (pointer to next)
                    dataArray++; // advance pointer
                }
                else
                {
                    entryData = nullptr;
                    entryId = 0;
                }
            }
        }
    }
    return;
}
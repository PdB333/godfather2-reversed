// FUNC_NAME: ConfigurationManager::parseDataBlock
void __thiscall ConfigurationManager::parseDataBlock(ConfigurationManager* this, const void* data) {
    uint32_t hashKey = 0xe041efe5;
    // Initialize hash/decryption context with the data and a magic key
    initHash(data, hashKey);

    // Iteration state
    char modeFlag;            // local_64: 0 = linked list traversal, non-zero = bitfield-masked array traversal
    uint32_t* bitfieldBase;   // local_60: pointer to bitfield array (when modeFlag != 0)
    uint32_t currentIndex;    // local_58: current index into the array (mode !=0) or iteration position (mode 0)
    uint32_t count;           // local_54: total number of entries (mode !=0)
    const void** currentEntryPtr; // local_8/ppuVar5: pointer to current entry (linked list mode)
    const void** arrayCursor; // local_5c: cursor into the raw array (mode !=0)
    const void* currentElement; // local_50: data of current entry
    uint32_t elementId;       // local_48: identifier or type of current entry
    uint16_t indexCopy;       // local_4c: temporary index (mode !=0)

    // The decompiled code uses an uninitialized local_8 at the beginning.
    // We assume that the data block starts with a header that provides initial pointers and mode.
    // For reconstruction we simulate proper initialization:
    // ... (omitted for clarity, but actual code must set these correctly)
    // In the original binary, these are likely set from the data block.

    // Loop over all entries
    while (true) {
        // Check termination condition
        bool shouldExit;
        if (modeFlag == '\0') {
            shouldExit = (*currentEntryPtr == nullptr);
        } else {
            shouldExit = (currentIndex == count);
        }
        if (shouldExit) {
            return;
        }

        // Determine the current element pointer
        const void** ppuVar3;
        if (modeFlag == '\0') {
            ppuVar3 = currentEntryPtr;
        } else {
            ppuVar3 = &currentElement;
        }

        // Extract the "next" pointer or data pointer from the entry
        const void* nextPtr;
        // Check a type field at offset +6
        if (*(int16_t*)((char*)ppuVar3 + 6) == 0x25e3) {
            // Special case: the pointer is stored as an offset (uint16) from the entry's base
            nextPtr = (const void*)(uintptr_t)*(uint16_t*)(ppuVar3 + 1);
        } else {
            // Normal case: pointer is the second field of the entry
            nextPtr = ppuVar3[1];
        }

        if (nextPtr == nullptr) {
            // Case: entry has no next pointer (or it's zero) – process as a "list item"
            const void** entryBase;
            if (modeFlag == '\0') {
                entryBase = currentEntryPtr;
            } else {
                entryBase = &currentElement;
            }

            // Determine the actual data location
            const void* dataPtr;
            if (*(int16_t*)((char*)entryBase + 6) == 0x25e3) {
                if (*entryBase == nullptr) {
                    dataPtr = (const void*)&DAT_00e2a89b; // default string
                } else {
                    dataPtr = (const void*)((int)entryBase[2] + (int)*entryBase);
                }
            } else {
                dataPtr = entryBase + 2; // skip the first two fields
            }

            // Access the list at +0x50
            uint32_t* list = (uint32_t*)((char*)this + 0x50);
            clearList(list);
            resetList(list);

            if (dataPtr != nullptr && *(char*)dataPtr != '\0') {
                const char* str = createStringFromPtr(dataPtr);
                addToList(list, str);
                if (*list != 0) {
                    addToSecondaryList((void*)((char*)this + 0x3C), list);
                }
            }
        } else if (nextPtr == (const void*)0x1) {
            // Case: entry marks a "single string" target
            const void** entryBase;
            if (modeFlag == '\0') {
                entryBase = currentEntryPtr;
            } else {
                entryBase = &currentElement;
            }

            const char* resultStr;
            if (*(int16_t*)((char*)entryBase + 6) == 0x25e3) {
                if (*entryBase == nullptr) {
                    resultStr = createStringFromPtr(&DAT_00e2a89b);
                    *(const char**)((char*)this + 0x58) = resultStr;
                    goto update_iteration; // jump to iteration update
                }
                entryBase = (const void**)((int)entryBase[2] + (int)*entryBase);
            } else {
                entryBase = entryBase + 2;
            }

            if (entryBase == nullptr) {
                *(const char**)((char*)this + 0x58) = nullptr;
            } else {
                resultStr = createStringFromPtr(entryBase);
                *(const char**)((char*)this + 0x58) = resultStr;
            }
        }

update_iteration:
        // Advance iteration depending on mode
        if (modeFlag == '\0') {
            // Linked list mode: advance by the size stored at beginning of current entry
            if ((int32_t)currentIndex < 0) {
                // Negative index: special case (re-point to next)
                currentEntryPtr = (const void**)((int)currentEntryPtr + (int)*currentEntryPtr);
                iterationHelper();
            } else if ((int32_t)currentIndex < (int32_t)(count - 1)) {
                currentIndex += 1;
                currentEntryPtr = (const void**)((int)currentEntryPtr + (int)*currentEntryPtr);
            } else {
                // End of list, set to sentinel
                currentEntryPtr = (const void**)&DAT_01163cf8;
            }
        } else {
            // Bitfield array mode: advance index and check bitmask
            currentIndex += 1;
            if (currentIndex != count) {
                indexCopy = (uint16_t)currentIndex;
                // Check if this index is present in the bitfield
                if ((*(uint8_t*)((currentIndex >> 3) + bitfieldBase) & (1 << (currentIndex & 7))) == 0) {
                    elementId = *arrayCursor;
                    currentElement = arrayCursor;
                    arrayCursor += 1;
                } else {
                    currentElement = nullptr;
                    elementId = 0;
                }
            }
        }
    }
}
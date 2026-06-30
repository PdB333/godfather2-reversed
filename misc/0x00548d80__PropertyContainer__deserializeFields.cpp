// FUNC_NAME: PropertyContainer::deserializeFields
// Function address: 0x00548d80
// Role: Deserializes a binary stream of field modifications into a PropertyContainer object.
// The stream can be either a linked list of entries (mode == 0) or a compact bitmask-driven array (mode != 0).
// Each entry contains a field index (0-9) and a value pointer. The function writes the pointer to the corresponding member offset.

void __thiscall PropertyContainer::deserializeFields(void* thisPtr, int mode, uint32_t* streamData)
{
    // thisPtr is unaff_EDI in the original decompilation
    int thisObj = (int)thisPtr;
    uint32_t currentBit = 0;
    uint32_t* dataPtr = streamData;
    uint32_t* entryBuffer;          // local_5c
    uint32_t entryArrayIndex;       // local_58
    uint32_t entryCount;            // local_54
    uint32_t* currentEntry;         // local_50
    uint32_t* listPtr;              // local_8
    uint32_t local_48;
    uint16_t local_4c;
    bool done = false;

    FUN_0043aff0(thisPtr, 0x50f03f03); // Initialize some internal state

    while (!done)
    {
        if (mode == 0)
        {
            // Linked list mode
            done = (*listPtr == 0);
        }
        else
        {
            // Compact mode: check if we've processed all entries
            done = (currentBit == entryCount);
        }

        if (done) break;

        // Get current entry pointer
        if (mode == 0)
        {
            currentEntry = listPtr;
        }
        else
        {
            currentEntry = &entryBuffer; // Actually points to local_50, but structure is different
        }

        // Extract field type from the entry
        uint32_t fieldType;
        if (mode == 0 && *(int16_t*)((int)listPtr + 6) == 0x25e3)
        {
            // Special case: field type is encoded as a 16-bit value at +6
            fieldType = (uint16_t)*(uint16_t*)(listPtr + 1);
        }
        else
        {
            fieldType = currentEntry[1];
        }

        // Write the value (currentEntry[2]) to the appropriate field offset
        switch (fieldType)
        {
        case 0:
            *(uint32_t**)(thisObj + 0x2c) = (uint32_t*)currentEntry[2];
            break;
        case 1:
            *(uint32_t**)(thisObj + 8) = (uint32_t*)currentEntry[2];
            break;
        case 2:
            *(uint32_t**)(thisObj + 0xc) = (uint32_t*)currentEntry[2];
            break;
        case 3:
            *(uint32_t**)(thisObj + 0x10) = (uint32_t*)currentEntry[2];
            break;
        case 4:
            *(uint32_t**)(thisObj + 0x14) = (uint32_t*)currentEntry[2];
            break;
        case 5:
            *(uint32_t**)(thisObj + 0x18) = (uint32_t*)currentEntry[2];
            break;
        case 6:
            *(uint32_t**)(thisObj + 0x1c) = (uint32_t*)currentEntry[2];
            break;
        case 7:
            *(uint32_t**)(thisObj + 0x20) = (uint32_t*)currentEntry[2];
            break;
        case 8:
            *(uint32_t**)(thisObj + 0x24) = (uint32_t*)currentEntry[2];
            break;
        case 9:
            *(uint32_t**)(thisObj + 0x28) = (uint32_t*)currentEntry[2];
            break;
        }

        // Advance to next entry
        if (mode == 0)
        {
            if ((int)currentBit < 0)
            {
                // Negative index: follow the linked list forward (offset encoded in *listPtr)
                listPtr = (uint32_t*)((int)listPtr + (int)*listPtr);
                FUN_0043b140(); // Internal rewind or recheck
                currentBit = entryArrayIndex; // Actually local_58, but likely a sync
            }
            else if ((int)currentBit < (int)(entryCount - 1))
            {
                listPtr = (uint32_t*)((int)listPtr + (int)*listPtr);
                entryArrayIndex = currentBit + 1;
                currentBit = entryArrayIndex;
            }
            else
            {
                // End of list: reset to a sentinel (DAT_01163cf8)
                listPtr = (uint32_t*)0x01163cf8;
                listPtr = (uint32_t*)0x01163cf8;
                // Note: double assignment suggests a bug or intentional sentinel
            }
        }
        else
        {
            // Compact mode: advance currentBit and check if we need to skip due to bitmask
            entryArrayIndex = currentBit + 1;
            currentBit = entryArrayIndex;
            if (currentBit != entryCount)
            {
                local_4c = (short)currentBit;
                // Check bitmask: if bit at position (currentBit) in array at dataPtr is 0, read next entry
                if ((*(uint8_t*)((currentBit >> 3) + (int)dataPtr) & (1 << (currentBit & 7))) == 0)
                {
                    entryBuffer = dataPtr;      // Actually local_5c
                    local_48 = *dataPtr;
                    dataPtr++;                  // Advance data pointer
                }
                else
                {
                    entryBuffer = 0;            // Skip this entry (null)
                    local_48 = 0;
                }
            }
        }
    }
}
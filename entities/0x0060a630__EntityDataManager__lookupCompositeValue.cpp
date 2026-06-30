// FUNC_NAME: EntityDataManager::lookupCompositeValue
// Address: 0x0060a630
// Role: Searches a collection of items by a key, returns a composite identifier built from multiple fields.
// The collection is an array of pointers at a global offset (gEntityTableBase + index*0x10).
// vtable[0x14] returns item count; vtable[0x20] returns a handle for a given index; vtable[0x18] fills an output structure (likely containing a type, priority, and an ID that is hashed via FUN_0060d740).

uint EntityDataManager::lookupCompositeValue(int tableIndex, int key)
{
    int* tablePtr;
    uint result;
    uint count;
    uint handle;
    uint loopIdx;
    uint composite;
    // Stack buffer for item data (8 bytes? Used by vtable call)
    char dataBuffer[8];
    uint countOut;          // +0x8 from dataBuffer
    int idRaw;              // +0xC: passed to FUN_0060d740
    uint priorityLow;       // +0x10
    uint priorityHigh;      // +0x14
    byte typeFlags;         // +0x18
    int itemType;           // +0x1c: condition to skip composite build (1 and 2 are excluded)

    // Global array of pointers to entity data sets (each entry 16 bytes)
    tablePtr = *(int**)(&gEntityDataSets + tableIndex * 0x10);
    count = 0;
    if (tablePtr != nullptr) {
        uint* countPtr = &countOut;  // pointer to a local used as output parameter
        // Get total number of items in this table
        (*(code**)(*tablePtr + 0x14))(tablePtr); // vtable call: getCount()? Actually it sets countOut via side effect? We'll assume it does.
        // Let's reassign count after call (the decompiler shows countOut used but not directly set; assume the call modifies it)
        count = countOut; // Actually countOut is global? No local. We'll keep as is.
        loopIdx = 0;
        if (countOut != 0) {
            do {
                // Get a handle for the current index
                handle = (**(code**)(**(int**)(&gEntityDataSets + tableIndex * 0x10) + 0x20))
                          (*(int**)(&gEntityDataSets + tableIndex * 0x10), 0, loopIdx);
                // Retrieve item data into the stack buffer and possibly update countPtr
                (**(code**)(**(int**)(&gEntityDataSets + tableIndex * 0x10) + 0x18))
                          (*(int**)(&gEntityDataSets + tableIndex * 0x10), handle, dataBuffer, &countPtr);
                // Hash the idRaw to get a comparable value
                int idHashed = FUN_0060d740(idRaw);
                if ((key == idHashed) && (result == 0)) {
                    result = handle; // First match stores the handle
                    if ((itemType != 1) && (itemType != 2)) {
                        // Build composite from various fields
                        composite = ((uint)typeFlags << 8 | priorityHigh) << 8;
                        // Consider global flag at gEntityDataFlags[tableIndex] to set sign bit
                        if (gEntityDataFlags[tableIndex] == 0) {
                            composite |= priorityLow;
                        } else {
                            composite |= 0x80000000 | priorityLow;
                        }
                        result = composite;
                    }
                }
                loopIdx++;
            } while (loopIdx < countOut);
        }
        return result;
    }
    return 0;
}
// FUNC_NAME: TaskManager::loadRecords
void __thiscall TaskManager::loadRecords(TaskManager* thisPtr, SmallRecord* sourceData, int recordCount, uint flags) {
    // Clear bit 0 of flags at +0x58
    *(uint*)((int)thisPtr + 0x58) &= 0xfffffffe;
    // Store new count and flags
    *(int*)((int)thisPtr + 0xc) = recordCount;
    *(uint*)((int)thisPtr + 0x14) = flags;

    if (recordCount != 0) {
        // Deallocate existing large array (element size 0x2c, at +0x08)
        if (*(int*)((int)thisPtr + 8) != 0) {
            operator delete[](*(void**)((int)thisPtr + 8));
        }
        // Allocate new large array (element size 0x2c)
        uint count = *(uint*)((int)thisPtr + 0xc);
        longlong sizeLl = (ulonglong)count * 0x2c;
        // Overflow-safe allocation: if multiplication overflows 32-bit, pass 0xFFFFFFFF
        uint size = -(uint)((int)((ulonglong)sizeLl >> 0x20) != 0) | (uint)sizeLl;
        void* newLargeArray = operator new[](size);
        if (newLargeArray != nullptr) {
            // Default construct each large element (constructor at 0x00897110)
            for (uint i = 0; i < count; ++i) {
                new ((char*)newLargeArray + i * 0x2c) LargeElement();
            }
        }
        *(void**)((int)thisPtr + 8) = newLargeArray;

        // Deallocate existing small array (element size 0x10, at +0x04)
        if (*(int*)((int)thisPtr + 4) != 0) {
            operator delete[](*(void**)((int)thisPtr + 4));
        }
        // Allocate new small array (element size 0x10)
        count = *(uint*)((int)thisPtr + 0xc);
        sizeLl = (ulonglong)count * 0x10;
        size = -(uint)((int)((ulonglong)sizeLl >> 0x20) != 0) | (uint)sizeLl;
        void* newSmallArray = operator new[](size);
        if (newSmallArray != nullptr) {
            // Default construct each small element (constructor at 0x008970c0)
            for (uint i = 0; i < count; ++i) {
                new ((char*)newSmallArray + i * 0x10) SmallRecord();
            }
        }
        *(void**)((int)thisPtr + 4) = newSmallArray;

        // Copy source data into small array (16 bytes per element)
        uint idx = 0;
        if (*(int*)((int)thisPtr + 0xc) != 0) {
            int offset = 0;
            do {
                SmallRecord* dest = (SmallRecord*)(*(int*)((int)thisPtr + 4) + offset);
                *dest = *(SmallRecord*)((int)sourceData + offset); // copy 16 bytes
                // Check bit 1 of the second 8-byte field (flags at offset 8)
                if ((*(uint*)((int)dest + 8) >> 1 & 1) != 0) {
                    *(int*)((int)thisPtr + 0x10) += 1; // increment counter
                }
                idx++;
                offset += 0x10;
            } while (idx < *(uint*)((int)thisPtr + 0xc));
        }

        // Post-processing helpers
        FUN_008963c0(); // Likely sorts or recalculates internal states
        FUN_00897370(); // Updates dependent data
    }
}
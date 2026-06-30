// FUNC_NAME: MemoryPool::init
void __thiscall MemoryPool::init(uint totalSize, int secondaryData, int somePointer)
{
    int* thisPtr = this;  // +0x00: field0
    uint count;
    int objectArrayBase;
    int i;
    int offset;

    thisPtr[0] = secondaryData;            // +0x00: secondary pointer
    thisPtr[1] = somePointer;              // +0x04: another pointer
    thisPtr[2] = totalSize;                // +0x08: total memory size for pool
    count = totalSize / 0x2A0;            // number of objects (each 0x2A0 bytes)
    thisPtr[4] = count;                   // +0x10: count
    thisPtr[7] = count;                   // +0x1C: duplicate count
    thisPtr[6] = count;                   // +0x18: yet another copy
    thisPtr[3] = 0x2A0;                   // +0x0C: element stride size
    thisPtr[8] = 0;                       // +0x20: some flag/state

    // Allocate and initialize array of objects, each with a sequential ID
    if (count != 1) {
        i = 0;
        do {
            uint currentId = i;          // 0-based, will become 1-based
            objectArrayBase = allocateBlock();  // returns base of allocated memory? (FUN_00513720)
            *(uint*)(objectArrayBase + i * 0x2A0) = currentId + 1;  // store ID (1..count)
            i++;
        } while (i < thisPtr[6] - 1);   // loop count-1 times
    }

    // Compute sentinel position
    offset = 0;
    if (thisPtr[0] != 0) {
        // Get some thread-local or heap base from FS segment, then add secondaryData
        offset = *(int*)(**(int**)(__readfsdword(0x2C) + 8) + thisPtr[0]);
    }
    // Write sentinel (-1) at the end of the object array
    *(int*)(thisPtr[6] * 0x2A0 - 0x2A0 + offset) = 0xFFFFFFFF;

    thisPtr[5] = 0;   // +0x14: some counter or flag
}
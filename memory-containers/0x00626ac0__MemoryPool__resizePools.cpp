// FUNC_NAME: MemoryPool::resizePools
void MemoryPool::resizePools() {
    // +0x40: largeBlockCount, +0x44: someStructPtr with flag at +5
    if ((*(int*)(this + 0x40) > 3) && ((*(byte*)(*(int*)(this + 0x44) + 5) & 0x11) == 0)) {
        FUN_00626640(); // flush/coalesce free list
    }

    uint largeBlockIdx = *(uint*)(this + 0x28); // +0x28: largeBlockStart (offset or pointer)
    int* largeBlockList = *(int**)(this + 0x08); // +0x08: base of small block list (2-int entries)
    int* activeSmallEnd = largeBlockList; // will track highest in-use small block pointer
    int* maxSmallPtr = largeBlockList;

    // Iterate over large blocks (size 0x18), find the maximum pointer stored at offset +4
    if (largeBlockIdx <= *(uint*)(this + 0x14)) { // +0x14: largeBlockEnd (offset)
        do {
            int** pSmallPtr = *(int***)(largeBlockIdx + 4); // pointer within large block
            if (maxSmallPtr < *pSmallPtr) {
                maxSmallPtr = *pSmallPtr;
                activeSmallEnd = *pSmallPtr;
            }
            largeBlockIdx += 0x18;
        } while (largeBlockIdx <= *(uint*)(this + 0x14));
    }

    // Iterate backward through small block list from current head to base, checking if any blocks are still in use
    int* smallBlockIter = *(int**)(this + 0x1c); // +0x1c: smallBlockHead
    if (smallBlockIter < largeBlockList) {
        do {
            if ((*smallBlockIter > 3) && ((*(byte*)(*(int*)(smallBlockIter[1]) + 5) & 0x11) == 0)) {
                FUN_00626640(); // coalesce
            }
            smallBlockIter += 2;
        } while (smallBlockIter < *(int**)(this + 0x08));
    }

    // Zero all small block entries from current head up to the highest found
    for (; smallBlockIter <= maxSmallPtr; smallBlockIter += 2) {
        *smallBlockIter = 0;
    }

    // ---- Reallocate large block list (size 0x18 elements) ----
    int oldLargeBase = *(int*)(this + 0x28); // +0x28: largeBlockStart
    ushort largeCount = *(ushort*)(this + 0x2c); // +0x2c: largeBlockCapacity
    int numLargeUsed = (*(int*)(this + 0x14) - oldLargeBase) / 0x18;

    if ((numLargeUsed * 4 < (int)(uint)largeCount) && (largeCount > 0x10)) {
        ushort newLargeCount = largeCount >> 1;
        uint newLargeSize = (uint)newLargeCount * 0x18;
        void* newLargeBase;
        if (newLargeSize == 0) {
            if (oldLargeBase != 0) {
                (*DAT_012059e0)(oldLargeBase); // free
                newLargeBase = 0;
            } else {
                newLargeBase = 0;
            }
        } else if (newLargeSize < 0xfffffffd) {
            newLargeBase = (*DAT_012059dc)(oldLargeBase, newLargeSize); // realloc
            if (newLargeBase == 0) {
                FUN_00635a80(); // error handler
                return;
            }
        } else {
            FUN_00633920(); // size too large
            newLargeBase = oldLargeBase;
        }

        // Adjust total memory counter in the manager struct pointed by +0x10
        int* totalMemPtr = (int*)(*(int*)(this + 0x10) + 0x24);
        *totalMemPtr = *totalMemPtr + (int)newLargeSize - (int)newLargeCount * 0x18; // actually: subtract old capacity and add new
        // The original code does: *totalMemPtr = *totalMemPtr + (uint)largeCount * -0x18; then + newLargeSize
        // Equivalent to subtract old and add new
        *totalMemPtr = *totalMemPtr + (int)newLargeSize - (int)largeCount * 0x18;

        *(int*)(this + 0x14) = (int)newLargeBase + numLargeUsed * 0x18; // +0x14: largeBlockEnd
        *(ushort*)(this + 0x2c) = newLargeCount;
        *(int*)(this + 0x28) = (int)newLargeBase; // +0x28: largeBlockStart
        *(uint*)(this + 0x24) = (uint)newLargeBase + (uint)newLargeCount * 0x18; // +0x24: largeBlockCapacityEnd

        // Update maxSmallPtr after potential relocation (note: pointer values might have changed, but we keep local copy)
        maxSmallPtr = activeSmallEnd;
    }

    // ---- Reallocate small block list (size 8 elements) ----
    int oldSmallBase = *(int*)(this + 0x1c); // +0x1c: smallBlockHead
    int smallCount = *(int*)(this + 0x20); // +0x20: smallBlockCapacity

    // Condition: if capacity <= (maxPtr - oldSmallBase)/8*4 OR capacity < 121, skip
    if ((smallCount <= ((int)maxSmallPtr - oldSmallBase >> 3) * 4) || (smallCount < 0x79)) {
        return;
    }

    int newSmallCount = smallCount / 2;
    uint newSmallSize = newSmallCount * 8;
    void* newSmallBase;
    if (newSmallSize == 0) {
        if (oldSmallBase != 0) {
            (*DAT_012059e0)(oldSmallBase);
            newSmallBase = 0;
        } else {
            newSmallBase = 0;
        }
    } else if (newSmallSize < 0xfffffffd) {
        newSmallBase = (*DAT_012059dc)(oldSmallBase, newSmallSize);
        if (newSmallBase == 0) {
            FUN_00635a80();
            return;
        }
    } else {
        FUN_00633920();
        newSmallBase = oldSmallBase;
    }

    // Adjust total memory counter
    int* totalMemPtr = (int*)(*(int*)(this + 0x10) + 0x24);
    *totalMemPtr = *totalMemPtr + (int)newSmallSize - smallCount * 8;

    // +0x18 seems to be an end-of-small‑block sentinel or offset
    *(int*)(this + 0x18) = oldSmallBase - 0xa8 + newSmallCount * 8;
    *(int*)(this + 0x1c) = (int)newSmallBase; // smallBlockHead
    *(int*)(this + 0x20) = newSmallCount;     // new capacity

    FUN_00635b50(); // reinitialize free list or defragment
}
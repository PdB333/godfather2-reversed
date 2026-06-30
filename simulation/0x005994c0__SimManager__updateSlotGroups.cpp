// FUNC_NAME: SimManager::updateSlotGroups
void __thiscall SimManager::updateSlotGroups(uint* thisPtr, bool immediate, undefined4 param_3)
{
    // Offset mapping for this (uint* base):
    // +0x00: flags (bit0 cleared at end)
    // +0x04: m_context (pointer to some object)
    // +0x58: m_processGroup0Count (byte)
    // +0x59: m_processGroup0Indices[0] (byte array)
    // +0x79: m_processGroup1Count (byte)
    // +0x7A: m_processGroup1Indices[0] (byte array)
    // +0x9A: m_processGroup2Count (byte)
    // +0x9C: m_processGroup2Indices[0] (uint array? but treated as byte-stepped)
    // +0x1BC: m_slotManager (pointer to SlotManager)
    // +0x1C0: m_resourceManager (pointer)
    // +0x1C4: m_anotherManager (pointer)

    // SlotManager offsets (uVar2 base):
    // +0x14: array of object pointers for group0
    // +0x18: array of status ints for group0
    // +0x1C: free list head for group0
    // +0x20: array of object pointers for group1
    // +0x24: array of status ints for group1
    // +0x28: free list head for group1
    // +0x2C: array of object pointers for group2
    // +0x30: array of status ints for group2
    // +0x34: free list head for group2

    byte count;
    byte index;
    uint slotManager;
    uint idx;
    int* statusArray;
    void** objArray;
    int* freeListHead;
    void* obj;
    byte* indexPtr;
    uint* uintIndexPtr;

    // Process another manager if immediate
    if (immediate) {
        void* anotherMgr = *(void**)(thisPtr[0x71]); // +0x1C4
        (*(void(**)(void))(*(int*)anotherMgr + 0x10))();
    }

    // Process resource manager if present
    void* resMgr = *(void**)(thisPtr[0x70]); // +0x1C0
    if (resMgr != 0) {
        (*(void(**)(int))(*(int*)resMgr + 0x18))(0);
        (*(void(**)(int))(*(int*)resMgr + 0x28))(0);
        (*(void(**)(int))(*(int*)resMgr + 0x38))(0);
        if (immediate) {
            (*(void(**)(int))(*(int*)resMgr + 0x10))(0);
        }
    }

    // Process group0 (indices stored as bytes starting at +0x59, count at +0x58)
    if (*(char*)(thisPtr + 0x16) != 0) { // count at +0x58 (0x16*4=0x58)
        count = *(byte*)(thisPtr + 0x16);
        indexPtr = (byte*)((int)thisPtr + 0x59);
        do {
            index = *indexPtr;
            slotManager = thisPtr[0x6f]; // +0x1BC
            statusArray = *(int**)(slotManager + 0x18);
            if (statusArray[index] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))(); // error/assert
            }
            objArray = *(void***)(slotManager + 0x14);
            obj = objArray[index];
            (**(void(**)(void))(*(int*)obj + 0x44))(); // process function
            idx = (uint)index;
            slotManager = thisPtr[0x6f];
            statusArray = *(int**)(slotManager + 0x18);
            if (statusArray[idx] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))();
            }
            if (statusArray[idx] == -2) {
                freeListHead = *(int**)(slotManager + 0x1C);
                statusArray[idx] = *freeListHead;
                *freeListHead = idx;
            }
            indexPtr++;
        } while ((int)(indexPtr - (byte*)((int)thisPtr + 0x59)) < (int)count);
    }
    *(char*)(thisPtr + 0x16) = 0; // clear count

    // Process group1 (indices at +0x7A, count at +0x79)
    if (*(char*)((int)thisPtr + 0x79) != 0) {
        count = *(byte*)((int)thisPtr + 0x79);
        indexPtr = (byte*)((int)thisPtr + 0x7A);
        do {
            index = *indexPtr;
            slotManager = thisPtr[0x6f];
            statusArray = *(int**)(slotManager + 0x24);
            if (statusArray[index] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))();
            }
            objArray = *(void***)(slotManager + 0x20);
            obj = objArray[index];
            (**(void(**)(void))(*(int*)obj + 0x18))(); // process function
            idx = (uint)index;
            slotManager = thisPtr[0x6f];
            statusArray = *(int**)(slotManager + 0x24);
            if (statusArray[idx] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))();
            }
            if (statusArray[idx] == -2) {
                freeListHead = *(int**)(slotManager + 0x28);
                statusArray[idx] = *freeListHead;
                *freeListHead = idx;
            }
            indexPtr++;
        } while ((int)(indexPtr - (byte*)((int)thisPtr + 0x7A)) < (int)count);
    }
    *(char*)((int)thisPtr + 0x79) = 0;

    // Process group2 (indices stored as uint at +0x9C, count at +0x9A)
    if (*(char*)((int)thisPtr + 0x9A) != 0) {
        count = *(byte*)((int)thisPtr + 0x9A);
        uintIndexPtr = (uint*)((int)thisPtr + 0x9C); // starts at offset 0x9C
        do {
            idx = *uintIndexPtr;
            slotManager = thisPtr[0x6f];
            statusArray = *(int**)(slotManager + 0x30);
            if (statusArray[(byte)idx] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))();
            }
            objArray = *(void***)(slotManager + 0x2C);
            obj = objArray[(byte)idx];
            // Check context byte at param_1[1]+0x2c
            if (*(char*)(thisPtr[1] + 0x2C) != 0 || immediate) {
                (**(void(**)(void))(*(int*)obj + 0x18))();
            }
            (**(void(**)(void))(*(int*)obj + 0x28))();
            idx = (uint)(byte)idx;
            slotManager = thisPtr[0x6f];
            statusArray = *(int**)(slotManager + 0x30);
            if (statusArray[idx] != -2) {
                (**(void(**)(void))(*DAT_01205590 + 4))();
            }
            if (statusArray[idx] == -2) {
                freeListHead = *(int**)(slotManager + 0x34);
                statusArray[idx] = *freeListHead;
                *freeListHead = idx;
            }
            // Advance by 1 byte (decompiler artifact: actual array is byte-sized, but stored as uint? treat as stepping by 1)
            uintIndexPtr = (uint*)((int)uintIndexPtr + 1);
        } while ((int)((char*)uintIndexPtr - ((char*)thisPtr + 0x9C)) < (int)count);
    }
    *thisPtr = *thisPtr & 0xFFFFFFFE; // clear bit 0 (some flag)
    *(char*)((int)thisPtr + 0x9A) = 0;

    // Call next update function
    FUN_005974f0(immediate, param_3);
    return;
}
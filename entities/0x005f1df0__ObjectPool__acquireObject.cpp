// FUNC_NAME: ObjectPool::acquireObject
// This function retrieves an object from a free list pool. It checks a lock/state,
// initializes the pool if needed, pops a node from the singly linked list, then
// configures the object based on a type lookup.

undefined4* ObjectPool::acquireObject(undefined4 param_1)
{
    char lockCheck;
    undefined4* pObject;
    int* pGlobalType; // unaff_EDI - points to some global type info
    bool freeListEmpty;

    pObject = nullptr;
    lockCheck = FUN_005f1790(); // check some lock or critical section
    if (lockCheck == '\0') {
        freeListEmpty = g_freePoolCount == 0; // DAT_011a0f08
        if (freeListEmpty) {
            FUN_005f1820(); // initialize pool
            freeListEmpty = g_freePoolCount == 0;
        }
        if (!freeListEmpty) {
            pObject = nullptr;
            // Check if g_freePoolHead is non-null and list is not self-referencing?
            if ((g_freePoolHeadTag != 0) && ((undefined4**)g_freePoolHead != &g_freePoolHead)) {
                g_freePoolCount = g_freePoolCount - 1;
                pObject = g_freePoolHead;           // pop head
                g_freePoolHead = (undefined4*)*g_freePoolHead; // advance head
            }
            FUN_005f5730(); // likely some synchronization or misc
            char valid = FUN_005f2e40(param_1);
            if (valid != '\0') {
                // Initialize fields of the newly acquired object
                pObject[0x1d] = 0;   // offset 0x74 - unknown field
                pObject[0x21] = 0;   // offset 0x84
                pObject[0x22] = 0;   // offset 0x88
                pObject[0x23] = 0;   // offset 0x8c
                *(undefined1*)((int)pObject + 0x7b) = 0; // byte field
                pObject[0x1f] = 0;   // offset 0x7c
                pObject[0x20] = 0;   // offset 0x80
                // Look up a value based on bits from two structures
                // puVar2[2] -> a pointer to a structure with byte offset 8
                // *pGlobalType (unaff_EDI) at offset 7 (byte)
                uint index = (*(byte*)(pObject[2] + 8) & 1) + (*(byte*)(*pGlobalType + 7) & 1) * 2;
                // DAT_011a0f14 is assumed to be an array of 4 values (index * 4)
                pObject[0xd] = *(undefined4*)(&g_lookupTable + index * 4); // offset 0x34
            }
            // Call some function with fields from the object
            FUN_005dbc10(*(undefined1*)(pObject + 0x19), pObject[0x17], g_extraFlag); // DAT_011a0efa
        }
    }
    return pObject;
}
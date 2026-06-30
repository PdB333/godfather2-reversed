// FUNC_NAME: Manager::clearAll
// Function at 0x00572f30: cleanup and release all elements managed by this Manager (likely component manager).
// Clears a primary element (with two sub-resources) and then iterates over an array of keyed entries, removing each.
// Offsets: +0x20: count of entries in array, +0x24: pointer to array of 8-byte entries, +0x28: pointer to a manager structure.

void __thiscall Manager::clearAll(void)
{
    int* pMgrData = *(int**)(this + 0x28); // +0x28: pointer to manager control block
    if (pMgrData != 0)
    {
        int* pElement = (int*)*pMgrData; // first element (pointer stored at offset 0 of manager block)
        if (pElement != 0)
        {
            // Free sub-resources at offsets +0x08 and +0x0C of the element
            if (pElement[2] != 0) // +0x08
            {
                releaseSubResource(pElement[2]); // FUN_00573f70
            }
            if (pElement[3] != 0) // +0x0C
            {
                releaseSubResource(pElement[3]); // FUN_00573f70
            }
            // Call virtual function on handler object pointed to by pMgrData[3]
            // The handler's vtable pointer +4 gives the second method, taking (handler*, pElement, 0)
            {
                int* pHandler = (int*)pMgrData[3]; // +0x0C in manager block -> pointer to handler object
                typedef void (__thiscall *HandlerMethod)(void* self, int arg1, int arg2);
                HandlerMethod func = (HandlerMethod)(*(int*)(*(int*)pHandler + 4));
                func(pHandler, (int)pElement, 0);
            }
            pMgrData[1]--; // decrement count at +0x04 in manager block
        }
        *pMgrData = 0; // clear the primary element pointer
    }

    // Now clear the array of keyed entries (8 bytes each; first 4 bytes are key)
    int entryCount = *(int*)(this + 0x20); // +0x20: number of entries
    if (entryCount > 0)
    {
        int* pArrayBase = *(int**)(this + 0x24); // +0x24: pointer to array
        for (int i = 0; i < entryCount; i++)
        {
            int key = *(int*)(pArrayBase + i * 2); // 8-byte stride, first 4 bytes
            removeKeyEntry(pMgrData, &key, &i); // FUN_00573df0 - removes entry by key, may modify i to avoid skipping
        }
    }
}
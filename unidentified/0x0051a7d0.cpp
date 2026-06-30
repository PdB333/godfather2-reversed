// FUN_0051a7d0: EARSObjectManager::deleteAndReclaimAll

uint32_t g_listHead = DAT_01205514; // start of object list
uint32_t* g_poolStack = (uint32_t*)(DAT_01206880 + 0x14); // pool stack pointer

void FUN_0051a7d0()
{
    // First pass: mark all objects as pending deletion and clear their extra pointer
    if (g_listHead != nullptr) {
        EARSObject* pObj = g_listHead;
        do {
            beginDeleteBatch();       // FUN_0051b120
            prepareObjectForDeletion(pObj); // FUN_0051b0b0(pObj)
            pObj->flags |= 0x200000;  // mark as pending delete
            endDeleteBatch();         // FUN_0051d6b0

            if (pObj->somePointer != nullptr) {
                *pObj->somePointer = 0;
                pObj->somePointer = nullptr;
            }

            // Advance to next node
            EARSObject** ppNext = &pObj->next;
            pObj = *ppNext;
        } while (*ppNext != nullptr); // continue while current node has a next
    }

    // Second pass: move all marked objects from active list to pool (free list)
    EARSObject** ppCurrent = &g_listHead;
    EARSObject* pObj = g_listHead;
    while (pObj != nullptr) {
        pObj = *ppCurrent; // re-read current node (since ppCurrent may have been updated)
        if ((pObj->flags & 0x200000) == 0) {
            // Not marked, move to next node
            ppCurrent = &pObj->next;
        } else {
            // Marked: unlink from list
            *ppCurrent = pObj->next;

            // Call destructor or cleanup
            objectDestructor(pObj); // FUN_0051a5e0(this, pObj)

            // Insert into pool stack
            uint32_t* pStack = (uint32_t*)(DAT_01206880 + 0x14); // pool stack pointer
            *(*pStack) = (uint32_t)&someGlobal; // seemingly store a global address as sentinel?
            (*pStack)++; // increment stack pointer
            uint32_t aligned = (*pStack + 3) & ~3; // align to 4 bytes
            *pStack = aligned;
            *(*pStack) = (uint32_t)pObj; // store object pointer
            (*pStack)++;
        }
        pObj = *ppCurrent;
    }
}
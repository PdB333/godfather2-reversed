// FUNC_NAME: EntityManager::flushPendingDestructionList

void __thiscall EntityManager::flushPendingDestructionList(EntityManager* thisPtr)
{
    uint32_t i = 0;
    // +0xb8: count of pending destruction items
    if (thisPtr->m_pendingCount != 0) {
        do {
            // +0xb4: array of pointers to pending items
            void* item = thisPtr->m_pendingArray[i];
            lockGlobalMutex(0);
            beginProcessingList(thisPtr);
            if (isProcessingAllowed()) {
                processPendingItem(item);
            }
            i++;
        } while (i < thisPtr->m_pendingCount);
    }
    // Clear the pending list after processing
    thisPtr->m_pendingCount = 0;
    deallocateArray(thisPtr->m_pendingArray);
    // +0xb4: pointer to array
    thisPtr->m_pendingArray = nullptr;
    // +0xbc: capacity of array
    thisPtr->m_pendingCapacity = 0;
    resetOtherLists();
    // Check if all other lists are empty before deciding to release the global reference
    // +0x88, +0xa0, +0xac: counts of other lists
    if (thisPtr->m_list1Count == 0 && thisPtr->m_list2Count == 0 && 
        thisPtr->m_list3Count == 0 && thisPtr->m_pendingCount == 0) {
        releaseGlobalReference(&g_globalManager);
        return;
    }
    addRefGlobalReference(&g_globalManager);
}
// FUNC_NAME: AnimationManager::addOrUpdateAnimRequest
uint AnimationManager::addOrUpdateAnimRequest(const AnimRequestData& requestData) {
    // Access global memory manager singleton
    MemoryManager* pMemMgr = g_pMemoryManager;
    uint index = 0;

    // Search for existing action with matching subType and animSet
    if (m_actionCount != 0) {
        AnimAction** actions = reinterpret_cast<AnimAction**>(m_pActions);
        do {
            AnimAction* pAction = actions[index];
            if (pAction != nullptr &&
                pAction->m_subType == requestData.subType &&
                pAction->m_animSet == requestData.animSet) {
                // Update target and current values
                pAction->m_currentValue = requestData.targetValue;
                pAction->m_targetValue = requestData.targetValue;
                return (index & 0xFFFFFF00) | 1; // success, existing
            }
            ++index;
        } while (index < m_actionCount);
    }

    // If no free blocks in memory pool, try to allocate more
    if (pMemMgr->m_pFreeList == nullptr &&
        (pMemMgr->m_pAllocatedList == nullptr || (pMemMgr->m_flags & 1) == 0)) {
        pMemMgr->allocateNewBlock();
    }

    AnimAction* pNewAction = pMemMgr->m_pFreeList;
    if (pNewAction != nullptr) {
        // Update memory manager stats
        uint freeBlock = reinterpret_cast<uint>(pNewAction);
        pMemMgr->m_allocCount++;
        pMemMgr->m_freeCount--;
        pMemMgr->m_pFreeList = reinterpret_cast<AnimAction*>(pNewAction->m_nextFree);

        // Write sentinel values for debugging
        pNewAction->m_debugMarkers[0] = 0xBADBADBA;
        pNewAction->m_debugMarkers[1] = 0xBEEFBEEF;
        pNewAction->m_debugMarkers[2] = 0xEAC15A55;
        pNewAction->m_debugMarkers[3] = 0x91100911;

        // Initialize action (vtable, etc.)
        pNewAction->init();

        // Copy request data
        pNewAction->m_type = requestData.type;
        pNewAction->m_subType = requestData.subType;
        pNewAction->m_animSet = requestData.animSet;
        pNewAction->m_animNameHash = requestData.animNameHash;
        pNewAction->m_currentValue = requestData.targetValue;
        pNewAction->m_targetValue = requestData.targetValue;

        // Add to action list (resize if necessary)
        if (m_actionCount < MAX_ACTIONS) {
            if (m_actionCount == m_actionCapacity) {
                if (m_actionCapacity == 0)
                    resizeActionArray(1);
                else
                    resizeActionArray(m_actionCapacity * 2);
            }
            AnimAction** array = reinterpret_cast<AnimAction**>(m_pActions);
            array[m_actionCount] = pNewAction;
            uint newCount = m_actionCount + 1;
            m_actionCount = newCount;
            return (newCount & 0xFFFFFF00) | 1; // success, new
        }
    }

    // Failed to allocate or list full
    return 0;
}
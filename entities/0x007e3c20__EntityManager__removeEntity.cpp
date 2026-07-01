// FUNC_NAME: EntityManager::removeEntity
void __thiscall EntityManager::removeEntity(Entity* pEntity)
{
    HandleNode* pCurrentHandle = m_pHandleList; // +0xC0
    bool bHandleFound = false;

    // Temporarily link the entity into a list for safety (preserve on-stack list head)
    HandleNode* tempListHead = nullptr;
    if (pEntity && (pEntity->m_pNext != nullptr))
    {
        pEntity->m_ppPrev = &tempListHead;
        tempListHead = &pEntity->m_pNext;
    }

    // Search the handle list for an existing handle pointing to this entity
    if (pCurrentHandle)
    {
        do
        {
            Entity* pObjFromHandle = nullptr;
            if (pCurrentHandle->m_pFieldPtr)
            {
                pObjFromHandle = reinterpret_cast<Entity*>(
                    reinterpret_cast<char*>(pCurrentHandle->m_pFieldPtr) - 0x48);
            }
            if (pObjFromHandle == pEntity)
            {
                bHandleFound = true;
                break; // equivalent to goto LAB_007e3c94
            }
            pCurrentHandle = pCurrentHandle->m_pNext; // +0x0C
        } while (pCurrentHandle);
    }

    if (!bHandleFound)
    {
        // No existing handle – process removal immediately
        HandleNode* procListHead = nullptr;
        if (pEntity && (pEntity->m_pNext != nullptr))
        {
            pEntity->m_ppPrev = &procListHead;
            procListHead = &pEntity->m_pNext;
        }

        // Process the removal list (iterate and schedule removal)
        ProcessRemovalList(&procListHead);

        // Get the first entity from the processed list (original pEntity)
        Entity* pFirstEntity = nullptr;
        if (procListHead)
        {
            pFirstEntity = reinterpret_cast<Entity*>(
                reinterpret_cast<char*>(procListHead) - 0x48);
        }

        // Call the entity's removal virtual function (vtable+0x158)
        if (pFirstEntity)
        {
            typedef void (__thiscall *RemovalFunc)(void*);
            (*((RemovalFunc*)(*(int**)pFirstEntity + (0x158 / sizeof(void*)))))(pFirstEntity);
        }

        // Flag that pending removals need processing
        m_bPendingRemovalProcessingNeeded = 1; // +0x80

        // Unlink the entity from the temporary processing list
        if (procListHead)
        {
            UnlinkNode(&procListHead);
        }
    }
    else
    {
        // Mark the existing handle for lazy removal
        pCurrentHandle->m_bRemovalScheduled = 1; // +0x08
    }

    // Clean up the safety temporary list (restore original links)
    if (tempListHead)
    {
        UnlinkNode(&tempListHead);
    }
}
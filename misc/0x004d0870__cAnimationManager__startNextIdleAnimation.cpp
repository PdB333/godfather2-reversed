// FUNC_NAME: cAnimationManager::startNextIdleAnimation

void __fastcall cAnimationManager::startNextIdleAnimation(cAnimationManager* thisPtr)
{
    // Global reentry guard
    static bool s_bInExec = false;
    bool bFound;

    if (s_bInExec)
        return;

    s_bInExec = true;

    // Traverse linked list of animation/task nodes starting from head at this->m_pNodeListHead (offset +0x4c)
    cAnimationNode* pNode = *(cAnimationNode**)(thisPtr + 0x4c);
    while (pNode != nullptr)
    {
        // Check if node is busy (offset +0xB0) or has 'skip' flag (bit 1 at offset +0xA8)
        if ((pNode->m_bBusy != 0) || ((pNode->m_nFlags & 2) != 0))
        {
            pNode = pNode->m_pNext;
            if (pNode == nullptr)
            {
                s_bInExec = false;
                return;
            }
            continue;
        }

        // If node has 'hasCallback' flag (bit 2) and a global function pointer is set, invoke it
        if (((pNode->m_nFlags & 4) != 0) && (*(void**)(g_pAnimationEngine + 0x50) != nullptr))
        {
            // Call is (cAnimationData*)(pNode + 8), 1 (some boolean)
            bool (*pfnCheck)(void*, int) = *(bool (**)(void*, int))(g_pAnimationEngine + 0x50);
            if (pfnCheck(&pNode->m_Data, 1))
            {
                // Mark this manager as currently processing an animation (offset +100)
                *(uint8_t*)(thisPtr + 100) = 1;
                s_bInExec = false;
                return;
            }
        }

        // Accept this node: mark manager as idle, store current node, set node as busy, launch animation
        *(uint8_t*)(thisPtr + 100) = 0;                     // m_bAnimating = 0
        *(cAnimationNode**)(thisPtr + 0x48) = pNode;        // m_pCurrentNode = pNode
        pNode->m_bBusy = 1;                                 // mark node as busy
        // Start async operation: (node data, 0, completion callback, node ptr, 0)
        FUN_00ac41a0(&pNode->m_Data, 0, FUN_004d19a0, pNode, 0);
        break;
    }

    s_bInExec = false;
}
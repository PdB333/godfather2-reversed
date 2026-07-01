// FUNC_NAME: ActionQueueManager::processAllQueues

void __fastcall ActionQueueManager::processAllQueues(void)
{
    // Node structure: PendingActionNode
    // offset 0: int m_actionId
    // offset 4: int m_padding
    // offset 8: char m_bProcessed
    // offset 12: PendingActionNode* m_pNext

    // List heads at this+0x98 (m_pPendingCommands) and this+0xAC (m_pPendingEvents)
    // Other members:
    // +0x58: void* m_pTarget (some object pointer)
    // +0x80: char m_bProcessingFlag
    // +0x84: PendingActionNode* m_pCurrentAction (pointer, but used as index? Actually stored as int*, but treated as index minus 0x48)
    // Bitfield at (actionId - 0x48) + 0x8e6 probably from m_pTarget

    PendingActionNode* pNode;
    PendingActionNode* pNext;
    int iVar3;
    int iVar4;
    PendingActionNode* pRemove;

    // Process command queue (list at this+0x98)
    PendingActionNode** ppCmdQueue = (PendingActionNode**)((int)this + 0x98);
    pNode = *ppCmdQueue;

    while (true)
    {
        pNext = pNode;
        if (pNext == nullptr)
            break;

        if (pNext == nullptr)
            pNode = nullptr;
        else
            pNode = pNext->m_pNext; // offset 12

        if (pNext->m_bProcessed == 0) // byte at +8
        {
            iVar4 = pNext->m_actionId; // offset 0
            pRemove = pNext;

            if (iVar4 != 0)
            {
                if (iVar4 != 0x48) // special action ID
                {
                    if (isActionAllowed()) // FUN_007fd640
                        continue; // skip this node

                    iVar3 = (iVar4 != 0) ? (iVar4 - 0x48) : 0;
                    // Check if a flag at (iVar3 + 0x8e6) bit 0 is set
                    if ((*((byte*)((int)this->m_pTarget + iVar3 + 0x8e6)) & 1) != 0)
                        continue;
                }
                if ((iVar4 != 0) && (pNext->m_actionId != 0x48))
                {
                    executeCommand((int)this->m_pTarget); // FUN_007208e0
                }
            }
            this->m_bProcessingFlag = 1; // byte at +0x80
            removeNodeFromList(ppCmdQueue, &pRemove); // FUN_007e2840
        }
    }

    // Process event queue (list at this+0xAC)
    PendingActionNode** ppEventQueue = (PendingActionNode**)((int)this + 0xAC);
    pNode = *ppEventQueue;

    while (true)
    {
        pNext = pNode;
        if (pNext == nullptr)
            break;

        if (pNext == nullptr)
            pNode = nullptr;
        else
            pNode = pNext->m_pNext;

        // Skip nodes that are already processed (m_bProcessed != 0)
        if (pNext->m_bProcessed != 0)
            continue;

        pRemove = pNext;

        if (pNext->m_actionId == 0)
            goto removeEventNode;

        if ((pNext->m_actionId == 0x48) || (!isActionAllowed()))
        {
            if ((pNext->m_actionId != 0) && (pNext->m_actionId != 0x48))
            {
                cancelEvent((int)this->m_pTarget); // FUN_0071f540
            }
            if ((pNext->m_actionId != 0) && (pNext->m_actionId != 0x48))
            {
                // Compare current action pointer (adjusted by -0x48)
                iVar4 = (int)this->m_pCurrentAction; // +0x84, stored as int*
                if (iVar4 != 0)
                    iVar4 = iVar4 - 0x48;
                else
                    iVar4 = 0;
                if ((pNext->m_actionId - 0x48) == iVar4)
                {
                    if (this->m_pCurrentAction != nullptr)
                    {
                        clearCurrentAction(&this->m_pCurrentAction); // FUN_004daf90
                        this->m_pCurrentAction = nullptr;
                    }
                    onCurrentActionCleared(); // FUN_00939eb0
                }
            }
removeEventNode:
            removeNodeFromList(nullptr, &pRemove); // FUN_007e2840, local_4 is unused
        }
    }

    // Clear processed flags for all nodes in both queues
    for (pNode = *ppCmdQueue; pNode != nullptr; pNode = pNode->m_pNext)
    {
        pNode->m_bProcessed = 0;
    }
    for (pNode = *ppEventQueue; pNode != nullptr; pNode = pNode->m_pNext)
    {
        pNode->m_bProcessed = 0;
    }
}
// FUNC_NAME: EntitySlotList::linkObject

void __thiscall EntitySlotList::linkObject(EntitySlotList* thisObj, void* pObject)
{
    int nodeIndex = getNodeIndex(pObject);
    if (nodeIndex < 0)
    {
        // Remove the current slot occupant if any
        if (thisObj->m_pSlot != NULL)
        {
            releaseSlot(thisObj->m_pSlot);  // FUN_004daf90
            thisObj->m_pSlot = NULL;
        }
    }
    else
    {
        // pObject is a base pointer; the linked list node is at offset +0x48
        EntityListNode* pNode = (pObject != NULL) ? (EntityListNode*)((uint8_t*)pObject + 0x48) : NULL;
        
        // Double-linked list manipulation: head is at thisObj->m_pSlot (+0xa4)
        if (thisObj->m_pSlot != pNode)
        {
            if (thisObj->m_pSlot != NULL)
            {
                releaseSlot(thisObj->m_pSlot);
            }
            thisObj->m_pSlot = pNode;
            if (pNode != NULL)
            {
                // Save the node's original "next" pointer into thisObj->m_nextNode
                thisObj->m_nextNode = *(EntityListNode**)((uint8_t*)pNode + 4);  // +0xa8
                // Rewire the node's "next" to point back to the slot pointer (circular list)
                *(EntityListNode**)((uint8_t*)pNode + 4) = &thisObj->m_pSlot;
            }
        }

        int globalState = *(int*)(DAT_01130020 + 0x6c); // g_gameManager->m_state
        if (globalState != 2)
        {
            thisObj->m_slotIndex = nodeIndex;   // +0x74
            thisObj->m_slotFlags = 1;           // +0x58 -> state flag
            return;
        }
        if (thisObj->m_slotFlags != 1)
        {
            thisObj->m_slotIndex = nodeIndex;
            notifyStateChange(1, 0);            // FUN_00956a50
            return;
        }
        if (thisObj->m_slotIndex != nodeIndex)
        {
            thisObj->m_slotIndex = nodeIndex;
            refreshSlot();                      // FUN_009218e0
            resetGlobalData(&DAT_011301c0, 0);  // FUN_00402050
            finalizeSlotUpdate();               // FUN_00921400
            return;
        }
    }
}
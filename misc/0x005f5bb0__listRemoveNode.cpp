// FUNC_NAME: listRemoveNode
// Function address: 0x005f5bb0
// Purpose: Removes a node from an intrusive doubly linked list (prev at +0x0, next at +0x4)
struct ListNode
{
    ListNode* m_pPrev; // +0x0
    ListNode* m_pNext; // +0x4
};

void __fastcall listRemoveNode(ListNode* pNode)
{
    ListNode* pPrev = pNode->m_pPrev; // previous node in list

    if (pPrev != nullptr)
    {
        ListNode* pNextOfPrev = pPrev->m_pNext; // should be pNode normally

        if (pNextOfPrev == pNode)
        {
            // Fast path: the previous node already points to this node
            pPrev->m_pNext = pNode->m_pNext;
            return;
        }
        else
        {
            // Fallback: linear scan from the previous node to find the node that points to pNode
            ListNode* pCur = pPrev->m_pNext;
            ListNode* pScan = pCur->m_pNext;
            while (pScan != pNode)
            {
                pCur = pCur->m_pNext;
                pScan = pCur->m_pNext;
            }
            pCur->m_pNext = pNode->m_pNext;
        }
    }

    // Note: The next node's prev is not updated here, likely handled by the caller
    // or this function is only called when the next node's prev fix is unnecessary.
}
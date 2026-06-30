// FUNC_NAME: ListNode::relinkToFront

void __thiscall ListNode::relinkToFront(ListNode* pNewHead)
{
    // +0: m_pNext (pointer to next node in list)
    // +4: m_pPrev (pointer to previous node in list)
    // +8: m_pOwnerList (pointer to the list header this node belongs to)

    // Remove from current list if attached
    if (m_pOwnerList != 0) {
        if (m_pPrev == 0) {
            // This node is the first in its list; update list header's first pointer
            m_pOwnerList->m_pFirst = m_pNext;
        } else {
            m_pPrev->m_pNext = m_pNext;
        }
        if (m_pNext != 0) {
            m_pNext->m_pPrev = m_pPrev;
        }
    }

    // Attach to the front of the new list (pNewHead is a list header)
    m_pOwnerList = pNewHead;
    if (pNewHead != 0) {
        ListNode* pOldFirst = pNewHead->m_pFirst; // previously first element
        m_pNext = pOldFirst;
        if (pOldFirst != 0) {
            pOldFirst->m_pPrev = this;
        }
        m_pPrev = 0; // This node becomes the new first element
        pNewHead->m_pFirst = this; // Update header's first pointer
    }
}
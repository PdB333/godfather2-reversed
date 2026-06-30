// FUNC_NAME: ListNode::moveNextBeforeCurrent

struct ListNode {
    ListNode* m_pNext;      // +0x00
    ListNode* m_pPrev;      // +0x04
    ListNode* m_pExtra;     // +0x08 (used as forward pointer in list)
    char m_bFlags;          // +0x15 (likely flag for sentinel or special node)
};

// ListManager contains a head pointer at offset 0x1c -> some substructure with head at +4
// For this function, param_2 is a pointer to a ListManager-like object.
// The function removes the node immediately after 'this' (pAnchor->m_pNext) and
// re-inserts it immediately before 'this' (becomes new predecessor).

void __thiscall ListNode::moveNextBeforeCurrent(ListNode* pAnchor, void* pListManager)
{
    // pAnchor is 'this', the anchor node
    ListNode* pNodeToMove = pAnchor->m_pNext;   // iVar1 = *this (the node to relocate)

    // Update pAnchor's forward pointer to skip pNodeToMove (point to its m_pExtra)
    pAnchor->m_pNext = pNodeToMove->m_pExtra;

    // If the next node after pNodeToMove is not a sentinel, update its backward pointer
    ListNode* pNextAfterMoved = pNodeToMove->m_pExtra; // node that follows pNodeToMove in the list
    if (pNextAfterMoved != nullptr && pNextAfterMoved->m_bFlags == '\0') {
        pNextAfterMoved->m_pPrev = pAnchor;
    }

    // Update pNodeToMove's backward pointer to pAnchor's previous
    pNodeToMove->m_pPrev = pAnchor->m_pPrev;

    // Now we need to insert pNodeToMove just before pAnchor.
    // Check if pAnchor is the head of the list (i.e., pAnchor == pListManager->head->headPtr)
    // pListManager+0x1c is a pointer to a list head structure; +4 is the head node pointer.
    ListNode** pHeadPtr = *((ListNode***)((char*)pListManager + 0x1c)) + 1; // simplified, actual offset +4 inside
    // But we'll treat as: the head pointer is stored as ((ListNode**)(*(int*)(pListManager+0x1c)) + 1)
    ListNode* pHeadNode = *(ListNode**)(*(int*)((char*)pListManager + 0x1c) + 4); 
    
    if (pAnchor == pHeadNode) {
        // pAnchor was the head; now pNodeToMove becomes new head
        *(ListNode**)(*(int*)((char*)pListManager + 0x1c) + 4) = pNodeToMove;
        pNodeToMove->m_pExtra = pAnchor;
        pAnchor->m_pPrev = pNodeToMove;
        return;
    }

    // pAnchor is not head; handle general case
    ListNode* pAnchorPrev = pAnchor->m_pPrev; // piVar2
    if (pAnchor == pAnchorPrev->m_pExtra) {
        // pAnchor is the tail? (prev node's extra points to pAnchor)
        pAnchorPrev->m_pExtra = pNodeToMove;
        pNodeToMove->m_pExtra = pAnchor;
        pAnchor->m_pPrev = pNodeToMove;
        return;
    }

    // Standard insertion: update pAnchorPrev's next to point to pNodeToMove
    pAnchorPrev->m_pNext = pNodeToMove;
    pNodeToMove->m_pExtra = pAnchor;
    pAnchor->m_pPrev = pNodeToMove;
}
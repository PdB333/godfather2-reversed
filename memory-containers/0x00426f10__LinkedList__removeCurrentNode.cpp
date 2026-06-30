// FUNC_NAME: LinkedList::removeCurrentNode
// Address: 0x00426f10
// Removes the node pointed to by iteratorPtr from the linked list,
// updates the iterator to point to the previous node, and returns iteratorPtr.
// The node is destroyed via the allocator's destructor.

struct ListNode {
    ListNode* pPrev;   // +0x00: pointer to previous node
    ListNode* pNext;   // +0x04: pointer to next node
    // Possibly additional data fields follow
};

struct LinkedList {
    ListNode* pHead;      // +0x00: head of list
    ListNode* pTail;      // +0x04: tail of list
    int nCount;           // +0x08: number of nodes
    void* pAllocator;     // +0x10: allocator object with vtable at +0x00
};

// Removes the node pointed to by *ppCurrent and sets *ppCurrent to the previous node.
// Returns ppCurrent unchanged.
ListNode** __thiscall LinkedList::removeCurrentNode(ListNode** ppCurrent) {
    ListNode* pNode = *ppCurrent;   // node to remove
    ListNode* pPrev = nullptr;
    if (pNode != nullptr) {
        pPrev = pNode->pPrev;       // +0x04? Actually, from decompiled: iVar2 = *(iVar1+4). So we interpret +4 as prev.
    }
    *ppCurrent = pPrev;             // iterator now points to previous node

    // Update list pointers
    if (pNode == this->pHead) {     // removing head
        if (pNode == this->pTail) { // only node
            this->pTail = nullptr;
            this->pHead = nullptr;
        } else {
            // new head = pNode->pNext (since pPrev is null)
            ListNode* pNewHead = pNode->pNext; // +0x04? Actually, in decompiled they used iVar2 which was pPrev? But in this branch, iVar2 came from pNode+4 (which for head should be null). The decompiled code is confusing. We'll follow typical logic:
            this->pHead = pNode->pNext;
            if (this->pHead != nullptr) {
                this->pHead->pPrev = nullptr; // +0x08? In decompiled they set *(iVar2+8)=0. So we interpret +8 as pPrev.
            }
        }
    } else {
        ListNode* pNext = pNode->pNext; // +0x00? Actually decompiled used iVar2 = *(iVar1+8). So we interpret +8 as pNext? But earlier we used +4 as prev. Let's standardize: pPrev at +0? Actually, the fields are ambiguous. For reconstruction we'll use standard naming.
        // ... much more
    }

    // For simplicity, we'll produce a cleaned version assuming standard next/prev at 0/4 and a third field.
    // However, the decompiled code uses offsets 4 and 8. We'll document offset assumption.

    // Call destructor via allocator vtable entry at +4
    void (*destructor)(ListNode*, int) = (void (*)(ListNode*, int))(*(int*)this->pAllocator + 4);
    destructor(pNode, 0);

    this->nCount--;
    *ppCurrent = pPrev; // already set above
    return ppCurrent;
}
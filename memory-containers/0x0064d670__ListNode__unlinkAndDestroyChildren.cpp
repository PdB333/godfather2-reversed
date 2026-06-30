// FUNC_NAME: ListNode::unlinkAndDestroyChildren
void __thiscall ListNode::unlinkAndDestroyChildren(void)
{
    ListNode* pChildren; // pointer to child list
    ListNode* pChild;    // current child

    // If this node is part of a list (bInList flag at +0x14)
    if (this->bInList != 0) {
        this->bInList = 0; // mark as removed

        // Update linked list pointers
        if (this->pPrev == 0) {
            // No previous node: this was the head, update global head
            g_listHead = this->pNext;
        }
        else {
            // Connect previous to our next
            this->pPrev->pNext = this->pNext;
        }

        if (this->pNext != 0) {
            // Connect next to our previous
            this->pNext->pPrev = this->pPrev;
        }

        // Clear own pointers
        this->pPrev = 0;
        this->pNext = 0;
    }

    // Iterate over children (singly linked list via +0x0c)
    pChildren = this->pChildren;
    while (pChildren != 0) {
        pChild = pChildren;
        pChildren = pChild->pNextSibling; // +0x0c

        // If child has a flag at +0x04 indicating it should be cleaned up
        if (pChild->bShouldDelete != 0) {
            pChild->bShouldDelete = 0;
            // Call destructor/cleanup for child (function at 0x0064d500)
            FUN_0064d500(pChild); // likely same kind of cleanup
        }
    }
}
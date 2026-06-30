// FUNC_NAME: ListNode::swapWithNext
// Address: 0x00622330
// Reconstructed from Ghidra decompile
// This method moves the node immediately after 'this' to the position immediately before 'this'.
// Node layout: +0 next, +4 prev, +0x25 flag (if zero, reattach prev during operation)
// ListController layout: +0x1c m_pSentinel (points to a dummy sentinel node with +0 next, +4 prev)

void __thiscall ListNode::swapWithNext(ListNode* this, ListController* listController)
{
    ListNode* nextNode = this->next;          // piVar1: node to move
    this->next = nextNode->next;              // skip nextNode in forward chain

    // If nextNode's flag is zero, reattach its prev to this (it already points to this normally)
    if (*(char*)((int)nextNode + 0x25) == '\0') {
        nextNode->prev = this;
    }
    nextNode->prev = this->prev;              // attach nextNode before this

    // Handle special case: this is the last node of the list (this == sentinel->prev)
    if (this == listController->m_pSentinel->prev) {
        listController->m_pSentinel->prev = nextNode;   // update sentinel's prev
        nextNode->next = this;                          // nextNode becomes new last, this after it
        this->prev = nextNode;
        return;
    }

    ListNode* prevNode = this->prev;          // piVar2
    // Handle special case: this is the first node of the list (this == sentinel->next)
    if (this == prevNode->next) {             // equivalent to this == listController->m_pSentinel->next
        prevNode->next = nextNode;
        nextNode->next = this;
        this->prev = nextNode;
        return;
    }

    // Generic case: adjust the node before this to point to nextNode
    prevNode->next = nextNode;
    nextNode->next = this;
    this->prev = nextNode;
}
// FUNC_NAME: ListNode::remove

ListNode* __thiscall ListNode::remove(bool deleteNode) {
    // +0x00: pointer to the list head (or container) that owns this node
    // +0x04: pointer to the next node in the list
    ListNode* headPtr = this->list;     // offset 0
    if (headPtr != nullptr) {
        ListNode* nextOfHead = headPtr->next; // offset 4 of head
        if (nextOfHead == this) {
            // This node is the first node after the head; bypass directly.
            headPtr->next = this->next;
        } else {
            // Walk forward from the head's next to find the node that points to this.
            ListNode* prev = nextOfHead;
            ListNode* curr = prev->next;
            while (curr != this) {
                prev = curr;
                curr = prev->next;
            }
            // Unlink this node by updating the previous node's next pointer.
            prev->next = this->next;
        }
    }
    // If the delete flag is set, free the node's memory (likely operator delete / destructor)
    if ((deleteNode & 1) != 0) {
        FUN_009c8eb0(this);  // freeNode / destructor
    }
    return this;
}
// FUNC_NAME: ListNode::insertAfter
void __thiscall ListNode::insertAfter(ListNode* this, ListNode* prevNode)
{
    // First field (offset 0) stores a pointer to the previous node (or the node after which we insert)
    this->prevNode = prevNode;                                    // +0x00
    // Second field (offset 4) is the next pointer, initially null
    this->nextNode = 0;                                           // +0x04

    if (prevNode != 0) {
        // Insert this node between prevNode and its current next
        this->nextNode = prevNode->nextNode;                      // +0x04
        prevNode->nextNode = this;                                // +0x04 (prevNode->next)
    }
    // Note: If this is a doubly linked list, the next node's prev pointer is not updated here,
    // suggesting either a singly linked list or that the update is done elsewhere.
}
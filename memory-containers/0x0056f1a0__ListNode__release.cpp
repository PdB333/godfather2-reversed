// FUNC_NAME: ListNode::release
void ListNode::release() {
    // Decrement reference count at +0x09
    this->refCount--;

    // If the node is not in use (active flag = 0) and reference count reaches zero, remove from list
    if (this->active == 0 && this->refCount == 0) {
        ListNode* prevNode = this->prev;   // +0x00
        ListNode* nextNode = this->next;   // +0x04

        // Update previous node's next pointer
        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }

        NodeManager* mgr = g_nodeManager; // DAT_01205564
        if (nextNode != nullptr) {
            // Update next node's prev pointer
            nextNode->prev = prevNode;
            return;
        }

        // Replacing tail (or sentinel) when removing last node
        mgr->tail = mgr->head;           // +0x08 = +0x04
        mgr->head = prevNode;            // +0x04 = prev

        if (prevNode == nullptr) {
            mgr->tail = mgr->sentinel;   // +0x08 = +0x0c
        }
    }
}
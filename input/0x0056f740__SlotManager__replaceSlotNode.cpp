// FUNC_NAME: SlotManager::replaceSlotNode
void __thiscall SlotManager::replaceSlotNode(SlotManager* this, ListNode* newNode) {
    // Increment reference count of new node
    if (newNode != 0) {
        ++(newNode->refCount); // +0x09
    }

    // Get current node stored at this+0x40
    ListNode* oldNode = *(ListNode**)((int)this + 0x40);
    if (oldNode != 0) {
        // Decrement reference count of old node
        --(oldNode->refCount); // +0x09

        // If the old node is not locked (flag == 0) and references are gone, unlink it from the global list
        if ((oldNode->flag == 0) && (oldNode->refCount == 0)) { // flag at +0x08
            ListNode* nextNode = oldNode->next;       // +0x00
            ListNode* prevNode = oldNode->prev;       // +0x04

            // Update next node's prev pointer
            if (nextNode != 0) {
                nextNode->prev = prevNode;
            }

            // Global list head structure (DAT_0120558c)
            ListHead* head = (ListHead*)0x0120558c; // replace with actual global variable

            if (prevNode != 0) {
                // Update previous node's next pointer
                prevNode->next = nextNode;
                // Store new node into this slot
                *(ListNode**)((int)this + 0x40) = newNode;
                return;
            } else {
                // Removing the head of the global list
                head->tail = head->first;     // +0x08 = +0x04
                head->first = nextNode;       // +0x04 = nextNode
                if (nextNode == 0) {
                    head->tail = head->last;  // +0x08 = +0x0c
                }
            }
        }
    }

    // Store new node into this slot
    *(ListNode**)((int)this + 0x40) = newNode;
}
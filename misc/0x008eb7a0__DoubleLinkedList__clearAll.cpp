// FUNC_NAME: DoubleLinkedList::clearAll
// Function at 0x008eb7a0: Iteratively removes and destroys all nodes in a doubly-linked list.
// The list structure (presumably DoubleLinkedList) has head at +0x00, tail at +0x04.
// Each node has next at +0x00, prev at +0x04, and a sub-object (or pointer) at +0x08.
// The sub-object at +0x08 is cleaned up via external function destroySubObject(addr), 
// then the node itself is freed via external function freeNode(addr).

void __thiscall DoubleLinkedList::clearAll(void* this) {
    int* node;
    int* currNode;

    // Start with the head node
    node = *(int**)this;          // this+0x00 = head pointer
    currNode = nullptr;

    if (node != nullptr) {
        int nextNode = *node;     // node->next at +0x00
        *(int**)this = (int*)nextNode;   // head = node->next
        currNode = node;
        if (nextNode == 0) {
            // List became empty, update tail
            *(int*)((int)this + 4) = 0;   // this+0x04 = tail = 0
        } else {
            // New head's prev becomes null
            *(int*)(nextNode + 4) = 0;     // new head->prev = 0
            *node = 0;                     // detach old node (optional, not strictly needed)
        }
    }

    // Process all nodes removed from the head
    while (currNode != nullptr) {
        if (currNode != nullptr) {
            // Clean up sub-object at node+0x08
            if (*(int*)(currNode + 8) != 0) {
                destroySubObject(currNode + 8);  // call 0x004daf90
            }
            // Free the node itself
            freeNode(currNode);                 // call 0x009c8eb0
        }

        // Fetch next node to process (head may have changed if nodes were added during cleanup)
        node = *(int**)this;
        currNode = nullptr;
        if (node != nullptr) {
            int nextNode = *node;
            *(int**)this = (int*)nextNode;
            currNode = node;
            if (nextNode == 0) {
                *(int*)((int)this + 4) = 0;
            } else {
                *(int*)(nextNode + 4) = 0;
                *node = 0;
            }
        }
    }
}
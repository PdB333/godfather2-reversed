// FUNC_NAME: LinkedList::erase
void __thiscall LinkedList::erase(int *this, int unusedParam, int **iterator) {
    // Node layout: +0x00: unknown (likely data or padding), +0x04: next, +0x08: prev
    struct ListNode {
        int field0;
        ListNode *next; // +0x04
        ListNode *prev; // +0x08
    };

    ListNode *node = (ListNode *)*iterator;           // current node to remove
    ListNode *nextNode = (node != nullptr) ? node->next : nullptr; // node's next (offset +0x04)

    // Advance iterator to next node
    *iterator = (int *)nextNode;

    // Remove node from the doubly linked list (head/tail stored in this)
    ListNode *head = (ListNode *)this[0]; // +0x00: head
    ListNode *tail = (ListNode *)this[1]; // +0x04: tail

    if (node == head) {
        if (node == tail) {
            // Only node in list
            this[0] = 0; // head = nullptr
            this[1] = 0; // tail = nullptr
        } else {
            // Remove head, new head is nextNode
            this[0] = (int)nextNode; // head = nextNode
            if (nextNode != nullptr) {
                nextNode->prev = nullptr; // clear new head's prev (offset +0x08)
            }
        }
    } else {
        ListNode *prevNode = node->prev; // offset +0x08
        if (node == tail) {
            // Remove tail, new tail is prevNode
            this[1] = (int)prevNode; // tail = prevNode
            if (prevNode != nullptr) {
                prevNode->next = nullptr; // clear new tail's next (offset +0x04)
            }
        } else {
            // Remove middle node: link prevNode->next = nextNode, nextNode->prev = prevNode
            prevNode->next = nextNode;   // offset +0x04 of prevNode
            nextNode->prev = prevNode;   // offset +0x08 of nextNode
        }
    }

    // Deallocate the node using a virtual function from allocator stored in this[4]
    // allocator is a pointer to a class with a vtable; second function (offset +0x04) is called
    AllocatorBase *allocator = (AllocatorBase *)this[4]; // +0x10
    allocator->deallocate(node, 0); // virtual function: (**(code **)(*(int *)allocator + 4))(node, 0)

    // Decrement the node count stored in this[2]
    this[2]--; // +0x08: count
}
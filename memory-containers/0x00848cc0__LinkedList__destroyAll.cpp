// FUNC_NAME: LinkedList::destroyAll
int __fastcall LinkedList::destroyAll(void) {
    // param_1 (ECX) = this, pointer to head node
    // Node structure: offset 0 = vtable pointer, offset 4 = prev, offset 8 = next
    // This function unlinks each node from the list and calls its virtual destructor (via vtable[0](1))

    LinkedListNode* node = reinterpret_cast<LinkedListNode*>(this);
    if (node == nullptr) {
        return 0;
    }

    do {
        // Unlink current node from the list
        LinkedListNode* prev = node->prev; // offset 4
        LinkedListNode* next = node->next; // offset 8

        if (prev != nullptr) {
            prev->next = next; // Set previous node's next to current's next
        }
        if (next != nullptr) {
            next->prev = prev; // Set next node's prev to current's prev
        }

        VirtualDestructorFunc destructor = node->vtable[0]; // First vtable entry is delete/destructor
        LinkedListNode* nextNode = node->next; // Save next pointer before destruction

        destructor(1); // Call destructor (argument 1 might indicate deallocation)

        node = nextNode;
    } while (node != nullptr);

    return 0;
}
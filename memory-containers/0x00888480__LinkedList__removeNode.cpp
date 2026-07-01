// FUNC_NAME: LinkedList::removeNode

void __thiscall LinkedList::removeNode(Node*& iterator, int unusedParam) {
    // param_1 = this
    // param_2 = unused (maybe a flag or legacy parameter)
    // param_3 = pointer to iterator (reference to a Node*)

    Node* nodeToRemove = iterator;  // *param_3
    Node* nextNode;
    if (nodeToRemove == 0) {
        nextNode = 0;
    } else {
        nextNode = nodeToRemove->next;  // nodeToRemove + 0x4
    }
    iterator = nextNode;  // Advance iterator to next

    // Update head and tail pointers of the list
    if (nodeToRemove == head) {
        if (nodeToRemove == tail) {
            // Removing the only node
            tail = 0;
            head = 0;
        } else {
            // Removing head, new head is next
            head = nextNode;
            if (nextNode != 0) {
                nextNode->prev = 0;  // offset 0x8
            }
        }
    } else {
        Node* prevNode = nodeToRemove->prev;  // offset 0x8
        if (nodeToRemove == tail) {
            // Removing tail, new tail is prev
            tail = prevNode;
            prevNode->next = 0;  // offset 0x4
        } else {
            // Removing a middle node
            prevNode->next = nodeToRemove->next;
            nodeToRemove->next->prev = prevNode;
        }
    }

    // Call destructor through allocator vtable (allocator + 0x4)
    // allocator is stored at this + 0x10 (param_1[4])
    void (*destroyFunc)(Node*, int) = (void (*)(Node*, int))(*(int*)(*(int*)(this + 0x10) + 0x4));
    destroyFunc(nodeToRemove, 0);  // Second parameter 0 likely means "deallocate"

    // Decrement count
    this->count--;  // param_1[2]

    // The iterator parameter (param_3) was updated earlier, and the caller likely uses the new value via a saved register (unaff_EBX in original asm)
}
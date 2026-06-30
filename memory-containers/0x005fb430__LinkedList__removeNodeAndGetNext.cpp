// FUNC_NAME: LinkedList::removeNodeAndGetNext
void LinkedList::removeNodeAndGetNext(int *output, LinkedList *container, Node *node) {
    // offset +0x18: sentinel node
    // offset +0x1c: count (total nodes)
    // vtable at offset 0, second entry is a deallocation function (free node)

    if (container == nullptr) {
        debugBreak(); // FUN_00b97aea
    }

    if (node == container->sentinel) {
        debugBreak();
    }

    Node *nextNode = node->next; // offset 0

    if (node != this->sentinel) { // this->sentinel at +0x18
        // Remove node from the list
        node->prev->next = nextNode;  // node->prev at offset 4
        nextNode->prev = node->prev;

        // Call deallocator on node (size 0xc = 12 bytes)
        this->vtable->deallocate(node, 0xc); // vtable+4

        this->count--; // this->count at +0x1c
    }

    // Output the container and next node (for iterator advancement)
    output[0] = (int)container;
    output[1] = (int)nextNode;
}
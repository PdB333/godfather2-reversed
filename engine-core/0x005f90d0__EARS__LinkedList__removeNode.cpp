// FUNC_NAME: EARS::LinkedList::removeNode
void EARS::LinkedList::removeNode(Node* node, Iterator* outIterator) {
    // Assertions (debug)
    if (this == nullptr) {
        EA_ASSERT(0); // FUN_00b97aea in original
    }
    if (node == this->head) {
        EA_ASSERT(0); // cannot remove sentinel head
    }

    Node* nextNode = node->next; // save next before unlink

    // Unlink node from doubly linked list
    // node layout: [next (0x00), prev (0x04)]
    node->prev->next = nextNode;
    nextNode->prev = node->prev;

    // Deallocate node memory (size = 12 bytes = 0xC)
    this->vtable->vfuncDeallocate(node, 0xC); // virtual function at vtable+4
    this->count--; // +0x1C

    // Fill output iterator: [list pointer, next node pointer]
    outIterator->list = this;      // +0x00
    outIterator->next = nextNode;  // +0x04
}
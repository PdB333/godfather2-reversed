// FUNC_NAME: CachedLinkedList::getLastNode
// Address: 0x005d0ca0
// Role: Retrieves and caches the last node in a linked list. The list structure:
//   +0x00: Node* head       (first node)
//   +0x04: Node* current    (currently tracked node, may be cached)
// Each node has a next pointer at +0x20.
__thiscall Node* CachedLinkedList::getLastNode() {
    // If current is null, initialize it from head
    if (this->current == 0) {
        this->current = this->head;
    }

    // Traverse to the end of the list via next pointers (+0x20)
    if (this->current != 0) {
        Node* pNext = this->current->next;   // offset +0x20
        while (pNext != 0) {
            this->current = pNext;
            pNext = this->current->next;
        }
    }

    // Return the cached last node
    return this->current;
}
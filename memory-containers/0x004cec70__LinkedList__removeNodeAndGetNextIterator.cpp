// FUNC_NAME: LinkedList::removeNodeAndGetNextIterator
void LinkedList::removeNodeAndGetNextIterator(SmartPointer* outIterator, LinkedList* otherList, Node* node)
{
    // param_2 == 0 -> invalid list
    if (otherList == nullptr) {
        assert(0);
    }
    // param_3 must not be the sentinel node of otherList
    if (node == otherList->sentinel) {
        assert(0);
    }

    Node* nextNode = node->next;

    // Only remove if node is not the sentinel of this list (the list that owns the node)
    if (node != this->sentinel) {
        // Remove node from doubly linked list
        node->prev->next = nextNode;
        nextNode->prev = node->prev;

        // Call deallocator via vtable (function at index 1, size 12 bytes)
        (this->vtable->deallocate)(node, 12);

        // Decrement node count
        this->count--;
    }

    // Write output iterator: store the otherList pointer and the next node pointer
    outIterator[0] = (int)otherList;
    outIterator[1] = (int)nextNode;
}
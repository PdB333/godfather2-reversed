// FUNC_NAME: LinkedList::~LinkedList
void __thiscall LinkedList::~LinkedList(LinkedList *this, byte flags)
{
    LinkedListNode *currentNode; // node being processed
    LinkedListNode *nextNode;    // next node in list

    // Set vtable pointer (likely to ensure correct vtable during destruction)
    this->vtable = (void *)&PTR_FUN_00e32808; // +0x00: vtable pointer

    // Iterate through linked list starting at head (+0x04)
    currentNode = this->head; // +0x04: head pointer
    while (currentNode != nullptr) {
        // Save next node before clearing
        nextNode = currentNode->next; // +0x04 in node: next pointer
        // Clear both pointers in the current node
        currentNode->next = nullptr;  // +0x04
        currentNode->prev = nullptr;  // +0x00
        currentNode = nextNode;
    }

    // If bit 0 of flags is set, free the object's memory
    if ((flags & 1) != 0) {
        operator delete(this); // or custom deallocation function at 0x009c8eb0
    }
}
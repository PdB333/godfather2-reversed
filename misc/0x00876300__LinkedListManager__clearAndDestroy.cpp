// FUNC_NAME: LinkedListManager::clearAndDestroy
// Function address: 0x00876300
// Role: Destructor/cleanup function that clears a linked list of nodes and optionally frees the object itself.
// The class has a vtable pointer at offset 0, a linked list head at +4, and a pointer to a managed resource at +8.

LinkedListManager* __thiscall LinkedListManager::clearAndDestroy(byte deleteSelf) {
    LinkedListManager* thisPtr = this;
    LinkedListNode* currentNode;
    LinkedListNode* nextNode;

    // Free the managed resource if it exists (offset +8)
    if (this->managedResource != nullptr) {
        FUN_004daf90(&this->managedResource); // assumed free function
    }

    // Set vtable pointer to base class vtable to prevent virtual calls after cleanup
    this->vtable = &PTR_FUN_00e32808;

    // Walk the linked list starting from head at offset +4
    currentNode = this->headNode;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        // Clear out node's links and data (assumed pattern: first two fields)
        currentNode->next = nullptr;
        currentNode->prevOrData = nullptr;
        currentNode = nextNode;
    }

    // Optionally delete the object itself if the flag is set
    if ((deleteSelf & 1) != 0) {
        FUN_009c8eb0(this); // operator delete or deallocation
    }

    return this;
}
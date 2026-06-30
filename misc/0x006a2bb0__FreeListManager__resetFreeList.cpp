// FUNC_NAME: FreeListManager::resetFreeList
void* FreeListManager::resetFreeList(void* this_) {
    // Initialize first field of the object to 0 (likely a reference count or lock)
    *(uint32_t*)this_ = 0;

    // Iterate over the global free list (singly linked, sentinel at &freeListHead)
    void** currentNode = (void**)freeListHead;
    void** sentinel = (void**)&freeListHead;
    while (currentNode != sentinel) {
        void** nextNode = (void**)*currentNode; // next pointer stored at offset 0
        FUN_009c8f10(currentNode);              // destroy the node
        currentNode = nextNode;
    }

    // Reset the free list to empty (head and tail point to sentinel)
    freeListHead = (void*)sentinel;
    freeListTail = (void*)sentinel;
    freeListCount = 6; // Initial capacity or constant

    return this_;
}
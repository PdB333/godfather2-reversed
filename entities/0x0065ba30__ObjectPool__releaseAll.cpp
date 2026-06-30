// FUNC_NAME: ObjectPool::releaseAll
void __thiscall ObjectPool::releaseAll() {
    // Iterate over the internal linked list starting at offset 0 of this
    Node* current = *(Node**)this;
    while (current != nullptr) {
        Node* next = current->next; // save next before moving node to free list

        // First-time initialization: set global flag, call poolInit, register atexit
        if ((g_poolInitialized & 1) == 0) {
            g_poolInitialized |= 1;
            poolInit();
            _atexit(poolShutdown);
        }

        // Decrement global pool count
        g_poolCount--;

        // Move current node to the global free list
        current->next = g_poolFreeList;
        g_poolFreeList = current;

        current = next;
    }
}
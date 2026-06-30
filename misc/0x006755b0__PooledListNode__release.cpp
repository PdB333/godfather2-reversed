// FUNC_NAME: PooledListNode::release
void __thiscall PooledListNode::release(void) {
    // Check for null this pointer
    if (this == nullptr) {
        return;
    }

    PooledListNode* nextNode = this->next;          // +0x04
    PoolAllocator* allocator = this->allocator;     // +0x00

    // Remove next node from the pool if it exists
    if (nextNode != nullptr) {
        // Index of the next node is stored 8 bytes before its data pointer (header offset -8)
        int nextIndex = *(int*)((char*)nextNode - 8);
        // Array of active node pointers is at allocator + 0x0C
        void** activeArray = *(void***)((char*)allocator + 0x0C);
        activeArray[nextIndex] = nullptr;           // mark slot as free

        // Decrement reference count in allocator at offset +0x04
        int* refCount = (int*)((char*)allocator + 4);
        (*refCount)--;

        // Free the memory block of the next node (block starts 0x10 bytes before the data)
        operator delete((char*)nextNode - 0x10);    // or custom allocator free (DAT_01206694)
    }

    // Now remove this node itself
    // Index of this node is stored 8 bytes before its data pointer (this[-2])
    int thisIndex = *(int*)((char*)this - 8);
    void** activeArray = *(void***)((char*)this->allocator + 0x0C);
    activeArray[thisIndex] = nullptr;

    int* refCount = (int*)((char*)this->allocator + 4);
    (*refCount)--;

    // Free this node's block (starts 4 bytes before the data pointer)
    operator delete((char*)this - 4);
}
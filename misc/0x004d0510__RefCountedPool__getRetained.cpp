// FUNC_NAME: RefCountedPool::getRetained
// Address: 0x004d0510
// Implements a thread-safe object pool with reference counting.
// The pool stores pointers to allocated objects in a circular buffer.
// Returns a pointer to an object with its reference count incremented.
// If the pool is empty, returns nullptr.

int* RefCountedPool::getRetained() {
    bool bSuccess = false;
    int* pObj = nullptr;

    EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x28)); // poolCS

    if (*(int*)(this + 0x24) != 0) { // availableCount > 0
        // Retrieve object pointer from circular buffer
        pObj = *(int**)(*(int*)(this + 0x18) + *(int*)(this + 0x20) * 4); // bufferBase[currentIndex]
        
        // Advance index with wrap-around
        int newIndex = *(int*)(this + 0x20) + 1; // currentIndex + 1
        *(int*)(this + 0x20) = newIndex;
        if (*(int*)(this + 0x1c) <= newIndex) { // maxCount <= newIndex
            *(int*)(this + 0x20) = 0;
        }
        
        // Decrement available count
        *(int*)(this + 0x24) = *(int*)(this + 0x24) - 1; // availableCount--
        bSuccess = true;
    }

    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x28));

    if (bSuccess) {
        // Increment reference count of the object
        *pObj = *pObj + 1; // refCount++
    }

    return pObj;
}
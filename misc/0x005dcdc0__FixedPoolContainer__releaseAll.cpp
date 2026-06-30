// FUNC_NAME: FixedPoolContainer::releaseAll
// Function address: 0x005dcdc0
// This function returns all pooled elements from the container back to the global pool,
// then frees the internal array and calls an optional cleanup callback.
// The container stores an array of pointers to objects allocated from a fixed-size pool.
// The global pool is a FreeListPool with head at +0x44, free count at +0x1c, allocated count at +0x20.

struct FreeListPool {
    int freeCount;         // +0x1c
    int allocatedCount;    // +0x20
    void* freeListHead;    // +0x44
    // ... other fields
};

extern FreeListPool* g_pool; // DAT_01223508

class FixedPoolContainer {
public:
    void** m_elementsArray;   // +0x270
    uint m_elementCount;      // +0x274
    uint m_capacityOrFlag;    // +0x278 (set to 0 after freeing)
    void* m_cleanupObject;    // +0x2a0
    void (*m_cleanupFunc)(void*); // +0x2ac

    __thiscall void releaseAll(void) {
        FreeListPool* pool = g_pool;
        uint count = this->m_elementCount;
        
        // Return each element to the pool's free list
        for (uint i = 0; i < count; i++) {
            void** element = reinterpret_cast<void**>(this->m_elementsArray)[i];
            if (element != nullptr) {
                // Link element back into free list
                *element = pool->freeListHead;
                pool->allocatedCount--;
                pool->freeCount++;
                pool->freeListHead = element;
            }
        }
        
        // Clear count
        this->m_elementCount = 0;
        
        // Free the array itself (presumably allocated with operator new[])
        operator delete[](this->m_elementsArray); // FUN_009c8f10
        this->m_elementsArray = nullptr;
        this->m_capacityOrFlag = 0;
        
        // Call optional cleanup callback
        if (this->m_cleanupObject != nullptr) {
            this->m_cleanupFunc(this->m_cleanupObject);
        }
        
        // Second check (likely compiler artifact or for safety)
        if (this->m_elementsArray != nullptr) {
            operator delete[](this->m_elementsArray);
        }
    }
};
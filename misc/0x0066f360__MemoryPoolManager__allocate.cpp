// FUNC_NAME: MemoryPoolManager::allocate
// Function address: 0x0066f360
// Role: Allocates memory from a pool-based allocator. Iterates through fixed-size pools,
// returns a block from the pool's free list or allocates a new one via the pool's allocator.
// Falls back to a generic allocator if no pool matches.

class MemoryPoolManager {
public:
    int m_poolCount;               // +0x08
    PoolDescriptor** m_pools;      // +0x0C
    AllocatorInterface* m_fallback;// +0x10

    void* allocate(uint size);
};

// Describes a single fixed-size pool.
class PoolDescriptor {
public:
    void* m_freeListHead;          // +0x08  linked list of free blocks
    uint m_blockSize;              // +0x0C  size of each block in this pool
    uint m_unknownArg;             // +0x10  passed to custom allocator when creating new blocks
    int m_freeCount;               // +0x14  number of blocks currently in free list
    int m_minFree;                 // +0x18  tracked minimum free count
    AllocatorInterface* m_allocator; // +0x1C  custom allocator for this pool (may be null)
};

// Abstract allocator interface used by pools and fallback.
class AllocatorInterface {
public:
    virtual void* allocate(uint size, uint extraArg) = 0; // vtable+4
};

__thiscall void* MemoryPoolManager::allocate(uint size) {
    // Try to find a pool that can satisfy the request and has free blocks.
    for (int i = 0; i < m_poolCount; i++) {
        PoolDescriptor* pool = m_pools[i];

        // Check if this pool's block size is >= requested size and has free blocks.
        if (size <= pool->m_blockSize && pool->m_freeCount != 0) {
            void* ptr = pool->m_freeListHead;

            if (ptr != nullptr) {
                // Pop block from free list.
                pool->m_freeListHead = *(void**)ptr;
                pool->m_freeCount--;

                // Update minimum free count tracked.
                if (pool->m_freeCount < pool->m_minFree) {
                    pool->m_minFree = pool->m_freeCount;
                }

                return ptr;
            } else {
                // Free list empty: use pool's custom allocator if available.
                if (pool->m_allocator != nullptr) {
                    return pool->m_allocator->allocate(pool->m_blockSize, pool->m_unknownArg);
                }
                // Otherwise skip this pool (fallback to next or global).
            }
        }
    }

    // No suitable pool found: use fallback allocator.
    if (m_fallback != nullptr) {
        return m_fallback->allocate(size, 0x10);
    }

    return nullptr;
}
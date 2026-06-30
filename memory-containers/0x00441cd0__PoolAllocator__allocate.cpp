// FUNC_NAME: PoolAllocator::allocate
void* PoolAllocator::allocate()
{
    // DAT_01223428 is a global pointer to a pool manager or static instance
    // Offsets: 
    //   +0x1c: pointer to the active pool instance (PoolAllocator*)
    // PoolAllocator members:
    //   +0x08: freeList (linked list head)
    //   +0x0c: elementSize (size of each element)
    //   +0x10: elementCount (number of elements)
    //   +0x14: usedCount (number of currently allocated elements)
    //   +0x18: minUsedCount (low watermark of usedCount, updated on free)
    //   +0x1c: fallbackAllocator (pointer to an object with a vtable, allocate at vtable+4)
    PoolAllocator* pool = *(PoolAllocator**)((char*)g_poolManager + 0x1c);
    void* node = pool->freeList;
    if (node != nullptr)
    {
        // Pop from free list
        pool->freeList = *(void**)node;           // next node
        pool->usedCount--;
        if ((uint32_t)pool->usedCount < (uint32_t)pool->minUsedCount)
        {
            pool->minUsedCount = pool->usedCount;
        }
        return node;
    }
    // If free list is empty and a fallback allocator exists, use it
    if (pool->fallbackAllocator != nullptr)
    {
        // Fallback allocator's vtable entry +4 is the allocate function
        IAllocator* fallback = pool->fallbackAllocator;
        return fallback->vtable[1](pool->elementSize, pool->elementCount);
    }
    return nullptr;
}
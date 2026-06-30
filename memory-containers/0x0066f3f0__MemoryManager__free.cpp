// FUNC_NAME: MemoryManager::free
// Function at 0x0066f3f0: Memory pool deallocation. Given a pointer to free, it finds the owning pool and either adds it to a free list or delegates to a custom deallocator.
// Structure fields commented with offsets in bytes.
// The function receives 'this' in ECX and the pointer to free in ESI (register parameter).

void MemoryManager::free(void* ptr)
{
    PoolDescriptor* pool;
    uint32_t i;

    // 'ptr' corresponds to unaff_ESI in the decompiled code.
    if (ptr == 0) return;

    // Main region range: from this->mainBase to this->mainBase + this->mainSize
    // Check if ptr falls outside the main managed region
    if (this->vtable != 0 && 
        (ptr < this->mainBase || ptr >= (void*)((uint8_t*)this->mainBase + this->mainSize)))
    {
        // Outside main range: delegate to parent allocator's free method
        // parentAllocator is at this->vtable (offset 0x10). Its vtable's function at index 8 is the deallocator.
        void** parentVtable = *(void***)this->vtable;
        typedef void (__thiscall ParentFreeFunc)(void* self, void* ptr);
        ParentFreeFunc* parentFree = (ParentFreeFunc*)(parentVtable[2]); // offset 8 = index 2
        parentFree(this->vtable, ptr);
        return;
    }

    // ptr is within main region; find which pool descriptor owns it
    pool = 0;
    for (i = 0; i < this->numPools; i++)
    {
        PoolDescriptor* currentPool = this->pools[i];
        // Check if ptr falls within this pool's address range
        if (ptr >= currentPool->base && ptr < (void*)((uint8_t*)currentPool->base + currentPool->size))
        {
            pool = currentPool;
            break;
        }
    }

    if (pool == 0)
    {
        // No pool found (should not happen if ptr is valid)
        return;
    }

    // Check if the pool has a custom deallocator (via vtable at offset 0x1C)
    if (pool->vtable != 0)
    {
        // ptr must be within the pool's range, but we double-check:
        if (ptr < pool->base || ptr >= (void*)((uint8_t*)pool->base + pool->size))
        {
            // If outside (should not happen), call custom deallocator
            void** poolVtable = *(void***)pool->vtable;
            typedef void (__thiscall PoolFreeFunc)(void* self, void* ptr);
            PoolFreeFunc* poolFree = (PoolFreeFunc*)(poolVtable[2]); // offset 8 = index 2
            poolFree(pool->vtable, ptr);
            return;
        }
    }

    // Normal free list insertion
    // The freed block's first word points to the previous free head
    *(uint32_t*)ptr = (uint32_t)pool->freeHead;
    pool->freeCount++;
    pool->freeHead = ptr;
}
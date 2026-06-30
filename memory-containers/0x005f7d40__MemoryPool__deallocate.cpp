// FUNC_NAME: MemoryPool::deallocate

void __thiscall MemoryPool::deallocate(void* this, uint32_t* ptr)
{
    uint32_t* node;
    uint32_t* listHead;
    uint32_t freeList[4]; // local buffer for list removal

    if (ptr != nullptr) {
        // Traverse the active list to find the node tracking this allocation
        for (node = *(uint32_t**)((uint32_t)this + 0x6c);
            (listHead = *(uint32_t**)((uint32_t)this + 0x6c), node != listHead);
            node = (uint32_t*)*node)
        {
            if (node == *(uint32_t**)((uint32_t)this + 0x6c)) {
                debugAssert("Circular list assertion");
            }
            if (node[2] == (uint32_t)ptr) {
                // Remove the node from the tracked allocations list
                removeFromList(freeList, (void*)((uint32_t)this + 0x54), node);
                break;
            }
            if (node == *(uint32_t**)((uint32_t)this + 0x6c)) {
                debugAssert("Circular list assertion");
            }
        }

        // Call the object's destructor (vtable first entry)
        (**(void (__thiscall**)(void*))(*(uint32_t*)ptr))(ptr);

        // Return the memory to the pool's free list
        uint32_t* poolDescriptor = *(uint32_t**)(g_poolManager + 0x28);
        uint32_t* freeHead = (uint32_t*)*poolDescriptor;
        if (freeHead != nullptr) {
            // Check if the pointer is within the existing free block range
            if ( ((int*)poolDescriptor[7] != nullptr) &&
                (ptr < freeHead ||
                 (uint32_t*)((uint8_t*)poolDescriptor[1] + (uint32_t)freeHead) <= ptr) )
            {
                // Custom deallocation via callback
                (**(void (__thiscall**)(void*))(*(int*)poolDescriptor[7] + 8))(ptr);
                return;
            }
            // Insert the freed pointer into the free list
            *ptr = poolDescriptor[2];
            poolDescriptor[5] += 1;
            poolDescriptor[2] = (uint32_t)ptr;
        }
    }
}
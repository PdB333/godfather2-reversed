// FUNC_NAME: MemoryManager::allocate
// Function address: 0x005cc330
// Role: Allocate memory from global heaps (EARS allocator)

void* MemoryManager::allocate(uint size)
{
    // Check if primary heap exists
    if (g_pPrimaryHeap != nullptr)
    {
        // Prepare allocation output structure (possibly size/alignment info)
        AllocInfo info = {0, 0, 0, 0};

        // Call virtual allocate on primary heap (vtable offset 4)
        // This likely fills in info with a memory pointer or offset
        g_pPrimaryHeap->alloc(size, &info);

        // Obtain final memory block from secondary heap/pool
        void* mem = g_pSecondaryHeap->allocFromInfo(&info);

        if (mem != nullptr)
        {
            // Write type tag (4) into first byte of allocated memory
            memcpy(mem, &kTypeTag4, 1);
            // Invoke allocation callback (e.g., reference counting)
            g_pAllocCallback(4);
            return mem;
        }

        // Cleanup callback on failure
        g_pAllocCallback(4);
    }
    return nullptr;
}
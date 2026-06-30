// FUNC_NAME: EAPoolAllocator::allocateBlock
// Address: 0x004abf10
// Role: Fixed-size block allocator with free list and fallback allocator.

struct EAPoolAllocator
{
    void*       m_pFreeList;      // +0x08: Pointer to first free block (linked list)
    int         m_elementSize;    // +0x0c: Size of each block (passed to fallback)
    int         m_alignment;      // +0x10: Alignment requirement (passed to fallback)
    int         m_freeCount;      // +0x14: Number of blocks currently free
    int         m_minFreeCount;   // +0x18: Minimum free count observed (statistics)
    void*       m_pFallback;      // +0x1c: Pointer to fallback allocator object (vtable-based)
    // The fallback object's vtable has alloc function at offset +0x04:
    // typedef void* (__thiscall *FallbackAllocFn)(void* self, int size, int alignment);
};

// Reconstructed __thiscall method
void* __thiscall EAPoolAllocator::allocateBlock()
{
    void* pBlock = m_pFreeList;
    if (pBlock != nullptr)
    {
        // Pop head of free list (first word of block points to next free block)
        m_pFreeList = *(void**)pBlock;
        m_freeCount--;
        // Track minimum free count for diagnostics
        if (m_freeCount < m_minFreeCount)
            m_minFreeCount = m_freeCount;
        return pBlock;
    }

    // Fallback to external allocator (if set)
    if (m_pFallback != nullptr)
    {
        // Call fallback object's alloc method (second vtable entry)
        // The fallback is a pointer to an object with a vtable;
        // offset +0x04 is the alloc(size, alignment) method.
        typedef void* (__thiscall *AllocFn)(void* self, int size, int alignment);
        AllocFn allocFn = *(AllocFn*)(*(int**)m_pFallback + 4);
        return allocFn(m_pFallback, m_elementSize, m_alignment);
    }

    return nullptr;
}
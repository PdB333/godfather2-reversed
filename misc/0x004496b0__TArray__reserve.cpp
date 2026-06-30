// FUNC_NAME: TArray::reserve
void __thiscall TArray::reserve(uint newCapacity)
{
    // Fields at offsets (relative to this):
    // +0x00: m_pData      (int*) - pointer to element storage
    // +0x04: m_nCount     (uint) - number of elements currently stored
    // +0x08: m_nCapacity  (uint) - current allocated capacity
    // +0x0C: m_pAlloc     (void*) - custom allocator (0 = use global default)
    // +0x10: m_pAllocVtbl (void**) - vtable for allocator object

    if (m_nCapacity >= newCapacity)
        return;

    // Determine allocator to use
    void* allocator = m_pAlloc;
    if (allocator == nullptr)
        allocator = &DAT_01218a14;  // global default allocator

    // Allocate new memory: each element is 8 bytes
    // The first vtable entry is an allocation function: (void* __thiscall *)(void* alloc, size_t size)
    typedef void* (__thiscall *AllocFunc)(void*, size_t);
    AllocFunc allocFunc = *(AllocFunc*)(*(int*)m_pAllocVtbl); // vtable[0]
    void* newData = allocFunc(allocator, newCapacity * 8);

    // Copy existing data (8 bytes per element)
    if (m_pData != nullptr && m_nCount > 0)
    {
        for (uint i = 0; i < m_nCount; i++)
        {
            if (newData != nullptr)
            {
                // Copy 8-byte element
                ((uint32_t*)newData)[i * 2] = ((uint32_t*)m_pData)[i * 2];
                ((uint32_t*)newData)[i * 2 + 1] = ((uint32_t*)m_pData)[i * 2 + 1];
            }
        }
    }

    // Free old memory using allocator's deallocation function (vtable[1])
    // Deallocation signature: (void __thiscall *)(void* alloc, void* ptr, uint32_t param)
    typedef void (__thiscall *FreeFunc)(void*, void*, uint32_t);
    FreeFunc freeFunc = *(FreeFunc*)(*(int*)m_pAllocVtbl + 4); // vtable[1]
    freeFunc(allocator, (void*)m_pData, 0);

    // Update members
    m_pData = (int*)newData;
    m_nCapacity = newCapacity;
}
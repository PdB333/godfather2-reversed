// FUNC_NAME: PathSegment::~PathSegment()
void __thiscall PathSegment::~PathSegment()
{
    // Check if the path allocator is valid and not a null pointer (0x48 is used as sentinel?)
    if (m_pPathAlloc && m_bSomeFlag && m_pPathAlloc != (void*)0x48)
    {
        // Add the path node to the free list in the global allocator
        int* freeListHead = (int*)(g_pGlobalAllocator + 0x14); // global allocator's free list head pointer
        *(int**)*freeListHead = &PTR_LAB_0110baa8;           // set free chunk marker
        *freeListHead += 4;
        *(int**)*freeListHead = &m_pPathNode;                // store address of the node member (offset 0x54)
        *freeListHead += 4;
        *(int*)*freeListHead = 0;                            // null terminator
        *freeListHead += 4;

        // Get the container object from the path pointer (offset 0x48 into the container)
        PathContainer* container = (m_pPathAlloc == 0) ? nullptr : (PathContainer*)((char*)m_pPathAlloc - 0x48);
        // Call the container's virtual method at vtable offset 0x54
        container->VMethod_0x54();
    }

    int* pPathAllocField = &m_pPathAlloc; // offset 0x68
    if (m_pPathAlloc && m_pPathAlloc != (void*)0x48)
    {
        PathContainer* container2 = (m_pPathAlloc == 0) ? nullptr : (PathContainer*)((char*)m_pPathAlloc - 0x48);
        // Call a method on the container with -1 as parameter, then call our own virtual method with the result
        uint result = container2->VMethod_0x58(0xffffffff);
        this->VMethod_0x5c(result);
    }

    // Clear the lowest bit of the flags at offset 0x15E
    *(unsigned short*)((int)this + 0x15E) &= 0xfffe;

    if (m_pPathAlloc)
    {
        FUN_004daf90(pPathAllocField); // likely frees the path allocator or its data
        m_pPathAlloc = 0;
    }

    // Zero out three fields at offsets 0x70, 0x74, 0x78
    m_Field0x70 = 0;
    m_Field0x74 = 0;
    m_Field0x78 = 0;
}
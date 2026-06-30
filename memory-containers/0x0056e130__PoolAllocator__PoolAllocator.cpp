// FUNC_NAME: PoolAllocator::PoolAllocator
// Address: 0x0056e130
// Role: Constructor that initializes a fixed-size pool allocator. Takes a backing allocator (heap allocator), element count, and an opaque parameter (likely a heap pointer or name). Sets up a doubly linked free list of elements of size 0x38 bytes, allocates a large auxiliary buffer, and obtains an allocation buffer via the backing allocator.

PoolAllocator * __thiscall PoolAllocator::PoolAllocator(PoolAllocator *this, HeapAllocator *heapAlloc, int elemCount, void *userParam)
{
    void *poolBase;

    g_poolAllocatorSingleton = this; // DAT_012234e8
    this->m_vtable = &PoolAllocator_vtable; // PTR_FUN_00e3abdc
    this->m_pHeapAllocator = heapAlloc;
    // Call a virtual function on the heap allocator (likely a prepare/init)
    (*(void (**)(void))(*(int *)heapAlloc + 8))();
    this->m_freeListTail = 0;
    this->m_numAllocated = 0;
    poolBase = AllocatePool_0056e020(); // Returns a block of elemCount * 0x38 bytes
    this->m_pPool = poolBase;
    this->m_pFreeListHead = poolBase;
    this->m_elementCount = elemCount;
    // Build doubly linked free list
    if (elemCount != 0) {
        for (int i = 0; i < elemCount; i++) {
            char *current = (char *)this->m_pFreeListHead + i * 0x38;
            if (i != 0) {
                *(int *)(current + 4) = (int)(current - 0x38); // prev link
            }
            if (i < elemCount - 1) {
                *(int *)current = (int)(current + 0x38); // next link
            }
        }
    }
    // Zero out a 0x1000-byte buffer starting at offset 0x30
    int *buffer = (int *)((char *)this + 0x30);
    for (int j = 0x400; j != 0; j--) {
        *buffer++ = 0;
    }
    // Store user parameter
    this->m_userParam = userParam;
    // Allocate a small buffer from the heap allocator (size=2, alignment=0x10, flags=0)
    AllocationRequest req;
    req.size = 2;
    req.alignment = 0x10;
    req.flags = 0;
    this->m_pAuxBuffer = (void *)(*(int (__thiscall **)(HeapAllocator *, void *, AllocationRequest *))(*(int *)heapAlloc))(heapAlloc, userParam, &req);
    PostInitialize_0056e530();
    return this;
}
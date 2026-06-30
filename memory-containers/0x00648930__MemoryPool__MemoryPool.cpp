// FUNC_NAME: MemoryPool::MemoryPool
void __thiscall MemoryPool::MemoryPool(void) {
    // Clear first three bytes (flags or padding)
    this->m_flags[0] = 0;
    this->m_flags[1] = 0;
    this->m_flags[2] = 0;

    // Configuration fields
    this->m_blockSize = 0x10;          // +0x178: block size (16 bytes)
    this->m_blockCount = 0;            // +0x17c: number of blocks
    this->m_memcpyFunc = _memcpy;      // +0x180: pointer to memcpy
    this->m_memsetFunc = _memset;      // +0x184: pointer to memset
    this->m_allocFunc = &LAB_0064acb0; // +0x188: allocation function
    this->m_freeFunc = &LAB_00649db0;  // +0x1a4: free function
    this->m_alignFunc = &LAB_0064ac80; // +0x1ac: alignment function
    this->m_alignment = 4;             // +0x1a0: alignment (4 bytes)
    this->m_id1 = 9;                   // +0x1b4: some ID
    this->m_id2 = 10;                  // +0x1b5: another ID
    this->m_id3 = 0;                   // +0x1b6: padding

    // Zero out remaining fields
    this->m_field_18c = 0;
    this->m_field_190 = 0;
    this->m_field_194 = 0;
    this->m_field_198 = 0;
    this->m_field_19c = 0;
    this->m_field_1a8 = 0;
    this->m_field_1b0 = 0;
    this->m_field_1b8 = 0;
    this->m_field_1c0 = 0;
    this->m_field_1c8 = 0;
    this->m_field_1d0 = 0;
    this->m_field_1d8 = 0;

    // Call internal initialization (likely critical section or global state)
    FUN_00649ec0();

    // Initialize first list (sentinel at +0x04)
    // The list node at +0x04 is a sentinel with prev/next pointers
    long long* sentinel1 = (long long*)((char*)this + 4);
    *sentinel1 = 0;                     // clear first 8 bytes
    *(long long*)((char*)this + 0xc) = 0;
    *(long long*)((char*)this + 0x14) = 0;
    *(long long*)((char*)this + 0x1c) = 0;
    *(long long*)((char*)this + 0x24) = 0;
    // Set list head pointers to point to sentinel
    *(long long**)((char*)this + 0x1c) = sentinel1; // next
    *(long long**)((char*)this + 0x18) = sentinel1; // prev

    // Clear a 256-byte block at +0x78 (used as sentinel for multiple lists)
    char* baseSentinel = (char*)this + 0x78;
    *(long long*)((char*)this + 0x44) = 0;
    *(long long*)((char*)this + 0x4c) = 0;
    memset(baseSentinel, 0, 0x100);

    // Initialize multiple doubly linked lists with sentinel nodes
    // Each list has a pair of pointers (prev/next) stored at fixed offsets
    // List 1: sentinel at +0x78, pointers at +0x8c (prev) and +0x90 (next)
    *(void**)((char*)this + 0x90) = baseSentinel;
    *(void**)((char*)this + 0x8c) = baseSentinel;

    // List 2: sentinel at +0x98, pointers at +0xac and +0xb0
    *(void**)((char*)this + 0xb0) = (char*)this + 0x98;
    *(void**)((char*)this + 0xac) = (char*)this + 0x98;

    // List 3: sentinel at +0xb8, pointers at +0xcc and +0xd0
    *(void**)((char*)this + 0xd0) = (char*)this + 0xb8;
    *(void**)((char*)this + 0xcc) = (char*)this + 0xb8;

    // List 4: sentinel at +0xd8, pointers at +0xec and +0xf0
    *(void**)((char*)this + 0xf0) = (char*)this + 0xd8;
    *(void**)((char*)this + 0xec) = (char*)this + 0xd8;

    // List 5: sentinel at +0xf8, pointers at +0x10c and +0x110
    *(void**)((char*)this + 0x110) = (char*)this + 0xf8;
    *(void**)((char*)this + 0x10c) = (char*)this + 0xf8;

    // List 6: sentinel at +0x118, pointers at +0x12c and +0x130
    *(void**)((char*)this + 0x130) = (char*)this + 0x118;
    *(void**)((char*)this + 0x12c) = (char*)this + 0x118;

    // List 7: sentinel at +0x138, pointers at +0x14c and +0x150
    *(void**)((char*)this + 0x150) = (char*)this + 0x138;
    *(void**)((char*)this + 0x14c) = (char*)this + 0x138;

    // List 8: sentinel at +0x158, pointers at +0x16c and +0x170
    *(void**)((char*)this + 0x170) = (char*)this + 0x158;
    *(void**)((char*)this + 0x16c) = (char*)this + 0x158;
}
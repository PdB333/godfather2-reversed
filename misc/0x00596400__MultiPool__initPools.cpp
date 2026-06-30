// FUNC_NAME: MultiPool::initPools
void __thiscall MultiPool::initPools(MultiPool *this, int count0, int count1, int count2)
{
    // Check if already initialized (byte at +0x04)
    if (this->m_bInitialized)
        return;

    // Store pool sizes
    this->m_count0 = count0;    // +0x08
    this->m_count2 = count2;    // +0x10
    this->m_bInitialized = 1;   // +0x04 (byte)
    this->m_count1 = count1;    // +0x0C

    // Pool 0 free list head
    this->m_freeIndex0 = 0;     // +0x1C

    // Allocate object array and index array for pool 0
    this->m_objects0 = (int*)gAllocator.allocate(count0 * 4);    // +0x14
    this->m_indices0 = (int*)gAllocator.allocate(this->m_count0 * 4); // +0x18

    // Initialize pool 0: create objects and set free list
    for (int i = 0; i < this->m_count0; i++)
    {
        this->m_objects0[i] = (this->vtbl->createPool0Object)(); // vtable+0x10
        this->m_indices0[i] = i + 1;
    }
    this->m_indices0[this->m_count0 - 1] = -1; // terminator

    this->m_freeIndex1 = 0;     // +0x28

    // Pool 1
    this->m_objects1 = (int*)gAllocator.allocate(this->m_count1 * 4); // +0x20
    this->m_indices1 = (int*)gAllocator.allocate(this->m_count1 * 4); // +0x24
    for (int i = 0; i < this->m_count1; i++)
    {
        this->m_objects1[i] = (this->vtbl->createPool1Object)(); // vtable+0x14
        this->m_indices1[i] = i + 1;
    }
    this->m_indices1[this->m_count1 - 1] = -1;

    this->m_freeIndex2 = 0;     // +0x34

    // Pool 2
    this->m_objects2 = (int*)gAllocator.allocate(this->m_count2 * 4); // +0x2C
    this->m_indices2 = (int*)gAllocator.allocate(this->m_count2 * 4); // +0x30
    for (int i = 0; i < this->m_count2; i++)
    {
        this->m_objects2[i] = (this->vtbl->createPool2Object)(); // vtable+0x18
        this->m_indices2[i] = i + 1;
    }
    this->m_indices2[this->m_count2 - 1] = -1;
}
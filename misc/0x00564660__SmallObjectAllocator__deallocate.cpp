// FUNC_NAME: SmallObjectAllocator::deallocate
void __thiscall SmallObjectAllocator::deallocate(void* this)
{
    // +0x00: base pointer to memory pool
    void* poolBase = *(void**)this;
    // +0x08: allocation index (size class or slot index)
    int allocIdx = *(int*)((char*)this + 8);

    if (allocIdx >= 0)
    {
        // Retrieve thread-local storage value (ignored – allocator state)
        TlsGetValue(DAT_01139810);
        // Free block: poolBase + (allocIdx * 16), type 0x17 (unknown)
        // FUN_00aa26e0 is internal memory deallocation routine
        FUN_00aa26e0(poolBase, allocIdx << 4, 0x17);
    }
}
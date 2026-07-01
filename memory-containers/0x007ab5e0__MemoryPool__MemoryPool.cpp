// FUNC_NAME: MemoryPool::MemoryPool
MemoryPool * __thiscall MemoryPool::MemoryPool(MemoryPool *this, void *poolBuffer, int poolSize)
{
    // Call to global pool initialization routine (likely sets up internal allocator)
    FUN_0080e6a0(poolBuffer, poolSize);

    // Set vtable pointer
    this->vtable = &PTR_LAB_00d6b95c; // vtable for MemoryPool

    // Clear byte at offset 0x1c (e.g., a flag or pad)
    this->field_0x1c = 0;

    // Compute base address from internal pointer at offset 0x48
    // If that pointer is null, base becomes zero (dummy base)
    int base;
    if (this->ptr_0x48 == 0)
    {
        base = 0;
    }
    else
    {
        base = (int)this->ptr_0x48 - 0x48; // offset to start of pool header?
    }

    // Set pointers to sub‑regions within the pool
    // Each offset is relative to 'base'
    this->poolBase        = (char *)base;              // +0x58: base of pool
    this->regionA         = (char *)(base + 0x26ac);   // +0x5c: region A (size 0x26ac from base)
    this->regionB         = (char *)(base + 0x26c4);   // +0x60: region B
    this->regionC         = (char *)(base + 0x26b8);   // +0x64: region C
    this->regionD         = (char *)(base + 0x2744);   // +0x68: region D
    this->regionE         = (char *)(base + 0x2738);   // +0x6c: region E

    return this;
}
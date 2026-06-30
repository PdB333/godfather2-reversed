// FUNC_NAME: TLSFixedSizeAllocator::allocateBlock
int * __thiscall TLSFixedSizeAllocator::allocateBlock(int *this, uint blockCount)
{
    uint totalSize;
    int *tlsContext;
    int fallbackResult;
    int allocSize;

    // Initialize this allocator header: pointer to 0, no previous, flags
    this[0] = 0;           // +0x00: next pointer
    this[1] = 0;           // +0x04: previous pointer or unused
    this[2] = -0x80000000; // +0x08: flags (top bit set, indicating allocated from pool)
    // Retrieve thread-local storage context (pointer to per-thread allocator state)
    tlsContext = (int *)TlsGetValue(DAT_01139810);
    allocSize = blockCount * 0x40 + 0x10; // total bytes needed: 16 header + blockCount*64
    totalSize = tlsContext[8] + allocSize; // +0x20 offset? likely current offset + needed
    if (totalSize < (uint)tlsContext[0xb]) { // +0x2c: pool capacity?
        // Allocate from the linear pool by advancing the offset
        tlsContext[8] += allocSize;
        fallbackResult = tlsContext[8] - allocSize; // get the starting address
    } else {
        // Pool exhausted: call fallback allocator (virtual function at vtable+0x14)
        fallbackResult = (**(int (__thiscall **)(int *))(tlsContext[0] + 0x14))(tlsContext);
    }
    this[0] = fallbackResult;  // +0x00: allocation base address
    this[3] = fallbackResult;  // +0x0c: possibly the same address used for iteration
    // Store back the block count with a flag indicating this header owns the memory
    this[2] = blockCount | 0x80000000;
    return this;
}
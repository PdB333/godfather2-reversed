// FUNC_NAME: EARSAllocator::allocateChunk
// Function at 0x005407c0: Constructs a fixed-size allocator chunk from TLS-based pool
// Typically part of EA's internal memory management system (EARSAllocator)

int * __thiscall EARSAllocator::allocateChunk(int *thisChunk, uint chunkSize)
{
    uint alignedSize;
    int *tlsValue;
    int rawMemPool;
    uint totalSize;
    uint capacity;

    // Initialize the chunk metadata structure
    // offset +0x00: pointer to raw memory
    thisChunk[0] = 0;
    // offset +0x04: next free pointer (or end marker)
    thisChunk[1] = 0;
    // offset +0x08: size/capacity flags - initial capacity with high bit set for 'uninitialized'
    thisChunk[2] = -0x80000000;

    // Get the thread-local storage value (likely pointer to a TLS heap context)
    tlsValue = (int *)TlsGetValue(DAT_01139810);

    // +0x20 in TLS context: current allocation offset in the pool
    rawMemPool = tlsValue[8];

    // Align requested size to 16-byte boundary
    // Calculate total size: metadata overhead is 0x10 bytes, plus actual storage aligned to 16
    alignedSize = chunkSize * 8 + 0x10 & 0xfffffff0;
    totalSize = rawMemPool + alignedSize;

    // Check if TLS pool has enough remaining space (capacity stored at +0x2C)
    capacity = (uint)tlsValue[0xb];
    if (capacity < totalSize) {
        // Not enough space: call allocation callback (at vtable+0x14) to get more memory
        rawMemPool = (**(code **)(*tlsValue + 0x14))(alignedSize);
    } else {
        // Enough space: advance the pool offset
        tlsValue[8] = totalSize;
    }

    // Store the raw memory pointer
    thisChunk[0] = rawMemPool;
    // +0x0C: also store it as the 'current write position'
    thisChunk[3] = rawMemPool;
    // +0x08: set the chunk capacity, with high bit cleared to mark as 'initialized'
    thisChunk[2] = chunkSize | 0x80000000;

    return thisChunk;
}
// FUNC_NAME: MemoryPool::allocateFromPool
// Address: 0x0069b380
// Role: Allocates a block from a fixed-size memory pool. If the requested size matches the pool's block size,
//   it attempts to reuse a block from the free list; otherwise falls back to a general allocation path.
// Offsets: +0x04 = mBlockSize (uint)

int __thiscall MemoryPool::allocateFromPool(uint requestedSize)
{
    uint alignedSize;
    uint originalAlignedSize;
    int blockIndex;
    int localArray1[3];   // Temporary block list (for chaining)
    int localArray2[3];   // Temporary block list
    code *pDtor1;         // Destructor for localArray1 elements
    code *pDtor2;         // Destructor for localArray2 elements
    int localVar;         // Single element
    code *pDtor3;         // Destructor for localVar

    alignedSize = requestedSize;
    alignSize(&alignedSize, requestedSize);  // FUN_00698c60 – rounds up size
    originalAlignedSize = alignedSize;
    if (alignedSize != mBlockSize) {
        // Size differs from pool's fixed block size – try to get a block from the free list
        blockIndex = tryAllocateFromFreeList(alignedSize + 0x10);  // FUN_004d4b20
        if (blockIndex >= 0) {
            return originalAlignedSize + 0x20;
        }
    }

    // Initialize empty block list
    localArray1[0] = 0;
    localArray1[1] = 0;
    localArray1[2] = 0;
    pDtor1 = nullptr;

    // Clean up any existing blocks in the free list? (FUN_004d3b50 might be deallocation)
    deallocateBlock(alignedSize);        // FUN_004d3b50
    deallocateBlock(localArray1);        // FUN_004d3b50

    // Perform the actual allocation using the general path
    alignedSize = alignedSize & 0xFFFFFF00;  // Align to 256-byte boundary
    allocateGeneral(&alignedSize, originalAlignedSize, localArray2, alignedSize);  // FUN_0069a730

    uint result = alignedSize;

    // Call destructors for any stale blocks
    if (localVar != 0) {
        pDtor3(localVar);
    }
    if (localArray2[0] != 0) {
        pDtor2(localArray2[0]);
    }
    if (localArray1[0] != 0) {
        pDtor1(localArray1[0]);
    }

    return result + 0x20;  // Return pointer past the 32-byte header
}
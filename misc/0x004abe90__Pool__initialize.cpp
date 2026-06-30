// FUNC_NAME: Pool::initialize
// Address: 0x004abe90
// Role: Initializes a fixed-block memory pool allocator from a pre-allocated buffer.
// Each block is aligned to the specified alignment; the pool links all blocks into a free list.

struct Pool {
    void*        pMemory;       // +0x00: pointer to the start of the pool memory
    uint32       totalSize;     // +0x04: total size of the pool memory
    void*        pFreeList;     // +0x08: head of the singly-linked free list
    uint32       elementSize;   // +0x0C: size of each block after alignment
    uint32       alignment;     // +0x10: alignment for block headers (minimum 4)
    uint32       freeCount;     // +0x14: current number of free blocks (initialized to numBlocks)
    uint32       numBlocks;     // +0x18: total number of blocks
    // +0x1C: reserved/unused (set to 0)
};

Pool* __thiscall Pool::initialize(void* pMemory, uint32 totalSize, uint32 elementSize, uint32 alignment)
{
    this->pMemory   = pMemory;
    this->totalSize = totalSize;
    this->pFreeList = nullptr;
    this->elementSize = elementSize;
    this->alignment   = alignment;
    // Clear reserved field
    *(uint32*)((uint8*)this + 0x1C) = 0;

    // Enforce minimum alignment of 4 bytes
    if (alignment < 4) {
        alignment = 4;
    }

    // Align elementSize upward to the next multiple of alignment
    uint32 misalignment = (alignment - 1) & elementSize;
    if (misalignment != 0) {
        elementSize = (alignment - misalignment) + elementSize;
    }
    this->elementSize = elementSize;

    // Calculate number of blocks (truncated integer division)
    uint32 blockCount = totalSize / elementSize;
    this->numBlocks = blockCount;
    this->freeCount = blockCount;

    // Build the free list by linking each block's header to the previous block
    uint8* currentBlock = (uint8*)pMemory;
    uint8* prevBlock = nullptr;
    for (uint32 i = 0; i < blockCount; ++i) {
        // Store pointer to previous (or nullptr at end) in the first 4 bytes of each block
        *(void**)currentBlock = prevBlock;
        prevBlock = currentBlock;
        currentBlock += elementSize;
    }
    // The last block becomes the head of the free list
    this->pFreeList = prevBlock;

    return this;
}
// FUNC_NAME: MemoryPool::init
void __thiscall MemoryPool::init()
{
    // Pool header (4 words = 16 bytes), but we have 0x13 alignment padding before blocks.
    // Offsets: +0x18 = elementSize, +0x28 = count, +0x20 = alignment,
    //          +0x30 = freeHead, +0x34 = freeTail,
    //          +0x1c = allocationCount, +0x14 = totalAllocated, +0x0c = totalSize
    uint allocSize = elementSize * count + 0x13 + alignment;
    byte* rawMemory = new byte[allocSize]; // FUN_009c8e50(allocSize) - custom allocator

    PoolChunkHeader* chunk = (PoolChunkHeader*)rawMemory;
    chunk->nextChunk = nullptr;                // [0] = 0
    chunk->previousHead = (PoolChunkHeader*)freeHead; // [1] = old head

    if (freeHead) {
        ((PoolChunkHeader*)freeHead)->nextChunk = chunk; // link old head to new chunk
    }

    // Align start of data blocks to `alignment` boundary after the header
    uint alignedStart = (alignment + 0x13 + (uint)rawMemory) & ~(alignment - 1);
    byte* firstBlock = (byte*)alignedStart;
    byte* lastBlock = firstBlock + (count - 1) * elementSize; // +0x28

    chunk->firstBlock = firstBlock;  // [2]
    chunk->lastBlock = lastBlock;    // [3]

    // Initialize free list within this chunk
    for (byte* block = firstBlock; block <= lastBlock; block += elementSize) {
        *(void**)block = (void*)(block + elementSize);
    }

    // Link the last block to the previous free tail (from the pool)
    *(void**)lastBlock = (void*)freeTail;
    freeTail = firstBlock; // new head of free list

    // Update pool statistics
    allocationCount++;          // +0x1c
    totalAllocatedBytes += elementSize; // +0x14
    totalSize += elementSize;          // +0x0c
}
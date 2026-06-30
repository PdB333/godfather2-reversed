// FUNC_NAME: MemoryManager::splitFreeBlock

struct MallocBlock {
    uint32_t prevSize;        // +0x00 (size of previous block if free, else padding)
    uint32_t sizeAndFlags;    // +0x04 (size with low bit: 1 = previous block in use, 0 = free)
    MallocBlock* nextFree;    // +0x08
    MallocBlock* prevFree;    // +0x0C
};

struct Heap {
    uint8_t padding1[0x30];           // +0x00
    MallocBlock* freeListSentinel;     // +0x30 (fixed sentinel node)
    uint8_t padding2[0x0C];           // +0x34 (or more)
    MallocBlock* firstFreeBlock;       // +0x3C
    uint8_t padding3[0x408];          // +0x40 to +0x448
    MallocBlock* smallFreeListHead;    // +0x444 (for blocks < 0x200 bytes)
};

void __fastcall splitFreeBlock(int unused, uint requestedSize, Heap* heap, MallocBlock* freeBlock)
{
    // Unlink freeBlock from the free list (doubly linked)
    freeBlock->nextFree->prevFree = freeBlock->prevFree;
    freeBlock->prevFree->nextFree = freeBlock->nextFree;

    uint blockSize = freeBlock->sizeAndFlags & ~1;  // original free block size (low bit cleared)
    uint remainingSize = blockSize - requestedSize;

    if (remainingSize < 16) {
        // Remainder too small to be a free block; allocate the whole block
        // Mark the next block's prev_in_use bit to indicate this block is allocated
        uint32_t* nextBlockSizeField = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(freeBlock) + 4 + blockSize);
        *nextBlockSizeField |= 1;
        return;
    }

    // Split: create a new free block (remainder) at offset requestedSize
    MallocBlock* remainder = reinterpret_cast<MallocBlock*>(reinterpret_cast<char*>(freeBlock) + requestedSize);

    // Insert remainder at the front of the free list
    remainder->nextFree = heap->firstFreeBlock;
    remainder->prevFree = heap->freeListSentinel;          // sentinel node serves as tail marker
    heap->firstFreeBlock->prevFree = remainder;
    heap->firstFreeBlock = remainder;

    // If the allocation is small, also add remainder to the small-block free list
    if (requestedSize < 0x200) {
        heap->smallFreeListHead = remainder;
    }

    // Set the allocated block's size (with in-use flag)
    freeBlock->sizeAndFlags = requestedSize | 1;

    // Set the remainder block's size (with prev_in_use flag set for the allocated block)
    remainder->sizeAndFlags = remainingSize | 1;

    // Write the footer size at the end of the remainder block (for coalescing backward)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(remainder) + remainingSize) = remainingSize;
}
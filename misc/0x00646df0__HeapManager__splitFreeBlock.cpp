// FUNC_NAME: HeapManager::splitFreeBlock
// Takes a free block of blockSize bytes, removes it from the free list,
// allocates requestedSize bytes from the start, and returns the remainder
// as a new free block (if large enough). The blockSize is passed in EAX by the caller.
void __fastcall HeapManager::splitFreeBlock(int unused, uint requestedSize, HeapManager* manager, void* block, uint blockSize) {
    // Unlink the free block from the doubly‑linked free list
    // Offset +0x8: next, +0xC: prev in a FreeBlock header
    *(FreeBlock**)((char*)*(FreeBlock**)((char*)block + 8) + 0xC) = *(FreeBlock**)((char*)block + 0xC);
    *(FreeBlock**)((char*)*(FreeBlock**)((char*)block + 0xC) + 8) = *(FreeBlock**)((char*)block + 8);

    uint remainingSize = blockSize - requestedSize;

    if (remainingSize < 0x10) {
        // Remainder too small to split; mark the block as used and set a flag on the next block's header
        uint* nextBlockSize = (uint*)((char*)block + 4 + blockSize);
        *nextBlockSize |= 1;          // mark next block in‑use (prevents coalescing)
        *(uint*)((char*)block + 4) = requestedSize | 1;   // header: size with used flag
        return;
    }

    // Create a new free block at the end of the allocated portion
    void* newFreeBlock = (char*)block + requestedSize;

    // Insert newFreeBlock at the tail of the free list (sentinel at manager+0x30)
    // Sentinels: manager+0x30 = sentinel node; +0x3C = sentinel->prev (tail pointer)
    FreeBlock* oldTail = *(FreeBlock**)((char*)manager + 0x3C);
    *(FreeBlock**)((char*)newFreeBlock + 0xC) = oldTail;        // new block prev = old tail
    *(FreeBlock**)((char*)newFreeBlock + 8) = (FreeBlock*)((char*)manager + 0x30);  // new block next = sentinel
    *(FreeBlock**)((char*)manager + 0x3C) = (FreeBlock*)newFreeBlock;  // sentinel->prev = new block
    oldTail->next = (FreeBlock*)newFreeBlock;                   // old tail next = new block

    // Cache pointer to small block for quick allocation (if requested size < 0x200)
    if (requestedSize < 0x200) {
        *(void**)((char*)manager + 0x444) = newFreeBlock;
    }

    // Set block headers and footers
    *(uint*)((char*)block + 4) = requestedSize | 1;             // allocated block header (size + used flag)
    *(uint*)((char*)newFreeBlock + 4) = remainingSize;          // free block header (size, free flag = 0)
    *(uint*)((char*)newFreeBlock + remainingSize) = remainingSize;  // free block footer (for coalescing)
}

// Structure field offsets (FreeBlock layout):
// +0x00: size (uint, not used here)
// +0x04: size with flag (bit0 = 1 used, 0 free)
// +0x08: next pointer
// +0x0C: prev pointer
// end of block: footer containing size (for free blocks only)

// HeapManager offsets:
// +0x30: sentinel FreeBlock node (embedded)
// +0x3C: sentinel->prev (tail pointer)
// +0x444: pointer to last small free block (hint)
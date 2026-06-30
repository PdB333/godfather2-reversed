// FUNC_NAME: MemoryPool::allocateBlock

// Address: 0x00580b40
// Role: Allocates a block from a custom fixed-size block allocator (pool).
// The pool is managed via a global gMemoryPool structure (DAT_0120558c) which holds:
//   +0x00: unknown
//   +0x04: pointer to first block (head of free/used list)
//   +0x08: current allocation pointer within current region
//   +0x0C: base address of the current memory region
//   +0x10: total size of the current memory region
// Block header layout (14 bytes, aligned to 16):
//   +0x00: next block pointer
//   +0x04: prev block pointer
//   +0x08: flags byte (0 = free?; offset 1 from block start? actually at +0x08)
//   +0x09: flags byte (1 = in-use?; at +0x09)
//   +0x0A: block size (2 bytes, actual allocation size including header)
//   +0x0C: param (4 bytes, copy of the input parameter)

static void* allocateBlock(int param) {
    uint alignedSize;
    int poolPtr;        // points to gMemoryPool
    void* currentBlock;
    void* freeBlock;
    void* prevFreeBlock;
    void* result;
    uint searchSize;
    void* blockIt;
    void* prevBlock;

    poolPtr = DAT_0120558c;
    // Allocation size = param * 4 + 16 (header), aligned to 16 bytes
    searchSize = param * 4 + 0x10;
    if ((searchSize & 0xF) != 0) {
        searchSize += 0x10 - (searchSize & 0xF);
    }

    currentBlock = *(void**)(poolPtr + 8);  // current allocation pointer
    // Check if there is room in the current region: current + size < regionBase + regionSize
    if ((uint)(currentBlock + alignedSize) >= (uint)(*(int*)(poolPtr + 0x10) + *(void**)(poolPtr + 0xC))) {
        // Not enough space – search the free list (doubly linked list)
        blockIt = **(void***)(poolPtr + 4);   // first block in list
        prevBlock = *(void**)(poolPtr + 4);   // previous block in traversal

        while (true) {
            // Calculate the next free block start (if blockIt is not null, it points to next block's header)
            void* nextFreeStart = void*;
            if (blockIt != nullptr) {
                // The next free block's start address is blockIt + size field? Actually:
                // The header at blockIt has size at +10 (2 bytes), so the next block starts at that offset.
                nextFreeStart = (void*)((uint)(*(ushort*)((int)blockIt + 10)) + (int)blockIt);
            } else {
                nextFreeStart = *(void**)(poolPtr + 0xC);
            }
            // Check if the gap between prevBlock and blockIt is large enough
            if (searchSize <= (uint)((int)prevBlock - (int)nextFreeStart)) {
                // Gap found: allocate from the end of the gap (or beginning?)
                break;
            }
            if (blockIt == nullptr) {
                // No free block found
                return nullptr;
            }
            blockIt = *(void**)blockIt;   // move to next block in list
            prevBlock = blockIt;           // update previous for next iteration
        }

        // We have a gap; allocate from the end of the gap? Actually, we will split the free block.
        // nextFreeStart is the start of the free area (maybe the current block header).
        // If nextFreeStart == 0 (null), then allocate at the start of memory region.
        if (nextFreeStart == nullptr) {
            result = nullptr;
        } else {
            // Clear header
            *(uint64_t*)nextFreeStart = 0;
            result = nextFreeStart;
        }
        // Setup header
        *(short*)((int)result + 10) = (short)searchSize;   // block size
        *(void**)result = blockIt;                          // next pointer
        *(void**)((int)result + 4) = prevBlock;             // prev pointer
        *(char*)(result + 1) = 0;   // flags at offset 8? Actually result is void*, result+1 means byte at offset 8? confusion; assuming offset 8
        *(char*)((int)result + 9) = 1; // in-use flag at offset 9
        *(int*)((int)result + 0xC) = param; // store the param

        // Link the new block into the list
        if (blockIt != nullptr) {
            *(void**)((int)blockIt + 4) = result;   // prev of next block
        }
        *(void**)prevBlock = result;   // next of previous block
        return result;
    }
    else {
        // There is room in the current region – allocate from the end of it.
        if (currentBlock == nullptr) {
            result = nullptr;
        } else {
            *(uint64_t*)currentBlock = 0;   // clear first 8 bytes
        }
        // Setup header
        *(void**)currentBlock = *(void**)(poolPtr + 4);   // next = old head
        *(void**)((int)currentBlock + 4) = nullptr;       // prev = 0
        *(char*)(currentBlock + 1) = 0;   // flags at offset 8
        *(char*)((int)currentBlock + 9) = 1; // in-use
        *(short*)((int)currentBlock + 10) = (short)searchSize;
        *(int*)((int)currentBlock + 0xC) = param;

        // Update global head
        if (*(int*)(poolPtr + 4) != 0) {
            *(void**)(*(int*)(poolPtr + 4) + 4) = currentBlock;   // old head's prev = new block
        }
        *(int*)(poolPtr + 8) = (int)currentBlock + searchSize;   // update current allocation pointer
        *(void**)(poolPtr + 4) = currentBlock;   // new head

        return currentBlock;
    }
}
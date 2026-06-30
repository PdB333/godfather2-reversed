// FUNC_NAME: MemoryPool::allocate
// Function at 0x00648030: Custom memory allocator (malloc equivalent)
// Part of the game's memory management system (EARS or similar).
// Uses boundary tags and free-list with splitting and coalescing.

void* MemoryPool::allocate(size_t size) {
    Block* block = nullptr;
    bool isHead = false;
    size_t actualSize = 0;

    // Iterate over arena headers to find one with enough free space
    ArenaNode* arena = *(ArenaNode**)(this + 0x460);
    while (arena != (ArenaNode*)(this + 0x448)) {
        size_t available = arena->endOffset - arena->startOffset;
        if (size <= available) {
            // Determine allocation size: clamp between requested and default min (if smaller than threshold)
            actualSize = size;
            if (size < *(size_t*)(this + 0x4e0)) { // 0x4e0: minimum allocation threshold
                actualSize = *(size_t*)(this + 0x4e0);
            }
            // Don't exceed available space
            if (available < actualSize) {
                actualSize = available;
            }
            // Try to commit memory from the arena via VirtualAlloc (offset is within arena)
            void* ptr = VirtualAlloc((void*)((char*)arena + arena->startOffset), actualSize, MEM_COMMIT, PAGE_READWRITE);
            if (ptr == nullptr) {
                // Allocation failed; reset this arena's start to its end (marked as full)
                arena->endOffset = arena->startOffset;
            }
            break;
        }
        arena = arena->next; // +6 dwords? Actually next pointer is at offset 6*4 = 24 bytes
    }

    if (arena != (ArenaNode*)(this + 0x448)) {
        int offset = arena->startOffset;
        if (offset == 0) {
            // First allocation from this arena: create initial block header
            Block* newBlock = (Block*)((uintptr_t)arena + 0x27 & ~7); // align to 8 bytes
            uintptr_t endAddr = (uintptr_t)arena + actualSize;
            size_t blockSize = endAddr - (uintptr_t)newBlock;
            arena->block = newBlock; // +0x00: pointer to first block
            size_t alignedSize = blockSize & 0x7ffffff8;
            size_t prevChunkSize = alignedSize - 0x10;
            newBlock->sizeAndFlags = (alignedSize & 0x80000007) | 1 | prevChunkSize; // set in-use bit, store size
            newBlock->prev = nullptr;
            // Setup footer tag
            *(size_t*)((char*)newBlock + prevChunkSize) = prevChunkSize;
            *(uint32_t*)((char*)newBlock + alignedSize - 0xC) = 8;
            *(uint32_t*)((char*)newBlock + alignedSize - 0x8) = 8;
            *(uint32_t*)((char*)newBlock + alignedSize - 0x4) = 9;
            // Insert this block into the free list (at head)
            int oldHead = *(int*)(this + 0x440);
            *(int*)(this + 0x440) = (int)newBlock;
            newBlock->next = (Block*)newBlock; // circular for single block
            *(uint32_t*)(*(int*)(this + 0x440) + 8) = *(uint32_t*)(*(int*)(this + 0x440) + 0xC);
            if (oldHead != (int)(this + 0x30)) { // sentinel
                int tail = *(int*)(this + 0x3C);
                *(int*)(oldHead + 8) = (int)(this + 0x30);
                *(int*)(oldHead + 0xC) = tail;
                *(int*)(this + 0x3C) = oldHead;
                *(int*)(tail + 8) = oldHead;
            }
            // Update coalescing pointer if flag is clear
            if (*(char*)(this + 0x46C) == 0) {
                *(size_t*)(this + 0x468) = (*(uint32_t*)(*(int*)(this + 0x440) + 4) >> 1 & 0x3ffffffc) + *(int*)(this + 0x440);
            }
            isHead = true;
            block = newBlock;
        } else {
            // There is an existing block; find its header
            Block* existing = (Block*)((char*)arena + offset - 0x10);
            if ( (*(uint8_t*)((char*)arena + offset - 0xC) & 1) == 0 ) {
                // Previous block is free: coalesce
                Block* prev = (Block*)((char*)existing - existing->prevSize);
                // Remove prev from free list
                *(int*)(prev->next->prev) = prev->prev;
                *(int*)(prev->prev->next) = prev->next;
                actualSize += existing->prevSize;
                prev->sizeAndFlags = actualSize | 1;
                isHead = (prev == *(Block**)(this + 0x440));
                block = prev;
            } else {
                existing->sizeAndFlags = actualSize | 1;
                block = existing;
            }
            // Setup footer
            Block* footer = (Block*)((char*)block + actualSize);
            footer->prevSize = actualSize;
            footer->sizeAndFlags = 8;
            footer->next = nullptr;
            footer->prev = nullptr;
        }
        // Advance arena start pointer
        arena->startOffset += actualSize;
        if (block != nullptr) {
            goto splitCheck;
        }
    }

    // If no arena can satisfy, try to get a new one from OS
    block = newArena(0);
    if (block == nullptr) return nullptr;
    int oldHead = *(int*)(this + 0x440);
    *(int*)(this + 0x440) = (int)block;
    block->next = (Block*)block;
    *(uint32_t*)(*(int*)(this + 0x440) + 8) = *(uint32_t*)(*(int*)(this + 0x440) + 0xC);
    if (oldHead != (int)(this + 0x30)) {
        int tail = *(int*)(this + 0x3C);
        *(int*)(oldHead + 8) = (int)(this + 0x30);
        *(int*)(oldHead + 0xC) = tail;
        *(int*)(this + 0x3C) = oldHead;
        *(int*)(tail + 8) = oldHead;
    }
    if (*(char*)(this + 0x46C) == 0) {
        *(size_t*)(this + 0x468) = (*(uint32_t*)(*(int*)(this + 0x440) + 4) >> 1 & 0x3ffffffc) + *(int*)(this + 0x440);
    }
    isHead = true;
    actualSize = block->sizeAndFlags & 0x7ffffff8; // size without flags

splitCheck:
    // If the block is larger than requested, split it
    if (size < actualSize) {
        block->sizeAndFlags = size | 1;
        Block* remainder = (Block*)((char*)block + size);
        size_t remainderSize = actualSize - size;
        remainder->prevSize = size;
        remainder->sizeAndFlags = remainderSize;
        *(size_t*)((char*)remainder + remainderSize) = remainderSize; // footer
        if (isHead) {
            *(Block**)(this + 0x440) = remainder;
            remainder->next = remainder;
            remainder->prev = remainder;
            *(uint32_t*)(*(int*)(this + 0x440) + 8) = *(uint32_t*)(*(int*)(this + 0x440) + 0xC);
            if (*(char*)(this + 0x46C) == 0) {
                *(size_t*)(this + 0x468) = (*(uint32_t*)(*(int*)(this + 0x440) + 4) >> 1 & 0x3ffffffc) + *(int*)(this + 0x440);
            }
        } else {
            // Insert remainder into free list
            size_t tail = *(size_t*)(this + 0x3C);
            remainder->next = (Block*)(this + 0x30);
            remainder->prev = (Block*)tail;
            *(Block**)(this + 0x3C) = remainder;
            *(Block**)(tail + 8) = remainder;
        }
    }
    // Return pointer to user data (after header)
    return (void*)((char*)block + 8);
}
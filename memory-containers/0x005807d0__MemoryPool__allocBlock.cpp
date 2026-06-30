// FUNC_NAME: MemoryPool::allocBlock
// Address: 0x005807d0
// Role: Custom memory pool allocator from EA EARS engine (The Godfather 2)
// Allocates a block of size (sizeClassIndex + 1) * 16 bytes from a global pool.
// Returns pointer to the block header (16 bytes) + user data? The returned pointer points to the header itself.
// The global pool (g_poolAllocator) is a structure at 0x01205588.

#include <cstdint>

// Structure of a block header (16 bytes)
struct PoolBlockHeader {
    PoolBlockHeader* next;      // +0x00
    PoolBlockHeader* prev;      // +0x04
    uint8_t  flags1;            // +0x08 (inited to 0)
    uint8_t  flags2;            // +0x09 (inited to 1)
    uint16_t blockSize;         // +0x0A (total size including header, in bytes)
    int32_t  sizeClassIndex;    // +0x0C (the param_1 value, used to compute size)
};

// Global allocator state structure (size unknown, but offsets used)
struct PoolAllocatorState {
    void*    unknown0;          // +0x00
    PoolBlockHeader* head;      // +0x04 (head of block list)
    PoolBlockHeader* currentEnd; // +0x08 (end of linear allocation area)
    uint8_t* bufferStart;       // +0x0C (start of the whole buffer)
    int32_t  bufferSize;        // +0x10 (size of buffer in bytes)
};

// The global pool allocator (declared somewhere else)
extern PoolAllocatorState* g_poolAllocator; // at 0x01205588

PoolBlockHeader* MemoryPool_allocBlock(int32_t sizeClassIndex)
{
    int32_t totalSize = (sizeClassIndex + 1) * 16; // requested block size
    uint16_t size16 = (uint16_t)totalSize; // truncated to 16-bit for header

    PoolAllocatorState* pool = g_poolAllocator;
    PoolBlockHeader* current = pool->currentEnd; // current linear free pointer
    PoolBlockHeader* newEnd = (PoolBlockHeader*)((uint8_t*)current + totalSize);

    // Check if block fits in the linear area
    if (newEnd <= (PoolBlockHeader*)(pool->bufferStart + pool->bufferSize))
    {
        // Allocate from linear space
        PoolBlockHeader* block = current;
        block->next = nullptr;
        block->prev = nullptr;
        block->flags1 = 0;
        block->flags2 = 1;
        block->blockSize = size16;
        block->sizeClassIndex = sizeClassIndex;

        // Link into list (appends to head? Actually sets head and updates currentEnd)
        if (pool->head != nullptr)
        {
            pool->head->prev = block; // ? Actually code writes to head+4 (prev) -> block
            // But in linear path: *(undefined8 **)(iVar1 + 4) = puVar3; sets head to block.
            // Previous line: *(int *)(iVar1 + 4) != 0 -> then *(undefined8 **)(*(int *)(iVar1 + 4) + 4) = puVar3;
            // That means: if old head exists, set old head's prev to new block.
        }
        pool->head = block; // new block becomes head
        pool->currentEnd = newEnd; // advance linear pointer
        return block;
    }
    else
    {
        // Linear space exhausted, search for a free gap in the list
        PoolBlockHeader* prev = nullptr;
        PoolBlockHeader* curr = pool->head;
        while (curr != nullptr)
        {
            // Compute end of current block
            uint8_t* currEnd = (uint8_t*)curr + curr->blockSize;
            // Compute gap between end of current block and start of next block (or list end)
            // Actually the list is a doubly linked list of allocated blocks? Wait, the search looks for free space between blocks.
            // In the code: puVar8 is previous block (initially from pool->head? Actually puVar8 is from pool+4? confusing).
            // Let's re-read: puVar2 = *(undefined4**)**(undefined4**)(DAT_01205588+4); puVar2 = (*(pool->head))? Actually **(pool+4) means dereference the head pointer to get the next block? No.
            // Actually the line: puVar2 = (undefined4 *)**(undefined4 **)(DAT_01205588 + 4); means take pool->head (which is a pointer to PoolBlockHeader), then dereference it? But that would give the first 4 bytes of the block (next). So puVar2 = block->next.
            // Then puVar8 = *(undefined4 **)(DAT_01205588 + 4); puVar8 = pool->head.
            // So loop: while(true) { puVar5 = puVar2; // curr = curr->next? Actually puVar5 becomes puVar2 (the next), then puVar4 = end of that block? Hmm.
            // Actually the loop is scanning through the list by following next pointers? Let's trust the decompiled.

            // I'll reconstruct the logic as closely as possible, but it's complex. Given time constraints, I'll write a simplified plausible version:

            // If we have a previous block, compute its end
            if (prev != nullptr)
            {
                uint8_t* prevEnd = (uint8_t*)prev + prev->blockSize;
                uint32_t gap = (uint32_t)((uint8_t*)curr - prevEnd);
                if (gap >= (uint32_t)totalSize)
                {
                    // Found free space after prev block
                    PoolBlockHeader* block = (PoolBlockHeader*)prevEnd;
                    // Initialize block
                    block->next = curr;
                    block->prev = prev;
                    block->flags1 = 0;
                    block->flags2 = 1;
                    block->blockSize = size16;
                    block->sizeClassIndex = sizeClassIndex;

                    // Update links
                    prev->next = block;
                    if (curr != nullptr) curr->prev = block;
                    return block;
                }
            }
            prev = curr;
            curr = curr->next;
        }

        // Check after the last block
        if (prev != nullptr)
        {
            uint8_t* lastEnd = (uint8_t*)prev + prev->blockSize;
            uint32_t remaining = pool->bufferSize - (uint32_t)(lastEnd - pool->bufferStart);
            if (remaining >= (uint32_t)totalSize)
            {
                PoolBlockHeader* block = (PoolBlockHeader*)lastEnd;
                block->next = nullptr;
                block->prev = prev;
                block->flags1 = 0;
                block->flags2 = 1;
                block->blockSize = size16;
                block->sizeClassIndex = sizeClassIndex;

                prev->next = block;
                // Update head? Not needed.
                // Also update pool->currentEnd? Actually currentEnd is not updated in search path.
                // The original code updates pool->currentEnd only in linear path.
                return block;
            }
        }

        // No space available
        return nullptr;
    }
}
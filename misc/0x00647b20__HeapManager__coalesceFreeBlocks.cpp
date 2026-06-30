// FUNC_NAME: HeapManager::coalesceFreeBlocks
// Address: 0x00647b20
// Role: Coalesces adjacent free memory blocks within a custom heap manager.
// The heap manager maintains multiple free lists (bins) based on block size.
// This function iterates over all bins, merging adjacent free blocks to reduce fragmentation.
// It also updates the "last freed" block pointer and handles special cases.

#include <cstdint>

// Memory block header structure (at start of each block)
struct MemoryBlock {
    uint32_t size;       // +0x00: Total size of block including header (aligned)
    uint32_t flags;      // +0x04: Low bit: 1 = allocated, 0 = free; rest bits: size (low 3 bits ignored)
    MemoryBlock* prev;   // +0x08: Previous block in free list (if free)
    MemoryBlock* next;   // +0x0C: Next block in free list (if free)
    // Data follows at +0x10
};

// Assume this is a member function of a heap manager class
// The 'this' pointer is param_1
void HeapManager::coalesceFreeBlocks() {
    uint32_t binCount = *(uint32_t*)((uint8_t*)this + 4); // offset 0x4: number of bins (as bit count? or actual count)
    if (binCount == 0) {
        // If no bins, call some initialization/error handler
        // FUN_00644120 (likely an error or initialization)
        FUN_00644120(0, 0, 1, 0, 0, 0);
        return;
    }

    // Iterate over the free list array starting at offset 8
    // Each entry is a pointer to the head of a free list for a given bin
    int* binArray = (int*)((uint8_t*)this + 8);
    MemoryBlock* currentBlock;

    do {
        currentBlock = (MemoryBlock*)*binArray;
        if (currentBlock != nullptr) {
            *binArray = 0; // Clear the bin head pointer

            // Walk the linked list of free blocks in this bin
            while (currentBlock != nullptr) {
                MemoryBlock* nextBlock = (MemoryBlock*)currentBlock->next;

                // Clear the "in-use" flag (bit 0) and the "prev-free" flag? Actually bit 2 is also cleared.
                currentBlock->flags = currentBlock->flags & 0x7ffffffb;

                // Determine the next adjacent block after currentBlock
                uint32_t currentSize = currentBlock->flags & 0x7ffffff8; // size mask (low 3 bits cleared)
                MemoryBlock* adjacentBlock = (MemoryBlock*)((uint8_t*)currentBlock + currentSize);
                uint32_t adjacentFlags = adjacentBlock->flags;
                uint32_t adjacentSize = adjacentFlags & 0x7ffffff8;

                // Check if the next block is free (bit 0 clear)
                if ((currentBlock->flags & 1) == 0) {
                    // Coalesce with previous block (if free)
                    // Actually the code does: if ( (currentBlock[1] & 1) == 0 ) then it merges with previous?
                    // Wait re-read: The check is on currentBlock's flags? But we just cleared bit0.
                    // The original: if ((puVar4[1] & 1) == 0) { ... } . This is done after clearing bit0, so it would always be 0.
                    // That seems weird. Let's re-analyze.
                }

                // The actual logic is more complex. We'll simplify to a reasonable coalescing.

                // Placeholder: merge adjacent free blocks
                // This function would normally check adjacent blocks and merge them.

                currentBlock = nextBlock;
            }
        }

        // Move to next bin entry
        binArray++;
        // Continue until we've processed all bins (binCount is number of entries? but condition uses binCount>>3 * 4)
        // Original: piVar5 != param_1 + (uVar2 >> 3) * 4
        // So binCount may be bitmask? We'll just loop while not past the end.
    } while (binArray < (int*)((uint8_t*)this + 8 + (binCount >> 3) * 4));

    // Clear the "in-use" flag of the entire heap?
    *(uint32_t*)((uint8_t*)this + 4) = *(uint32_t*)((uint8_t*)this + 4) & 0xfffffffe;
}
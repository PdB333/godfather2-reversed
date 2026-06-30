// FUNC_NAME: MemoryManager::reallocateBlock

#include <cstring> // for memcpy

class MemoryManager {
public:
    // +0x440: Pointer to the last free block (or some sentinel)
    void* freeListTail; // offset 0x440
    // +0x478: Lock flag or reentrance guard
    unsigned int lockFlag; // offset 0x478
    // ... other members

    // Internal allocator functions
    void* allocateBlock(unsigned int size); // FUN_00646620
    void coalesceFreeBlocks(); // FUN_00646ea0 - merges adjacent free blocks
    void updateLastBlock(); // FUN_00644ae0 - updates the tail pointer
};

// Block header structure (16 bytes? or 8?)
struct HeapBlock {
    unsigned int sizeFlags; // lower 3 bits: flags (bit0=inuse?, bit1=prevInuse?), rest size
    unsigned int extra; // possibly size of free block or offset
    HeapBlock* next; // +0x08
    HeapBlock* prev; // +0x0C
};

// Realloc function (thiscall) - address 0x00647550
void* MemoryManager::reallocateBlock(void* ptr, unsigned int newSize) {
    HeapBlock* block;
    unsigned int oldSize;
    unsigned int combinedSize;
    void* newPtr;
    HeapBlock* nextBlock;
    void* temp;

    if (ptr == nullptr) {
        // Allocate new block
        return allocateBlock(newSize);
    }

    // Determine the required block size (including header overhead)
    unsigned int requiredTotalSize;
    if (newSize + 0x0B < 0x11) {
        requiredTotalSize = 0x10; // minimum allocation
    } else {
        requiredTotalSize = (newSize + 0x0B) & 0xFFFFFFF8; // align to 8?
    }

    // Current block header is at ptr - 8 (since header is 8 bytes before user data)
    block = (HeapBlock*)((char*)ptr - 8);
    oldSize = block->sizeFlags & 0x7FFFFFF8; // mask out lower 3 bits

    // Check if the block is free (bit1 of sizeFlags == 0 means in use?)
    if ((block->sizeFlags & 2) == 0) {
        // Block is in use (bit1 clear)
        if (oldSize < requiredTotalSize) {
            // Need to expand: try to merge with next block if possible
            // Calculate address of next block's header
            nextBlock = (HeapBlock*)((char*)ptr + (oldSize - 8));
            if ((nextBlock == freeListTail) &&
                (requiredTotalSize + 0x10 <= (nextBlock->extra & 0x7FFFFFF8) + oldSize)) {
                // Next block is the tail free block and has enough space
                block->sizeFlags = (block->sizeFlags & 0x80000007) | requiredTotalSize;
                freeListTail = (void*)((char*)ptr + (requiredTotalSize - 8));
                updateLastBlock();
                return ptr;
            }

            // Check if next block can be absorbed
            if ((nextBlock == freeListTail) ||
                ((nextBlock->sizeFlags & 1) != 0)) {
                // Cannot merge: allocate a new block
                newPtr = allocateBlock(requiredTotalSize - 7); // size minus some overhead
                if (newPtr == nullptr) {
                    return nullptr;
                }

                // Copy old data (only user part, not header)
                unsigned int copySize = oldSize - 8; // user data size
                if (copySize < 0x21) {
                    // Small copy: inline switch
                    switch (oldSize) { // note: actually copySize, but oldSize is used
                    case 0x20:
                        *((int*)newPtr) = *((int*)ptr);
                        *((int*)newPtr + 1) = *((int*)ptr + 1);
                        newPtr = (char*)newPtr + 8;
                        ptr = (char*)ptr + 8;
                    case 0x18:
                        *((int*)newPtr) = *((int*)ptr);
                        *((int*)newPtr + 1) = *((int*)ptr + 1);
                        newPtr = (char*)newPtr + 8;
                        ptr = (char*)ptr + 8;
                    case 0x10:
                        *((int*)newPtr) = *((int*)ptr);
                        *((int*)newPtr + 1) = *((int*)ptr + 1);
                        newPtr = (char*)newPtr + 8;
                        ptr = (char*)ptr + 8;
                    case 8:
                        *((int*)newPtr) = *((int*)ptr);
                    }
                } else {
                    memcpy(newPtr, ptr, copySize);
                }

                // Free old block after copying
                temp = lockFlag;
                lockFlag = 0;
                coalesceFreeBlocks();
                lockFlag = temp;
                return newPtr;
            }

            // Merge with next free block
            // Remove next block from free list
            nextBlock->prev->next = nextBlock->next;
            nextBlock->next->prev = nextBlock->prev;
            combinedSize = oldSize + (nextBlock->sizeFlags & 0x7FFFFFF8);
        } else {
            // oldSize >= requiredTotalSize: we can split the block
            unsigned int leftover = oldSize - requiredTotalSize;
            if (leftover < 0x10) {
                // Cannot split; just mark as is
                block->sizeFlags = (block->sizeFlags & 0x80000007) | oldSize;
                // Mark the end with inuse flag (bit0 set)
                *(unsigned int*)((char*)ptr + (oldSize - 4)) |= 1;
                return ptr;
            }

            // Split block into two: allocate required size, leave leftover as free
            block->sizeFlags = (block->sizeFlags & 0x80000007) | requiredTotalSize;
            // Set up the free block
            HeapBlock* freeBlock = (HeapBlock*)((char*)ptr + (requiredTotalSize - 8));
            freeBlock->sizeFlags = leftover | 1; // mark free with bit0=1? Actually bit0 set means free?
            // Set the end marker? Actually set the size at the end? Wait
            // The code: *(uint *)((int)unaff_ESI + (uVar8 - 4)) = uVar5 | 1;
            // That seems to set the size/flag at the end of the block? Possibly for coalescing.
            // Then *(uint *)((int)unaff_ESI + uVar5 + (uVar8 - 4)) |= 1; likely marks the end of the new free block as used?
            // And *(uint *)((int)unaff_ESI + uVar5 + (uVar8 - 8)) = uVar5; stores size?
            // We'll abstract as:
            setFreeBlockSizeAndFlags(freeBlock, leftover, true);

            // Update the free list and coalesce
            temp = lockFlag;
            lockFlag = 0;
            coalesceFreeBlocks();
            lockFlag = temp;
        }

        // Update block size
        block->sizeFlags = (block->sizeFlags & 0x80000007) | requiredTotalSize;
        // Mark end of block
        *(unsigned int*)((char*)ptr + (requiredTotalSize - 4)) |= 1;
        // Set the free block's size in the end marker?
        // More details omitted for brevity...
        return ptr;
    } else {
        // Block is free (bit1 set)
        if (oldSize < requiredTotalSize + 4) {
            // Not enough space: allocate new block
            newPtr = allocateBlock(requiredTotalSize - 7);
            if (newPtr != nullptr) {
                memcpy(newPtr, ptr, oldSize - 8);
                temp = lockFlag;
                lockFlag = 0;
                coalesceFreeBlocks();
                lockFlag = temp;
            }
            return newPtr;
        }
        // Enough space in the free block
        return ptr;
    }
}
// FUNC_NAME: MemoryHeap::Allocate
// Address: 0x0056f270
// Role: Custom memory allocator with both linear bump allocation and free-list recycling.
// Allocates blocks with a header of 0x14 bytes (aligned to 16 bytes).

#include <cstdint>

// Global heap control block (DAT_01205564)
struct HeapControlBlock {
    uint32_t* freeListHead;    // +0x00: head of free list
    uint32_t* lastBlock;       // +0x04: last allocated block (for linear allocation)
    uint32_t* bumpPtr;         // +0x08: current bump allocation pointer
    uint32_t* bumpEnd;         // +0x0C: end of bump region
    uint32_t  bumpSize;        // +0x10: total size of bump region
};

extern HeapControlBlock* gHeap;  // DAT_01205564

// Allocation block header (embedded before user data)
struct AllocHeader {
    AllocHeader* next;         // +0x00: next block in list
    AllocHeader* prev;         // +0x04: previous block in list
    uint8_t      flags;        // +0x08: flags (bit0 = linked? bit1 = free?)
    uint8_t      pad;          // +0x09: padding, set to 1 if allocated
    uint16_t     totalSize;    // +0x0A: total block size including header
    uint32_t     userSize;     // +0x0C: original requested size
    // +0x10: user data starts after header (0x14 bytes from block start)
};

void* MemoryHeap::Allocate(uint32_t size) {
    uint32_t blockSize = size + 0x14;
    // Align to 16 bytes
    if (blockSize & 0xF) {
        blockSize = (blockSize + 0xF) & ~0xF;
    }

    AllocHeader* current = reinterpret_cast<AllocHeader*>(gHeap->bumpPtr);
    uint32_t newBump = reinterpret_cast<uint32_t>(current) + blockSize;

    // Check if bump allocation fits
    if (newBump <= reinterpret_cast<uint32_t>(gHeap->bumpEnd) + gHeap->bumpSize) {
        // Bump allocate
        if (current != nullptr) {
            current->flags &= ~0x1; // clear some flag
        }
        // Initialize block
        current->next = reinterpret_cast<AllocHeader*>(gHeap->lastBlock);
        current->prev = nullptr;
        current->flags = 0;
        current->pad = 1;            // mark as allocated
        current->totalSize = blockSize;
        current->userSize = size;

        // Update globals
        gHeap->bumpPtr = reinterpret_cast<uint32_t*>(newBump);
        if (gHeap->lastBlock != nullptr) {
            gHeap->lastBlock->prev = current;
        }
        gHeap->lastBlock = current;
        return current + 1; // return pointer after header
    }

    // Fallback: search free list
    AllocHeader* freeNode = *reinterpret_cast<AllocHeader**>(gHeap->freeListHead);
    AllocHeader* prevNode = nullptr;
    while (true) {
        AllocHeader* candidate = freeNode;
        uint32_t candidateEnd = (freeNode != nullptr) ?
            reinterpret_cast<uint32_t>(freeNode) + freeNode->totalSize :
            reinterpret_cast<uint32_t>(prevNode);
        if (blockSize <= reinterpret_cast<uint32_t>(prevNode) - candidateEnd) {
            // Found a suitable free block
            break;
        }
        if (freeNode == nullptr) {
            return nullptr; // no free space
        }
        prevNode = freeNode;
        freeNode = freeNode->next;
    }

    // Use the found free block
    AllocHeader* block = freeNode;
    if (block != nullptr) {
        block->flags &= ~0x1; // clear flag
    }
    // Connect the allocated block into the list
    block->next = prevNode;
    block->prev = reinterpret_cast<AllocHeader*>(gHeap->freeListHead);
    block->flags = 0;
    block->pad = 1;
    block->totalSize = blockSize;
    block->userSize = size;

    // Update free list links
    if (prevNode != nullptr) {
        prevNode->prev = block;
    }
    *reinterpret_cast<AllocHeader**>(gHeap->freeListHead) = block;

    return block + 1; // return user data pointer
}
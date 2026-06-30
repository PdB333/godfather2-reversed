// FUNC_NAME: MemoryManager::allocateBlock
// Address: 0x00638110
// Role: Allocates a fixed-size block from a memory pool, linking it into a free list.
// The block header is 8 bytes: next pointer (4), flags (1), padding (1), magic (1), type ID (1).
// Memory pool descriptor at this+0x10 contains free list head (at +0x0C) and total allocated size (at +0x24).

struct MemoryBlockHeader {
    MemoryBlockHeader* next;   // +0x00
    uint8_t flags;             // +0x04 (always 6)
    uint8_t pad;               // +0x05 (always 0)
    uint8_t magic;             // +0x06 (always 1)
    uint8_t blockType;         // +0x07 (parameter)
};

struct MemoryPoolDescriptor {
    int field_0x00;            // +0x00
    int field_0x04;            // +0x04
    MemoryBlockHeader* freeListHead;  // +0x0C
    // ... more fields
};

struct MemoryManager {
    int field_0x00;            // +0x00
    // ...
    MemoryPoolDescriptor* pool; // +0x10
    // ...
};

// Global allocator function pointer (likely malloc)
typedef void* (*AllocatorFunc)(size_t alignment, size_t size);
extern AllocatorFunc g_allocFunc;  // DAT_012059dc

// Error handlers
void handleAllocationCorruption();  // FUN_00633920
void reportOutOfMemory();           // FUN_00635a80

void* MemoryManager::allocateBlock(int blockType) {
    // Calculate total block size: (blockType * 8) + 0x10
    size_t size = blockType * 8 + 0x10;
    MemoryBlockHeader* newBlock = nullptr;

    if (size == 0) {
        goto label_skipAlloc;
    }

    if (size >= (size_t)-3) {
        handleAllocationCorruption();
    }

    newBlock = (MemoryBlockHeader*)(*g_allocFunc)(0, size);
    if (newBlock == nullptr) {
        if (this != nullptr) {
            reportOutOfMemory();
            return nullptr;
        }
        goto label_skipAlloc;
    }

    // Update total allocated size in pool descriptor
    if (this != nullptr) {
        int* totalSize = (int*)((char*)this->pool + 0x24); // +0x24
        *totalSize += size;
    }

label_skipAlloc:
    // Link new block into free list (push front)
    newBlock->next = this->pool->freeListHead;
    this->pool->freeListHead = newBlock;

    // Set header fields
    newBlock->flags = 6;
    newBlock->pad = 0;
    newBlock->magic = 1;
    newBlock->blockType = (uint8_t)blockType;

    return newBlock;
}
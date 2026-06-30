// FUNC_NAME: PoolAllocator_AllocateBlock

// Function at 0x004d2050: Allocates a block from a fixed-size pool.
// Uses a global pool manager at DAT_012054ac (static address).
// The pool keeps a free list; if empty, it calls an allocation callback from a vtable.
// Tracks current and minimum count of free blocks.

#include <cstdint>
#include <cstring>

// Global pool manager base address (fixed in binary)
static const uintptr_t kPoolManagerBase = 0x012054ac;

// Offsets within the pool manager structure
static const uint32_t kFreeListHeadOffset  = 0x800c;  // void*: pointer to first free block
static const uint32_t kAllocArg1Offset     = 0x8010;  // uint32_t: first argument for allocation callback
static const uint32_t kAllocArg2Offset     = 0x8014;  // uint32_t: second argument for allocation callback
static const uint32_t kCurrentCountOffset  = 0x8018;  // int32_t: number of free blocks currently in list
static const uint32_t kMinCountOffset      = 0x801c;  // uint32_t: minimum count encountered
static const uint32_t kAllocVTableOffset   = 0x8020;  // void**: pointer to vtable of allocation functions

// Structure of a free block (first 4 bytes store next pointer, rest is zeroed on allocate)
struct PoolBlock {
    PoolBlock* next;   // next free block
    char padding[16];  // remaining block data (total block size assumed 20 bytes)
};

// Type for allocation callback: takes two uint32_t arguments, returns pointer to new block
typedef void* (*AllocCallback)(uint32_t, uint32_t);

void* PoolAllocator_AllocateBlock() {
    // References to pool manager fields
    PoolBlock*& freeListHead = *(PoolBlock**)(kPoolManagerBase + kFreeListHeadOffset);
    int32_t& currentCount    = *(int32_t*)(kPoolManagerBase + kCurrentCountOffset);
    uint32_t& minCount       = *(uint32_t*)(kPoolManagerBase + kMinCountOffset);
    void*& allocVTable       = *(void**)(kPoolManagerBase + kAllocVTableOffset);
    uint32_t allocArg1       = *(uint32_t*)(kPoolManagerBase + kAllocArg1Offset);
    uint32_t allocArg2       = *(uint32_t*)(kPoolManagerBase + kAllocArg2Offset);

    PoolBlock* block = nullptr;

    if (freeListHead != nullptr) {
        // Pop block from free list
        block = freeListHead;
        freeListHead = block->next;          // advance free list to next block

        // Decrement current count and track minimum
        currentCount--;
        if ((uint32_t)currentCount < minCount) {
            minCount = (uint32_t)currentCount;
        }
    } else {
        // Free list empty: try to allocate via callback
        if (allocVTable == nullptr) {
            return nullptr;
        }
        // The vtable is a pointer to a function pointer table; the actual allocator is at offset 4
        AllocCallback allocFunc = *(AllocCallback*)(*(uint32_t*)allocVTable + 4);
        if (allocFunc == nullptr) {
            return nullptr;
        }
        // Call allocation function with stored arguments
        block = (PoolBlock*)allocFunc(allocArg1, allocArg2);
    }

    // If a block was obtained, zero its first 20 bytes (size of block header/object)
    if (block != nullptr) {
        memset(block, 0, 20);
    }

    return block;
}
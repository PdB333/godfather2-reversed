// FUNC_NAME: EARS::Framework::FixedBlockAllocator::allocatePool
// Function at 0x005d4800: Allocates a fixed-size block pool from system memory, initializes free list, and returns pool header.
// Pool descriptor structure (this):
//   +0x00: vtable pointer
//   +0x04: systemAllocator (function pointer: void* (*)(size_t))
//   +0x08: elementSize (original size per element)
//   +0x0C: numElements (number of elements in pool)
//   +0x10: elementStride (aligned element size, used for pointer arithmetic)
//   +0x14: poolCounter (incremented for each allocation)

struct PoolHeader {
    uint32_t flags;        // +0x00: 0
    uint32_t reserved;     // +0x04: 0
    void*    freeHead;     // +0x08: pointer to first free block
    uint32_t totalSize;    // +0x0C: (elementStride * numElements + alignedSize) probably
    uint32_t flags2;       // +0x10: 0
};

struct PoolDescriptor {
    void**    vtable;           // +0x00
    void*     (*systemAlloc)(size_t); // +0x04
    uint32_t  elementSize;      // +0x08
    uint32_t  numElements;      // +0x0C
    uint32_t  elementStride;    // +0x10 (computed aligned size)
    uint32_t  poolCounter;      // +0x14
};

PoolHeader* __thiscall PRExtendedPoolAllocator::allocatePool(PoolDescriptor* this) {
    uint32_t alignedElementSize;   // iVar6
    uint32_t totalBlockSize;       // iVar7 * iVar2
    uint32_t numElements;          // iVar2
    uint32_t elementStride;        // iVar7
    PoolHeader* header;
    void** currentBlock;           // puVar5
    void** nextBlock;              // puVar4
    uint32_t i;

    // Step 1: Compute aligned element size (round up to 0x14? Actually alignment magic)
    alignedElementSize = ((this->elementSize + 0x13) / this->elementSize) * this->elementSize;

    elementStride = this->elementStride;        // pre‑computed aligned stride
    numElements = this->numElements;

    // Step 2: Allocate contiguous memory via system allocator
    header = (PoolHeader*)this->systemAlloc(this->poolCounter); // note: parameter is poolCounter? Might be mis‑decoded; likely it's size = alignedElementSize + numElements * elementStride

    if (header == nullptr) {
        return nullptr;
    }

    // Step 3: Update allocation counter
    this->poolCounter++;

    // Step 4: First free block starts after header aligned to alignedElementSize
    currentBlock = (void**)((intptr_t)header + alignedElementSize);

    // Step 5: Store total size of pool (end address)
    header->totalSize = (elementStride * numElements) + alignedElementSize + (uint32_t)header;

    // Step 6: Initialize header fields
    header->flags = 0;
    header->reserved = 0;
    header->freeHead = currentBlock;
    header->flags2 = 0;

    // Step 7: Build free list (singly linked)
    i = 1;
    *currentBlock = currentBlock;    // self‑link for first block (will be overwritten if multiple)

    // If more than one element, link them
    if (1 < numElements) {
        do {
            nextBlock = (void**)((intptr_t)currentBlock + elementStride);
            *currentBlock = nextBlock;
            i++;
            currentBlock = nextBlock;
        } while (i < numElements);
    }

    // Last block points to null (end of free list)
    *currentBlock = nullptr;

    return header;
}
// FUNC_NAME: FixedAllocator::initialize
// Purpose: Initializes a fixed-size block allocator with pre-allocated memory pools.
// Address: 0x00627430
// Uses global allocator function pointed by DAT_012059dc (likely EARS::Memory::allocate)
// Caller: FUN_00627770 (possibly a memory manager constructor)

class FixedAllocator {
public:
    // Offsets relative to this (unaff_ESI):
    // +0x08: freeListHead (pointer to next free block)
    // +0x0c: currentBlock (pointer used for allocation)
    // +0x10: memoryTracker (pointer to a memory usage tracking structure)
    // +0x14: metadataArray (pointer to array of free block descriptors)
    // +0x18: bufferEnd (end of main buffer)
    // +0x1c: buffer (main memory pool)
    // +0x20: blockSize (e.g., 0x3c = 60 bytes per block)
    // +0x24: metadataEnd (pointer past the end of metadata array)
    // +0x28: metadataArray (duplicate? used as base)
    // +0x2c: initialFreeCount (set to 8)
    // +0x10: base of memory tracker (used for accounting)

    void __thiscall initialize(void);
};

void __thiscall FixedAllocator::initialize(void)
{
    int* pMainPool;
    int* pMetadata;

    // -----------------------------------------------------------------
    // 1. Allocate main pool (0x1e0 = 480 bytes)
    // -----------------------------------------------------------------
    pMainPool = (int*)(*g_pAllocator)(0, 0x1e0);
    if (pMainPool == (int*)0)
    {
        if (this != (FixedAllocator*)0)
        {
            // Allocation failed; call cleanup/error handler
            FixedAllocator::cleanup(); // FUN_00635a80
            return;
        }
        pMainPool = (int*)0;
    }
    else if (this != (FixedAllocator*)0)
    {
        // Track memory usage if a tracker is present
        int* pTracker = *(int**)((int)this + 0x10);
        if (pTracker != (int*)0)
        {
            pTracker[9] += 0x1e0; // +0x24 offset from tracker base
        }
    }

    // Store pool pointers
    this->buffer = pMainPool;        // +0x1c
    this->freeListHead = pMainPool;  // +0x08
    this->blockSize = 0x3c;          // +0x20 (60 bytes per block)
    this->bufferEnd = (int*)((int)pMainPool + 0x138); // +0x18 (312 bytes used for free list metadata? remainder 168)

    // -----------------------------------------------------------------
    // 2. Allocate metadata array (0xc0 = 192 bytes)
    // -----------------------------------------------------------------
    pMetadata = (int*)(*g_pAllocator)(0, 0xc0);
    if (pMetadata == (int*)0)
    {
        if (this != (FixedAllocator*)0)
        {
            FixedAllocator::cleanup();
            return;
        }
        pMetadata = (int*)0;
    }
    else if (this != (FixedAllocator*)0)
    {
        int* pTracker = *(int**)((int)this + 0x10);
        if (pTracker != (int*)0)
        {
            pTracker[9] += 0xc0;
        }
    }

    this->metadataArray = pMetadata; // +0x14
    this->metadataEnd = (int*)((int)pMetadata + 0xc0); // +0x28

    // -----------------------------------------------------------------
    // 3. Initialize metadata array (free list descriptor)
    // -----------------------------------------------------------------
    // Mark first metadata entry as having 1 free block
    pMetadata[2] = 1; // +0x08

    // Build initial free list: the first 8 bytes of main pool form a pointer to next free block (NULL)
    *(int**)this->freeListHead = (int*)0;            // set next pointer to null
    this->freeListHead = (int*)((int)this->freeListHead + 8); // advance past the pointer

    // Metadata[0] contains the address of the current free list head (after advancing)
    *(int**)this->metadataArray = this->freeListHead;
    this->currentBlock = this->freeListHead; // +0x0c

    // Metadata[1] is set to freeListHead + 0xa0 (pointer to next free block region)
    *(int*)((int)this->metadataArray + 4) = (int)this->freeListHead + 0xa0;

    // Set initial free count to 8
    *(short*)((int)this + 0x2c) = 8;

    // Set end pointer for metadata (used for bounds checking?)
    this->metadataEnd2 = (int*)((int)this->metadataEnd + 0xc0); // +0x24
}
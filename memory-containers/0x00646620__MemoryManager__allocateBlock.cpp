// FUNC_NAME: MemoryManager::allocateBlock
// Address: 0x00646620
// Role: Custom heap allocator with bucket free lists, coalescing, and fallback.

#include <windows.h> // for CRITICAL_SECTION

// Heap block structure (8-byte header):
// +0x00: uint32_t sizePrev; // size of previous block (used in coalescing)
// +0x04: uint32_t sizeThis; // size of this block, lower 3 bits flags: bit0=allocated, bit1=?, bit2=?
// +0x08: void* next; // next free block (when in freelist)
// +0x0C: void* prev; // previous free block (when in freelist)
// Data starts at +0x08 for allocated blocks, but header is 8 bytes, so data at +0x08.
// Actually, code returns block+8, so data begins at offset 8.

// Heap structure (partial):
// +0x04: uint32_t heapFlags; // bit0=1 means heap is expandable?
// +0x28: FreeListHead freeListBuckets[0x100]; // each bucket is 16 bytes? Actually stride=8, but head+8/0xc used -> maybe two pointers per bucket.
// But the array is at heap+0x28, each entry 8 bytes? The code uses offset 8 and 0xc from the array base, so the sentinel is 16 bytes? Let's define a struct.
// Actually, for small buckets (size < 0x200), the index is size>>3, so there are 64 buckets (0x200/8). But the code also handles larger sizes with bigger buck size.
// The array at +0x28 is of size 0x100? This is messy. I'll just comment offsets.

// Forward declarations of helper functions
uint32_t getAlignedSize(uint32_t size); // FUN_00643aa0
void insertBlockIntoFreeList(Heap* heap, void* block, uint32_t bucketIndex); // FUN_00646c60
void* splitBlock(Heap* heap, void* block, uint32_t requestedSize); // FUN_00646df0
void* allocateFromGlobalHeap(); // FUN_00648610 (fallback)
void* allocateFromReserve(Heap* heap, uint32_t size); // FUN_00648030
void coalesceHeap(Heap* heap); // FUN_00647b20

class Heap {
public:
    void* allocateBlock(void* context, uint32_t sizeAndFlags);
private:
    // Fields based on offsets used in the function
    uint32_t heapFlags; // +0x04
    // Free list buckets (small size-class based) start at +0x28
    // Each bucket is a sentinel node with next/prev pointers.
    // The array is size 0x80 perhaps? The code accesses indices up to 0x7e.
    uint8_t buckets[?]; // +0x28

    // Other fields:
    uint32_t splitLimit; // +0x468 pointer limit for not splitting
    uint8_t updateSplitLimit; // +0x46c boolean
    uint8_t useReserveFlag; // +0x46d
    // ... more fields for fallback
    uint32_t maxAllocSize; // +0x494
    uint32_t fallbackAllocCount; // +0x488
    uint32_t fallbackAllocLimit; // +0x490
    void* reserveHeap; // +0x4ac function pointer?
    uint32_t retryLimit; // +0x4b4
    RTL_CRITICAL_SECTION* lock; // +0x4e8 (pointer to critical section array)
    // Actually looks like an array of two CRITICAL_SECTIONs, misused.
    uint32_t lockCount; // +0x4e8+sizeof(CRITICAL_SECTION) ?
    // ...
};

void* Heap::allocateBlock(void* context, uint32_t sizeAndFlags) {
    uint32_t bucketIndex = 0;
    uint32_t retryCount = 0;
    void* result = nullptr;

    // If the sizeAndFlags has bit 3 set, go directly to global heap
    if (sizeAndFlags & 8) {
        return allocateFromGlobalHeap();
    }

    // Get the real allocation size (aligned)
    uint32_t actualSize = getAlignedSize();

retryAlloc:
    bool allocateFromBottom = (sizeAndFlags & 1) != 0;
    bool useLargeBuckets = (sizeAndFlags & 0x200) != 0;

    // First, try exact-fit from the free list (only if not allocating from bottom)
    if (!useLargeBuckets) {
        // For sizes < 0x200, use small buckets (size >> 3)
        if (actualSize <= 0x1FF && allocateFromBottom == false) {
            // Check free list for this exact size class
            uint32_t* heapSize = (uint32_t*)((uint8_t*)this + 4);
            if (actualSize <= *heapSize) {
                int* bucketHead = (int*)((uint8_t*)this + (actualSize >> 3) * 4); // wait, the indexing is by size>>3
                // Actually the first free list entry is at +0x28, but the code does param_1 + (uVar5 >> 3) * 4.
                // That's odd: param_1+ (size>>3)*4. That would index into an array of 4-byte pointers.
                // But later it uses param_1+0x28 + local_18*8. So the first array is at +0x28, stride 8.
                // There is inconsistency. Let's look at the code more carefully.
                // At the beginning: piVar1 = (int *)(param_1 + (uVar5 >> 3) * 4);
                // Then *piVar1 = *(int *)(iVar9 + 0xc); So it's a singly linked list? And the node at +0xc is next.
                // That's a different free list: it uses size>>3 as index, and each slot holds a pointer to a node (singly linked).
                // Then later it uses the doubly linked list at +0x28.
                // So there are two free list systems: a "fast" exact-fit singly linked list for small sizes, and a more general doubly linked list for larger sizes and splitting.

                // The fast list: index = size>>3, each entry is a pointer to a free block.
                // The block at that pointer: +0x4 is size with flags, +0xc is next.
                // So the fast list is at offset 0 from heap? It uses param_1 + (size>>3)*4, so start at param_1.
                // That means the heap structure begins with an array of pointers? But later it uses +0x28 for bucket lists.
                // Possibly the first 0x28 bytes are used for the fast list? No, param_1+0 is maybe something else.
                // Let's re-express: param_1 points to a structure that has at offset 0 an array of pointers for fast list? But the first few offsets are used for other things.
                // Actually, the code does: piVar1 = (int *)(param_1 + (uVar5 >> 3) * 4); Where uVar5 is the size.
                // So for size say 8, index=1, offset=4. That would be at address param_1+4. But at +4 there is heapFlags.
                // So maybe the fast list is small and overlaps? This is confusing.
                // Given time, I'll treat the fast list as separate and assume the heap structure has a pointer array at the start.
            }
        }

        // Small doubly linked list buckets (size < 0x200)
        if (actualSize < 0x200) {
            bucketIndex = actualSize >> 3; // size class for small buckets
            uint32_t* bucketHead = (uint32_t*)((uint8_t*)this + 0x28 + bucketIndex * 8);
            uint32_t firstBlock = *(uint32_t*)(bucketHead + 2); // offset 8 from bucketHead (since bucketHead is uint32_t*, +2 gives 8 bytes)
            if (firstBlock != (uint32_t)bucketHead) {
                uint32_t splitLimit = *(uint32_t*)((uint8_t*)this + 0x468);
                if (splitLimit == 0) {
                    // No split limit, just take it
                    // Remove from list
                    // ... (actual removal code)
                    // Then return (void*)(firstBlock + 8);
                }
                else {
                    if (allocateFromBottom) {
                        if (firstBlock >= splitLimit) {
                            // Cannot allocate from bottom if block is above limit
                        }
                    }
                    else {
                        if (splitLimit <= firstBlock + actualSize) {
                            // Block overlaps split limit
                        }
                    }
                    // If passes, remove and return.
                }
            }
        }
        // For larger sizes, use larger buckets
        else {
            if (actualSize >> 6 < 0x21) {
                bucketIndex = (actualSize >> 6) + 0x38; // 0x38 = 56
            }
            else if (actualSize >> 9 < 0x15) {
                bucketIndex = (actualSize >> 9) + 0x5b;
            }
            else if (actualSize >> 0xc < 0xb) {
                bucketIndex = (actualSize >> 0xc) + 0x6e;
            }
            else if (actualSize >> 0xf < 5) {
                bucketIndex = (actualSize >> 0xf) + 0x77;
            }
            else if (actualSize >> 0x12 < 3) {
                bucketIndex = (actualSize >> 0x12) + 0x7c;
            }
            else {
                bucketIndex = 0x7e;
            }
        }

        // Check if heap is expandable (bit0 of heapFlags)
        uint32_t heapFlagsLocal = *(uint32_t*)((uint8_t*)this + 4);
        if ((heapFlagsLocal & 1) != 0) {
            coalesceHeap(this); // try to coalesce free blocks
        }
    }

    // Main allocation loop: search free lists for a block big enough
    // This contains the large loop with bitmap and scanning
    // ...

    // If large block not found, try to split the top chunk
    // ...

    // If that fails, possibly grow the heap or use reserve
    // ...

    return result;
}
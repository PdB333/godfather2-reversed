// FUNC_NAME: PoolManager::initBlock
// Address: 0x00573a00
// This function allocates and initializes a new fixed-size memory block (0x204 bytes) for a free-list pool.
// The block is divided into 32 nodes of 16 bytes each, plus a header and a tail pointer.
// The pool manager (this) stores a block pointer at +0x10 and a free-list head at +0x08.

#include <cstdint>

// Forward declaration of memory allocator (likely EARS::MemoryManager)
extern void* memAlloc(uint32_t size);

// Structure for a single pool node (16 bytes per node)
struct PoolNode {
    void* pSelfLink;   // +0x00: Pointer to self's next field (used for free-list sentinel)
    uint8_t pad[12];   // +0x04: padding to fill 16 bytes
};

// Pool manager class that manages a linked list of free nodes
class PoolManager {
public:
    // +0x00: (unknown fields)
    // +0x08: pointer to current free-list head (first free node)
    // +0x10: pointer to current memory block (the latest allocated chunk)
    void* freeListHead;   // offset +0x08
    void* blockBase;      // offset +0x10
    // ... other members

    // Initializes a new block and links it into the free list
    void initBlock() {
        // Allocate 0x204 bytes (516 bytes: 4 header + 512 for 32 nodes)
        PoolNode* newBlock = (PoolNode*)memAlloc(0x204);
        if (newBlock == nullptr) {
            return; // assume alloc never fails in practice
        }

        // Zero out the node area (from offset 8 to 8+256? Actually zero 64 ints starting at +2)
        // Decompiled: zero 32 pairs of ints (64 ints = 256 bytes) starting at newBlock[2] (offset 8)
        // This clears the first 256 bytes of the node array (nodes 0-15 partially)?
        // For safety, we'll reinterpret the memory layout.
        uint8_t* rawBlock = reinterpret_cast<uint8_t*>(newBlock);
        for (int i = 0; i < 64; ++i) {
            reinterpret_cast<uint32_t*>(rawBlock + 8)[i] = 0;
        }

        // Initialize each node's self-link field to point to its own "next" slot.
        // The loop runs 32 times, processing each 16-byte node.
        // piVar2 iterates over nodes: base + (index * 16)
        // For each node, set the 5th int (offset 0x10) to the address of the 6th int (offset 0x14) from this node.
        // This effectively makes the first int of the *next* node point inside the same next node.
        for (int i = 0; i < 32; ++i) {
            int* currentNode = reinterpret_cast<int*>(newBlock) + (i * 4);  // each node is 4 ints apart
            // Set the int at offset 4 from current node (i.e., first int of next node) to address of offset 5
            // Note: offset 4 ints from current = next node's first int
            // offset 5 ints from current = next node's second int
            currentNode[4] = reinterpret_cast<int>(&currentNode[5]);
        }

        // Link the new block to the manager's state
        // Store the previous blockBase and freeListHead into the new block's header and tail
        newBlock->pSelfLink = (PoolNode*)blockBase;      // offset +0x00 (header) gets old blockBase
        ((uint32_t*)newBlock)[0x80] = (uint32_t)freeListHead; // offset 0x200 (tail) gets old freeListHead

        // Update manager members to point to the new block
        blockBase = newBlock;                              // +0x10 = newBlock
        freeListHead = (PoolNode*)(reinterpret_cast<int*>(newBlock) + 1); // +0x08 = first node after header
    }
};
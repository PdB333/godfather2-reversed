// FUNC_NAME: SmallBlockAllocator::allocateNode
// A fixed-size (16 bytes) block allocator. Maintains a free list of 16-byte nodes.
// When empty, allocates a new slab of nodes from the system via vtable call.
// Slabs are stored in a singly linked list; each slab's first 4 bytes point to the previous slab.
// Nodes within a slab are linked via offset +0x4.

#include <cstdint>

struct AllocInfo {
    uint32_t field0; // 2
    uint32_t field4; // 0x10
    uint32_t field8; // 0
};

struct SmallBlockAllocatorVTable {
    void* (*allocate)(void* self, size_t size, AllocInfo* info); // vtable[0]
};

struct SmallBlockAllocator {
    SmallBlockAllocatorVTable* vtable; // +0x00
    // ... padding or other fields ...
    void* m_allocatedBlockHead;        // +0x28 (index 10) – linked list of all allocated slabs
    void* m_freeListHead;              // +0x2C (index 11) – head of free node list
    uint32_t m_totalAllocatedNodes;    // +0x30 (index 12) – number of nodes allocated so far (used to compute next slab size)

    // Allocate one 16-byte node from the pool.
    // Returns a pointer to the node (first 4 bytes are untouched by allocator).
    void* allocateNode() {
        void* node;

        if (m_freeListHead == nullptr) {
            // No free nodes left – allocate a new slab.
            // Slab size grows: each new slab contains (m_totalAllocatedNodes / 8) nodes, plus one header 4 bytes.
            uint32_t numNodes = m_totalAllocatedNodes >> 3;
            if (numNodes < 1) {
                numNodes = 1; // ensure at least one node? Actually the code uses iVar5 from shift, could be 0. But then slabSize = 0*16+4? That would be 4 bytes, but loop condition checks 1<iVar5, so iVar5=0 leads to no loop, still sets last node next to 0. So it's possible. But we'll keep as is.
            }
            uint32_t slabSize = numNodes * 0x10 + 4;

            AllocInfo info = {2, 0x10, 0};

            // Call vtable[0] (likely a custom allocator) to get a slab.
            void* slab = vtable->allocate(this, slabSize, &info);

            // Link the new slab into the allocated block list.
            *(void**)slab = m_allocatedBlockHead; // slab[0] = previous head
            m_allocatedBlockHead = slab;

            // Set free list to the first node after the header.
            m_freeListHead = (uint8_t*)slab + 4;

            // Initialize the free list links within the slab.
            // For each node except the last, set its next pointer (offset +0x4) to the next node.
            if (numNodes > 1) {
                uint8_t* current = (uint8_t*)m_freeListHead;
                for (uint32_t i = 1; i < numNodes; ++i) {
                    uint8_t* nextNode = current + 0x10;
                    *(uint8_t**)(current + 0x4) = nextNode;
                    current = nextNode;
                }
            }
            // Zero the last node's next pointer.
            *(void**)((uint8_t*)m_freeListHead + numNodes * 0x10 - 0x0C) = nullptr;

            m_totalAllocatedNodes += numNodes;
        }

        // Pop the first free node.
        node = m_freeListHead;
        m_freeListHead = *(void**)((uint8_t*)node + 4);

        // Zero out fields of the node (offsets 4, 8, 12). First 4 bytes are left as-is.
        *(uint32_t*)((uint8_t*)node + 4) = 0;
        *(uint32_t*)((uint8_t*)node + 8) = 0;
        *(uint32_t*)((uint8_t*)node + 12) = 0;

        return node;
    }
};
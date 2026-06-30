// FUNC_NAME: NetPacketAllocator::allocateReliableNode
// Function address: 0x00637c50
// Allocates a 0x20-byte packet node from a fixed-size pool.
// Returns a pointer to the new node, or calls an alternative allocation (FUN_00635a80) if the pool is exhausted and a fallback is indicated.
// The node is initialized with type byte 0x05 at offset +0x04, and a sequence number from the allocator's context.
// The allocator's byte count at (this+0x10+0x24) is incremented by 0x20.

struct ReliablePacketNode {
    ReliablePacketNode* next;     // +0x00
    uint8_t typeFlags[4];         // +0x04 (bytes: 0x05, 0x00, 0xFF, 0x00)
    uint32_t sequence;            // +0x08 (copied from allocator's sequence counter at this+0x10+0x38)
    uint32_t field_0C;            // +0x0C (always set to 0)
    // padding up to 0x1C
    uint32_t field_1C;            // +0x1C (always set to 0)
};

// Global function pointer for memory allocation (likely TNL::alloc)
// Signature: void* (int, int)
extern void* (*g_allocFunc)(int, int);

// Forward declarations of helper functions
void initNodeA(ReliablePacketNode* node, int param);  // FUN_00637910
void initNodeB();                                       // FUN_00637960

ReliablePacketNode* NetPacketAllocator::allocateReliableNode(int param) {
    // Attempt to allocate a 0x20-byte block from the global allocator
    ReliablePacketNode* node = (ReliablePacketNode*)(*g_allocFunc)(0, 0x20);
    
    // If allocation failed:
    if (node == nullptr) {
        // If the allocator's context (this) is non-null, use an alternative allocation path
        if (this != nullptr) {
            node = (ReliablePacketNode*)FUN_00635a80();
            return node;
        }
        // Otherwise return null
        node = nullptr;
    } else {
        // Allocation succeeded: update the byte count in the allocator's pool manager
        // The pool manager is at offset +0x10 from 'this'
        int* allocatorPool = *(int**)((char*)this + 0x10);
        int* byteCount = (int*)((char*)allocatorPool + 0x24);
        *byteCount += 0x20;  // Increment allocated bytes
    }

    // Initialize node fields
    // Link the node into the allocator's free list (or similar linked list)
    ReliablePacketNode** listHead = *(ReliablePacketNode***)((char*)allocatorPool + 0x0C);
    node->next = *listHead;
    *listHead = node;

    // Set type/flag bytes
    node->typeFlags[0] = 5;    // +0x04: type identifier (reliable packet?)
    node->typeFlags[1] = 0;    // +0x05
    node->typeFlags[2] = 0xFF; // +0x06
    node->typeFlags[3] = 0;    // +0x07

    // Copy sequence number from the allocator's context at (pool + 0x38)
    node->sequence = *(uint32_t*)((char*)allocatorPool + 0x38);
    node->field_0C = 0;
    node->field_1C = 0;

    // Call node initialization routines with the given parameter
    initNodeA(node, param);  // FUN_00637910
    initNodeB();             // FUN_00637960

    return node;
}
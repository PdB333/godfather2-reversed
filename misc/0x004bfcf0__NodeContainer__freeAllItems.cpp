// FUNC_NAME: NodeContainer::freeAllItems
// Address: 0x004bfcf0
// Role: Releases all items in a container linked list, returning them to a global memory pool or calling custom destructors.

#include <cstdint>

// Forward declarations for external functions
void releaseSubObject();
void freeBuffer(void* ptr);

// Pool manager structure for memory allocation
struct PoolManager {
    uint8_t* poolBase;      // +0x00: Base address of pooled memory block
    uint32_t poolSize;      // +0x04: Size of the pooled block
    void* freeListHead;     // +0x08: Head of free list
    uint32_t freeCount;     // +0x0C: Number of free nodes
    // ... other fields ...
    void* destructor;       // +0x1C: Pointer to destructor object (vtable at offset 8)
};

// Node in the container's linked list
struct Node {
    void* nextFree;         // +0x00: Next node in free list (used by pool)
    // ... data ...
    Node* nextInContainer;  // +0x10: Next node in container's linked list
};

// Container class with sub-object, buffer, and linked list
struct NodeContainer {
    void* subObject;        // +0x90: Pointer to sub-object (released first)
    void* buffer;           // +0x80: Pointer to buffer (released second)
    Node* listHead;         // +0x94: Head of linked list of nodes
};

// Global pointer structure (root of pool access)
struct GlobalRoot {
    uint8_t* context;       // +0x00: pointer to context
};

// Global variable (address 0x012233a8)
extern GlobalRoot* g_globalRoot;

// Function to free all items in the container
void __fastcall NodeContainer::freeAllItems(NodeContainer* this)
{
    // Release sub-object if present
    if (this->subObject != 0) {
        releaseSubObject();
        this->subObject = 0;
    }

    // Release buffer if present
    if (this->buffer != 0) {
        freeBuffer(this);
    }

    // Get pointer to the global pool manager
    PoolManager* pool = *(PoolManager**)((uint8_t*)g_globalRoot->context + 0x3a00);

    // Iterate over the linked list of nodes
    Node* currentNode = this->listHead;
    while (currentNode != 0) {
        Node* nextNode = currentNode->nextInContainer;

        // Only process if pool is valid
        if (pool->poolBase != 0) {
            // Check if node belongs to the pool's memory range or if no destructor is set
            if ((pool->destructor == 0) ||
                ((uint8_t*)pool->poolBase <= (uint8_t*)currentNode &&
                 (uint8_t*)currentNode < (uint8_t*)pool->poolBase + pool->poolSize)) {
                // Return node to pool's free list
                currentNode->nextFree = pool->freeListHead;
                pool->freeCount++;
                pool->freeListHead = currentNode;
            } else {
                // Call custom destructor for this node (vtable at destructor + 8)
                (*(void(__thiscall**)(Node*))(*(uint32_t*)pool->destructor + 8))(currentNode);
            }
        }

        currentNode = nextNode;
    }
}
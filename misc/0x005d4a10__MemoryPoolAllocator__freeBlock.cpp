// FUNC_NAME: MemoryPoolAllocator::freeBlock
#include <cstddef>

// Represents a node in the free list, tracking a memory range and its free blocks.
struct FreeListNode {
    FreeListNode* prev;     // +0x00: previous node in doubly linked list
    FreeListNode* next;     // +0x04: next node in doubly linked list
    void* blockStart;       // +0x08: start address of managed range (or free list head)
    void* blockEnd;         // +0x0C: end address of managed range (exclusive)
    int allocatedCount;     // +0x10: number of currently allocated blocks in this range
};

// A memory pool allocator that manages multiple free block ranges.
class MemoryPoolAllocator {
public:
    void* vtable;               // +0x00: virtual function table (e.g., for node destruction)
    char allowNodeFree;         // +0x05: flag; if zero, empty nodes can be deallocated
    int nodeCount;              // +0x14: total number of free list nodes
    FreeListNode* freeListHead; // +0x1C: pointer to the first node in the free list

    // Returns true if the block was successfully freed, false otherwise.
    bool freeBlock(void* block);
};

bool MemoryPoolAllocator::freeBlock(void* block) {
    if (block == nullptr) {
        return false;
    }

    FreeListNode* node = this->freeListHead;
    if (node == nullptr) {
        return false;
    }

    // Walk the linked list to find the node whose memory range contains the block.
    while (block < node->blockStart || block >= node->blockEnd) {
        node = node->next;
        if (node == nullptr) {
            return false;
        }
    }

    // Push the block onto the node's single-linked free list.
    // The first 4 bytes of the freed block are overwritten with the previous head.
    *static_cast<void**>(block) = node->blockStart;
    node->blockStart = block;

    // Decrease the count of allocated blocks for this node.
    node->allocatedCount--;

    // If the node becomes completely free and we're allowed, remove and destroy it.
    if (node->allocatedCount == 0 && this->allowNodeFree == '\0') {
        // Unlink from the doubly linked list.
        if (node->prev == nullptr) {
            this->freeListHead = node->next;
        } else {
            node->prev->next = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }

        // Call the node's destructor via the vtable (third virtual function).
        using NodeDestructor = void (*)(FreeListNode*);
        (*reinterpret_cast<NodeDestructor>(
            *reinterpret_cast<void**>(this->vtable) + 8 // offset 8 = third entry
        ))(node);

        this->nodeCount--;
    }

    return true;
}
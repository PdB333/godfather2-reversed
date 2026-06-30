// FUNC_NAME: FreeList::insertFreeBlock
// Address: 0x00672dc0
// Inserts a freed memory block into a sorted free list (by address), coalescing adjacent blocks.
// Free nodes have the following layout at the start of each free block:
//   +0x00: size (int)
//   +0x04: next (FreeNode*)
//   +0x08: prev (FreeNode*)
// The free list's head pointer is stored at this+0x10.

struct FreeNode {
    int size;        // size of the free block (including this header)
    FreeNode* next;  // next node in free list
    FreeNode* prev;  // previous node in free list
};

struct FreeList {
    // ... other members ...
    FreeNode* head;  // offset 0x10
};

void* __thiscall FreeList::insertFreeBlock(void* block) {
    FreeNode* node = static_cast<FreeNode*>(block);
    FreeNode* current = this->head;
    FreeNode* prev = nullptr;

    // Walk the free list to find insertion point (sorted by address)
    while (current != nullptr) {
        if (node < current) {
            break;
        }
        prev = current;
        current = current->next;
    }

    if (prev != nullptr) {
        // Check if node can be merged with prev
        if (reinterpret_cast<FreeNode*>(reinterpret_cast<char*>(prev) + prev->size) == node) {
            // Merge with prev
            if (current == nullptr ||
                reinterpret_cast<FreeNode*>(reinterpret_cast<char*>(node) + node->size) != current) {
                // Just merge with prev
                prev->size += node->size;
                return prev;
            } else {
                // Merge with both prev and current
                prev->size += node->size + current->size;
                prev->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = prev;
                }
                return prev;
            }
        } else {
            // Not adjacent to prev, link prev->next to node
            prev->next = node;
        }
    } else {
        // No previous node, node becomes head
        this->head = node;
    }

    // Now set node's prev and next, possibly merging with current
    if (current == nullptr ||
        reinterpret_cast<FreeNode*>(reinterpret_cast<char*>(node) + node->size) != current) {
        // No merge with current
        node->prev = prev;
        node->next = current;
        if (current != nullptr) {
            current->prev = node;
        }
    } else {
        // Merge node with current
        node->size += current->size;
        node->prev = current->prev;
        node->next = current->next;
        if (node->next != nullptr) {
            node->next->prev = node;
        }
    }

    return node;
}
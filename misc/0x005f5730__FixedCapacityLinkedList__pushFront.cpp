// FUNC_NAME: FixedCapacityLinkedList::pushFront

#include <cstdint>

// Node structure for doubly linked list with fixed capacity
struct FixedCapacityListNode {
    FixedCapacityListNode* prev; // +0x0
    FixedCapacityListNode* next; // +0x4
};

// Fixed-capacity doubly linked list container
struct FixedCapacityLinkedList {
    FixedCapacityListNode* head;   // +0x0
    FixedCapacityListNode* tail;   // +0x4
    uint16_t maxCount;            // +0x8
    uint16_t count;               // +0xA

    // Inserts node at front of list, returns true on success, false if list is full or null
    bool __fastcall pushFront(FixedCapacityListNode* node);
};

bool FixedCapacityLinkedList::pushFront(FixedCapacityListNode* node) {
    // Validate this pointer and capacity
    if (this == nullptr) {
        return false;
    }

    if (count >= maxCount) {
        return false;
    }

    if (count == 0) {
        // Empty list: set both head and tail to the new node
        tail = node;
    } else {
        // Defensive check: head must be valid
        if (head == nullptr) {
            return false;
        }
        // Link old head's prev to the new node
        head->prev = node;
    }

    // Set new node's prev to old head (or null if list was empty)
    node->prev = head;
    // New node becomes the new head; its next is null (end of list)
    node->next = nullptr;

    // Update count and head pointer
    count++;
    head = node;

    return true;
}
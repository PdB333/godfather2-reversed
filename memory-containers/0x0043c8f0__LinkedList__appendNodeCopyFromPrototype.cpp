// FUNC_NAME: LinkedList::appendNodeCopyFromPrototype
// Function at 0x0043c8f0: Adds a new node to the end of a doubly linked list,
// copying data from a stored prototype node (or a static default).
// Class layout:
// +0x00: ListNode* head
// +0x04: ListNode* tail
// +0x08: int count
// +0x0C: ListNode* sourcePrototype (source to copy data from; if null, uses static default)
// +0x10: Allocator* allocator (pointer to a struct with first entry as allocation function)
// Node layout:
// +0x00: int data (copied from prototype)
// +0x04: ListNode* next
// +0x08: ListNode* prev

#include <cstdint>

struct ListNode {
    int32_t data;           // +0x00
    ListNode* next;         // +0x04
    ListNode* prev;         // +0x08
};

struct Allocator {
    // First virtual function: alloc(size)
    void* (*alloc)(size_t size); // +0x00
};

class LinkedList {
public:
    // Member variables (offsets from 'this')
    ListNode* head;               // +0x00
    ListNode* tail;               // +0x04
    int count;                    // +0x08
    ListNode* sourcePrototype;    // +0x0C  (prototype node whose data is copied)
    Allocator* allocator;         // +0x10

    // Method: appends a new node to the end, copying data from sourcePrototype
    void appendNodeCopyFromPrototype() {
        ListNode* srcNode = this->sourcePrototype;
        if (srcNode == nullptr) {
            srcNode = reinterpret_cast<ListNode*>(&DAT_01218a14); // static default node (address from Ghidra)
        }

        // Allocate new node (12 bytes) through allocator's alloc function
        ListNode* newNode = reinterpret_cast<ListNode*>(this->allocator->alloc(0xC));
        if (newNode != nullptr) {
            newNode->data = srcNode->data; // copy data from prototype
            newNode->next = nullptr;       // initialize next to null
            newNode->prev = nullptr;       // initialize prev to null
        }

        this->count++;

        if (this->tail != nullptr) {
            // List not empty: append to tail
            this->tail->next = newNode;
            newNode->prev = this->tail;
            this->tail = newNode;
        } else {
            // List empty: new node is both head and tail
            this->head = newNode;
            this->tail = newNode;
        }
    }
};
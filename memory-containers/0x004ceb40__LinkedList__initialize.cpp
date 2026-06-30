// FUNC_NAME: LinkedList::initialize
// Address: 0x004ceb40
// Description: Initializes a circular doubly linked list with a sentinel node. Uses virtual functions for cleanup and allocation.

#include <cstdint>

// Node structure (12 bytes)
struct ListNode {
    ListNode* next;   // +0x00
    ListNode* prev;   // +0x04
    uint32_t data;    // +0x08
};

// Class representing a linked list (size at least 0x20 bytes)
class LinkedList {
public:
    void* vtable;                 // +0x00
    int32_t field_4;              // +0x04 – used to conditionally call external function
    ListNode* temporaryBuffer;    // +0x08 – optional stack buffer fallback
    uint8_t pad[0x10];            // +0x0C to +0x17 (padding)
    ListNode* head;               // +0x18 (offset 6 in int* terms)
    int32_t count;                // +0x1C (offset 7)

    // Virtual function table:
    // [0] – allocate(size, buffer) returns void*
    // [2] – release/cleanup (called on the vtable pointer itself per decompilation)
    LinkedList* initialize();
};

// External helper functions
extern int32_t FUN_004265d0(int32_t param, void* vtablePtr);
extern void FUN_004cef60(LinkedList* obj, void* vtablePtr, uint32_t value);

LinkedList* LinkedList::initialize() {
    // Extract vtable pointer from this
    void** vtablePtr = reinterpret_cast<void**>(this->vtable);
    int32_t fieldVal = this->field_4;

    // Call virtual function at vtable[2] on the vtable pointer (unusual, kept as decompiled)
    reinterpret_cast<void(*)(void*)>(vtablePtr[2])(vtablePtr);

    // Compute value based on field_4
    uint32_t value = 0;
    if (fieldVal != 0) {
        value = FUN_004265d0(fieldVal, vtablePtr);
    }

    // Additional initialization
    FUN_004cef60(this, vtablePtr, value);

    // Use either the existing temporary buffer or a local one
    ListNode* buffer = this->temporaryBuffer;
    ListNode localBuf = {nullptr, nullptr, 0}; // 12-byte stack allocation
    if (buffer == nullptr) {
        buffer = &localBuf;
    }

    // Allocate a new node via vtable[0] (size 12, buffer pointer)
    ListNode* newNode = reinterpret_cast<ListNode*>(
        reinterpret_cast<void* (*)(int32_t, void*)>(vtablePtr[0])(12, buffer)
    );

    // Initialize the node as a self-loop (circular doubly linked sentinel)
    if (newNode != nullptr) {
        newNode->next = newNode;   // self-reference as next
        // Set prev (offset +4) to self. The condition is always true.
        if (reinterpret_cast<int32_t*>(&newNode->prev) != nullptr) {
            newNode->prev = newNode;
        }
    }

    // Update list state
    this->head = newNode;
    this->count = 0;

    return this;
}
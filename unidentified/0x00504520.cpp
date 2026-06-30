// FUN_NAME: ListNode::~ListNode
// Address: 0x00504520
// Role: Destructor for a doubly linked list node, removes node from list if linked, then calls operator delete if flag bit 0 is set.

#include <cstdint>

// Forward declaration of operator delete (likely at 0x009c8eb0)
extern void __cdecl operatorDelete(void* ptr);

class ListNode {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // Other members (unknown) occupy offsets +0x04 to +0x0F

    // Doubly linked list pointers:
    // +0x10: next node
    ListNode* next;
    // +0x14: previous node
    ListNode* prev;

    // Destructor
    // @param deleteFlag: If bit 0 set, calls operator delete at end
    // @returns this pointer
    ListNode* __thiscall ~ListNode(uint8_t deleteFlag) {
        // Set vtable to derived class vtable (e.g., PTR_FUN_00e37f48)
        this->vtable = (void*)0x00e37f48;

        // If node is linked (next != 0), remove itself from the doubly linked list
        if (this->next != nullptr) {
            // prev->next = next
            this->prev->next = this->next;
            // next->prev = prev
            this->next->prev = this->prev;
            // Clear next pointer (prev left as is, but not used after removal)
            this->next = nullptr;
        }

        // Set vtable to base class vtable (e.g., PTR_LAB_00e37304) for base destructor chain
        this->vtable = (void*)0x00e37304;

        // If deleteFlag & 1, free memory
        if (deleteFlag & 1) {
            operatorDelete(this);
        }

        return this;
    }
};
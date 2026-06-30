// FUNC_NAME: BaseObject::~BaseObject

#include <cstdint>

// Node structure for linked list at offset +0x04
struct ListNode {
    void* data;        // +0x00
    ListNode* next;    // +0x04
};

class BaseObject {
public:
    // Virtual function table (set to destructor vtable)
    void* vtable;                  // +0x00
    ListNode* listHead;            // +0x04

    // Destructor with scalar delete flag (byte)
    // param_1 (this): BaseObject*
    // param_2 (deleteFlag): bit0 = delete this after cleanup
    void* __thiscall ~BaseObject(uint8_t deleteFlag) {
        // Set vtable to destructor-specific vtable for correct virtual dispatch
        this->vtable = reinterpret_cast<void*>(0x00e32808);  // PTR_FUN_00e32808

        // Traverse the linked list and clear both pointers of each node
        ListNode* current = this->listHead;
        while (current != nullptr) {
            ListNode* nextNode = current->next;   // save next before clearing
            current->next = nullptr;              // detach from list
            current->data = nullptr;              // clear data pointer
            current = nextNode;
        }
        // Optional self-deallocation
        if (deleteFlag & 1) {
            reinterpret_cast<void (*)(void*)>(0x009c8eb0)(this);  // operator delete or custom dealloc
        }
        return this;
    }
};
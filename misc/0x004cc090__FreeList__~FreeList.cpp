// FUNC_NAME: FreeList::~FreeList
// Address: 0x004cc090
// Role: Destructor for a singly-linked list of fixed-size nodes (data + next pointer).
// Clears all nodes in the list by zeroing data and next fields. Does not free nodes individually,
// as they are assumed to be part of a pool or static allocation. If the deleting flag is set,
// also calls operator delete on the object itself.
// This is the MSVC scalar deleting destructor wrapper.

struct Node {
    void* data; // +0x0
    Node* next; // +0x4
};

class FreeList {
public:
    // Virtual function table – must be set by constructor/destructor
    void** vtable; // +0x0
    Node* head;    // +0x4

    // __thiscall
    // param_2: 0 = no delete, 1 = delete this after clean-up
    __thiscall ~FreeList(byte deletingFlag) {
        // Update vtable to base class (or final overrider)
        this->vtable = reinterpret_cast<void**>(&PTR_FUN_00e32808);

        // Walk the list and clear every node
        Node* curr = this->head;
        while (curr != nullptr) {
            Node* next = curr->next; // save next before clearing
            curr->next = nullptr;
            curr->data = nullptr;
            curr = next;
        }

        // Optionally release the memory (operator delete)
        if (deletingFlag & 1) {
            FUN_009c8eb0(this); // operator delete
        }

        // Return this (standard for MSVC scalar deleting destructor)
        return this;
    }
};
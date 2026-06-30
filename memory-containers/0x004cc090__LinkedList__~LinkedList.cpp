// FUNC_NAME: LinkedList::~LinkedList

// Destructor for a singly-linked list class.
// This class manages a linked list of nodes, each with a data pointer and a next pointer.
// The destructor zeros out each node (clearing data and next pointers) before optionally freeing the list object itself.
// 
// Class layout:
//   +0x00: vtable pointer
//   +0x04: head pointer (Node*)
//
// Node layout:
//   +0x00: data pointer (void*)
//   +0x04: next pointer (Node*)

class LinkedList {
public:
    struct Node {
        void* data;   // +0x00
        Node* next;   // +0x04
    };

    void** vtable;    // +0x00 (implicit in __thiscall)
    Node* head;       // +0x04

    // __thiscall destructor
    // param_2: byte flag - if bit 0 is set, operator delete is called on this object
    void __thiscall destructor(byte deleteFlag) {
        // Set vtable pointer (might be redundant if called from virtual destructor)
        this->vtable = (void**)&PTR_FUN_00e32808;

        // Traverse the linked list and zero out each node
        Node* current = this->head;
        while (current != nullptr) {
            Node* next = current->next;
            current->next = nullptr;    // clear next pointer
            current->data = nullptr;    // clear data pointer
            current = next;             // move to next node
        }

        // Optionally deallocate the list object itself
        if ((deleteFlag & 1) != 0) {
            // custom or standard deallocation at 0x009c8eb0 (likely operator delete)
            this->operatorDelete();     // placeholder for FUN_009c8eb0(this);
        }
    }
};
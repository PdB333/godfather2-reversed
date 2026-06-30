// FUNC_NAME: ObjectList::~ObjectList
// Function address: 0x0065a5a0
// Destructor for a generic object list with a vtable pointer and a head pointer to a linked list of nodes.
// The list nodes contain three 4-byte fields; the third field is the 'next' pointer.
// After clearing the list, if the low bit of flags is set, the object's memory is freed via a custom allocator.

class ObjectList {
public:
    // Vtable pointer at +0x00
    // This pointer is set to a global vtable (PTR_LAB_00e42de4) in the destructor.
    ListNode* head; // +0x04

    // Destructor: clears all nodes, resets vtable, optionally frees memory.
    ObjectList* __thiscall ~ObjectList(byte flags);
};

struct ListNode {
    uint unknown0; // +0x00
    uint unknown1; // +0x04
    ListNode* next; // +0x08
};

ObjectList* __thiscall ObjectList::~ObjectList(ObjectList* this, byte flags) {
    // Set vtable to base class vtable (likely a base destructor action)
    this->vtable = (void**)&PTR_LAB_00e42de4; // offset +0x00

    ListNode* node = this->head; // +0x04
    while (node != nullptr) {
        ListNode* nextNode = node->next; // +0x08
        // Clear the node's fields
        node->unknown0 = 0; // +0x00
        node->unknown1 = 0; // +0x04
        node->next = nullptr; // +0x08
        node = nextNode;
    }

    // If the low bit of flags is set, deallocate the object itself
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // Custom deallocation function (likely operator delete)
    }

    return this;
}
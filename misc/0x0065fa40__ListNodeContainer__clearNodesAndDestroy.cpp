// FUNC_NAME: ListNodeContainer::clearNodesAndDestroy
// Address: 0x0065fa40
// Function to reset a linked list of nodes (each node has three 4-byte fields) and optionally free the container.

// Known vtable pointer for this class type.
extern void* s_vtable_00e42de4;

// Node structure (assumed 12 bytes: unknown0, unknown1, next).
struct ListNode {
    int field0;   // +0x00
    int field1;   // +0x04
    ListNode* next; // +0x08
};

// Container class holding a linked list head at offset +0x04.
class ListNodeContainer {
public:
    void* vtable; // +0x00
    ListNode* head; // +0x04

    // Reset all nodes in the list and optionally delete this instance.
    // @param flags: if bit0 is set, free memory via operator delete.
    void* __thiscall clearNodesAndDestroy(byte flags);
};

void* __thiscall ListNodeContainer::clearNodesAndDestroy(byte flags) {
    // Set vtable to a global default (or sentinel) – possibly to prevent virtual calls.
    this->vtable = &s_vtable_00e42de4;

    // Walk the linked list, clearing each node.
    ListNode* current = this->head;
    while (current != nullptr) {
        ListNode* next = current->next; // save next before clearing
        current->field0 = 0;
        current->field1 = 0;
        current->next = nullptr;
        current = next;
    }

    // If flag indicates ownership, delete this container.
    if ((flags & 1) != 0) {
        // Call underlying deallocation (likely operator delete or a custom allocator).
        // The callee at 0x009c8eb0 is assumed to be an operator delete or similar.
        operator delete(this);
    }

    return this;
}
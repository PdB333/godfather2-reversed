// FUNC_NAME: IntrusiveNodeList::`scalar deleting destructor'
// Function at 0x004b1d50: Scalar deleting destructor for a class containing an intrusive singly-linked list.
// Sets vtable pointer, traverses list (nodes at offset 4) clearing each node's fields and next pointer,
// then optionally deallocates the owning object if flag & 1.

// Node structure (inferred from clears of [0], [1], [2] while traversing via [2])
struct IntrusiveNode {
    void* field0;       // +0x00
    void* field1;       // +0x04
    IntrusiveNode* next; // +0x08 – next pointer used for traversal
};

// Container class (partial definition)
class IntrusiveNodeList {
    void* vtable;                // +0x00 – points to PTR_LAB_00e42de4
    IntrusiveNode* head;         // +0x04 – start of linked list
    // ... other members
public:
    // Scalar deleting destructor; param2: flag (bit0 = delete this)
    void __thiscall scalarDeletingDestructor(byte flag);
};

// Reconstructed function
void __thiscall IntrusiveNodeList::scalarDeletingDestructor(byte flag) {
    // Set vtable pointer (likely to base class or derived vtable)
    this->vtable = &PTR_LAB_00e42de4; // global vtable symbol

    IntrusiveNode* current = this->head;       // param_1[1] at offset 4
    while (current != nullptr) {
        IntrusiveNode* next = current->next;   // puVar2[2] at offset 8
        // Clear entire node structure
        current->field0 = nullptr;  // puVar2[0]
        current->field1 = nullptr;  // puVar2[1]
        current->next = nullptr;    // puVar2[2]
        current = next;
    }

    // If the lower bit of the flag is set, deallocate the object
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete
    }

    // Return this (convention for deleting destructors)
    return this; // implicit in assembly, return type void in high-level but GCC/VC may return this
}
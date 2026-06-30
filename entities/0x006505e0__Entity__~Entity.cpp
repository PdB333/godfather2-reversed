// FUNC_NAME: Entity::~Entity

// Destructor for class Entity (or similar base with multiple inheritance).
// Vtable pointers at +0x0 and +0x18 suggest two base classes.
// Clears a singly-linked list at +0x4 where each node has offsets 0,4,8.
// Optionally deallocates memory if (param_2 & 1) is set.

class Entity {
public:
    // Virtual function table pointer (primary)
    void** vtable; // +0x0

    // Linked list head (list of components/children, nodes of type UnknownLinkNode)
    void* linkedListHead; // +0x4

    // Padding or other fields...
    // Possibly more fields between +0x8 and +0x18

    // Second virtual function table pointer (secondary base)
    void** vtable2; // +0x18

    // Constructor and other methods omitted.
};

// Structure for the linked list nodes (size 12 bytes)
struct UnknownLinkNode {
    void* field0;      // +0x0
    void* field4;      // +0x4
    UnknownLinkNode* next; // +0x8
};

// __thiscall destructor
void __thiscall Entity::~Entity(Entity* this, byte flags) {
    UnknownLinkNode* currentNode;
    UnknownLinkNode* nextNode;

    // Set vtable pointers (likely to indicate destruction in progress)
    this->vtable = (void**)&PTR_LAB_00e42de4;  // Placeholder: address from Ghidra
    this->vtable2 = (void**)&PTR_LAB_00e317cc; // Placeholder: address from Ghidra

    // Iterate over the linked list starting at +0x4
    currentNode = (UnknownLinkNode*)this->linkedListHead;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        // Zero out all three fields of the node
        currentNode->field0 = nullptr;
        currentNode->field4 = nullptr;
        currentNode->next = nullptr;
        // Note: Node memory is not freed here; likely handled elsewhere or nodes are statically allocated.
        currentNode = nextNode;
    }

    // If the delete flag is set, call the deallocation function
    if ((flags & 1) != 0) {
        // FUN_009c8eb0 likely calls operator delete or a custom deallocator
        FUN_009c8eb0(this);
    }

    // return this; implied by decompiled return
}
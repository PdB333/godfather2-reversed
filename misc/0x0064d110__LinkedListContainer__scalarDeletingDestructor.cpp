// FUNC_NAME: LinkedListContainer::scalarDeletingDestructor

// Reconstructed from 0x0064d110
// This is the scalar deleting destructor for a class that maintains a linked list of nodes.
// It first sets the vtable pointer (likely to a static vtable), clears the linked list by
// zeroing each node's first two fields and next pointer, then optionally calls operator delete
// if the low bit of the destructor flag (param_2) is set.

struct Node {
    int field0;      // +0x00
    int field1;      // +0x04
    Node* next;      // +0x08
};

class LinkedListContainer {
public:
    void** vtable;   // +0x00 - Points to static vtable (PTR_LAB_00e42de4)
    Node* head;      // +0x04 - Head of linked list

    // Destructor (with optional deallocation flag)
    // param_2: bit0 = 1 means call operator delete(this)
    LinkedListContainer* __thiscall scalarDeletingDestructor(bool shouldDelete) {
        // Set vtable (likely for base class or to reset vtordisp)
        this->vtable = &PTR_LAB_00e42de4;

        // Traverse the linked list and clear each node
        Node* node = this->head;
        Node* nextNode;
        while (node != nullptr) {
            nextNode = node->next;   // Save next before clearing
            node->field0 = 0;
            node->field1 = 0;
            node->next = nullptr;    // Unlink
            node = nextNode;
        }

        // Optionally deallocate this object
        if (shouldDelete) {
            // FUN_009c8eb0 is likely operator delete(void*)
            operator delete(this);
        }

        return this;
    }

    // Also provide a standard destructor that internally calls the scalar deleting variant
    // with shouldDelete = false.
    ~LinkedListContainer() {
        scalarDeletingDestructor(false);
    }
};

// Note: The actual operator delete is at 0x009c8eb0 (assumed).
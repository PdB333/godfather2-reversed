// FUNC_NAME: LinkedDataList::scalarDeletingDestructor
// Function address: 0x0064d110
// This is the scalar deleting destructor for a class that manages a linked list of 12-byte nodes.
// The destructor clears each node's data and optionally deallocates the object memory.

// Node structure: 12 bytes, fields at offsets +0x0, +0x4, +0x8
struct LinkedListNode {
    uint32_t field0;       // +0x00
    uint32_t field4;       // +0x04
    LinkedListNode* next;  // +0x08  (next node pointer)
};

class LinkedDataList {
public:
    // Vtable pointer at +0x00
    void* vtable;                // +0x00
    LinkedListNode* listHead;    // +0x04 (pointer to first node)

    // Scalar deleting destructor (takes bool flag for deletion)
    void* scalarDeletingDestructor(bool deleteFlag);
};

void* LinkedDataList::scalarDeletingDestructor(bool deleteFlag) {
    // Set vtable to this class's vtable (ensures correct virtual dispatch during destruction)
    this->vtable = (void*)0x00e42de4;   // PTR_LAB_00e42de4

    // Clear all nodes in the linked list by zeroing their contents.
    LinkedListNode* currentNode = this->listHead;
    while (currentNode != nullptr) {
        LinkedListNode* nextNode = currentNode->next;
        currentNode->field0 = 0;
        currentNode->field4 = 0;
        currentNode->next = nullptr;
        currentNode = nextNode;
    }

    // If the deletion flag is set, free the object's memory (operator delete)
    if ((deleteFlag & 1) != 0) {
        operator delete(this);
    }

    return this;
}
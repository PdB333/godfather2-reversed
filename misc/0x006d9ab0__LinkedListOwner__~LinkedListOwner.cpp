// FUNC_NAME: LinkedListOwner::~LinkedListOwner
// Function address: 0x006d9ab0
// Scalar deleting destructor for a class that owns a singly-linked list of nodes.
// Clears the list by zeroing each node's data and next pointers, then optionally deallocates the object.

class LinkedListOwner {
public:
    void* vtable;            // +0x00
    LinkedListNode* firstNode; // +0x04
};

struct LinkedListNode {
    void* data;      // +0x00
    LinkedListNode* next; // +0x04
};

// Custom deallocation function (likely operator delete or placement delete)
void __thiscall deleteThis(LinkedListOwner* obj);

LinkedListOwner* __thiscall LinkedListOwner::~LinkedListOwner(byte shouldDelete)
{
    // Set vtable to the base or most-derived vtable for proper destruction sequence
    thisPtr->vtable = &PTR_FUN_00e32808;

    // Iterate through the linked list and wipe each node's fields
    LinkedListNode* currentNode = thisPtr->firstNode;
    while (currentNode != nullptr) {
        LinkedListNode* nextNode = currentNode->next;
        currentNode->next = nullptr;   // break the chain
        currentNode->data = nullptr;   // clear stored pointer
        currentNode = nextNode;
    }

    // If the scalar-deleting flag is set, free the object memory
    if ((shouldDelete & 1) != 0) {
        deleteThis(thisPtr);
    }

    return thisPtr;
}
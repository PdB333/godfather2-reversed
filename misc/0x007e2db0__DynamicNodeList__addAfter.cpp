// FUNC_NAME: DynamicNodeList::addAfter
// Address: 0x007e2db0
// Role: Adds a new node to the dynamic array and inserts it after the given node in a linked list.
// The container stores 8-byte entries (Node structs) and maintains a linked list via the 'next' field at offset +4.
// When the array is full, it grows by doubling capacity (or to 1 if empty) via a global reallocation function.

struct Node {
    void* data;   // +0x00
    Node* next;   // +0x04
};

class DynamicNodeList {
public:
    Node* buffer;   // +0x00
    int count;      // +0x04
    int capacity;   // +0x08

    // Global function that reallocates the buffer for the given capacity.
    // Assumes it updates the container's buffer and capacity internally.
    static void grow(int newCapacity);

    // Inserts a new node after the node pointed to by nodePtr.
    // nodePtr is a pointer to a Node* (the node after which to insert).
    void addAfter(Node** nodePtr) {
        // Check if we need to grow the buffer
        if (count == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            grow(newCapacity);
        }

        // Get pointer to the new slot in the buffer
        Node* newSlot = &buffer[count];
        count++;

        // Retrieve the node to insert after
        Node* targetNode = *nodePtr;

        // Initialize the new slot
        newSlot->data = targetNode;
        newSlot->next = nullptr;

        if (targetNode != nullptr) {
            // Insert newSlot after targetNode in the linked list
            newSlot->next = targetNode->next;
            targetNode->next = newSlot;
        }
    }
};
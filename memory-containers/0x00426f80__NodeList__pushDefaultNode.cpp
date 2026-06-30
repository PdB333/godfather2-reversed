// FUNC_NAME: NodeList::pushDefaultNode

// Reconstructed from 0x00426f80 - Insert a node with default data at the front of a doubly linked list.
// The list stores 4-byte values (data) and maintains head, tail, and count.
// Allocation is done via a function pointer stored in the class (double indirection for vtable-like access).

class NodeList {
private:
    struct Node {
        void* data;   // +0x00 – pointer/int stored in the node
        Node* next;   // +0x04 – next node in list
        Node* prev;   // +0x08 – previous node in list
    };

    Node* head;                 // +0x00
    Node* tail;                 // +0x04
    int count;                  // +0x08
    void* defaultData;          // +0x0C – source data to copy when pushDefaultNode is called
    void* (* volatile *allocFuncPtr)(int size); // +0x10 – pointer to a function pointer that allocates memory

public:
    // Push a new node containing the stored default data (or global default if null) at the front.
    void pushDefaultNode() {
        // Determine data source: use member defaultData, else a global constant.
        void* source = this->defaultData;
        if (source == nullptr) {
            source = (void*)&DAT_01218a14; // global default value (address from original binary)
        }

        // Allocate a new node (12 bytes) using the allocator function pointer.
        // The double indirection (*(this->allocFuncPtr)) mimics the vtable access pattern.
        Node* newNode = (Node*)(*(this->allocFuncPtr))(12); // +0x00: data, +0x04: next, +0x08: prev
        if (newNode == nullptr) {
            return; // allocation failure – no node added
        }

        // Copy the 4-byte value from the source into the new node's data field.
        newNode->data = *(void**)source;

        // Initialize next and prev to null (will be overwritten for next).
        newNode->next = nullptr;
        newNode->prev = nullptr;

        // Link the new node at the front of the list.
        newNode->next = this->head;          // +0x04: next becomes old head
        if (this->head != nullptr) {
            this->head->prev = newNode;      // old head's prev points to new node
        }
        this->head = newNode;                // new head is the new node
        this->count++;                       // increment element count

        // If the list was empty, this node is also the tail.
        if (this->tail == nullptr) {
            this->tail = newNode;
        }
    }
};
// FUNC_NAME: Pool::releaseNode
// Address: 0x006f9d00
// Removes a node from the intrusive doubly-linked list in a Pool object,
// calls its destructor and frees associated memory.

class Pool {
public:
    // Node structure offsets:
    // +0x00: data pointer (object to destroy)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: destructor function pointer (called on data)
    // +0x10: allocated block to free (via FUN_004daf90)
    // +0x14: unknown
    // +0x18: next node
    // +0x1C: previous node
    struct Node {
        void* data;          // +0x00
        int field_0x04;      // +0x04
        int field_0x08;      // +0x08
        void (*destructor)(void*); // +0x0C
        void* allocBlock;    // +0x10
        int field_0x14;      // +0x14
        Node* next;          // +0x18
        Node* prev;          // +0x1C
    };

    Node* head;        // +0x00
    Node* tail;        // +0x04
    int count;         // +0x08
    void* poolManager; // +0x10 (has vtable, second entry is dealloc function)

    void releaseNode(Node* node) {
        if (node == nullptr)
            return;

        // Update linked list pointers
        if (node == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            // Remove node from head
            head = node->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }

        // Free the block associated with this node (offset +0x10)
        if (node->allocBlock != nullptr) {
            // FUN_004daf90 is likely a memory deallocation routine
            FUN_004daf90(node + 4);
        }

        // Call the node's data destructor if data exists
        if (node->data != nullptr) {
            node->destructor(node->data);
        }

        // Call the pool manager's dealloc function on the node itself
        // poolManager has a vtable; second function (offset 4) is dealloc(node, 0)
        void* mgr = *(void**)poolManager;
        void (*dealloc)(void*, int) = *(void (**)(void*, int))((uint8_t*)mgr + 4);
        dealloc(node, 0);

        count--;
    }
};
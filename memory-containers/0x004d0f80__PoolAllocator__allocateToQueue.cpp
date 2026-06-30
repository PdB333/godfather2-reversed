// FUNC_NAME: PoolAllocator::allocateToQueue
// Function address: 0x004d0f80
// Role: Pops a node from the free list (param_1) and enqueues it into a FIFO queue (param_2), storing param_3 as the node's data.
// Offsets: param_1 (this): freeListHead at +0x10, freeListTail at +0x14; param_2 (queue): queueHead at +0x110, queueTail at +0x114.
// Node layout: [next (0x0)] [data (0x4)]

class PoolAllocator {
public:
    struct Node {
        Node* next;
        void* data;  // stored data (pointer or value)
    };

    Node* freeListHead;   // +0x10: head of free list
    Node* freeListTail;   // +0x14: tail of free list (only used when popping last node)

    // __fastcall: this in ecx, queue in edx, data on stack
    void __fastcall allocateToQueue(void* queue, void* data) {
        Node* node = freeListHead;
        if (node != nullptr) {
            // If this node is the last in the free list, clear the tail
            if (freeListTail == node) {
                freeListTail = nullptr;
            }
            // Advance free list head to next node
            freeListHead = node->next;
        }

        // Prepare the node
        node->next = nullptr;
        node->data = data;

        // Enqueue into the queue (FIFO)
        Node** queueTail = reinterpret_cast<Node**>(static_cast<char*>(queue) + 0x114);
        Node** queueHead = reinterpret_cast<Node**>(static_cast<char*>(queue) + 0x110);
        if (*queueTail != nullptr) {
            // Append after current tail
            (**queueTail).next = node;
            *queueTail = node;
        } else {
            // Queue was empty
            *queueHead = node;
            *queueTail = node;
        }
    }
};
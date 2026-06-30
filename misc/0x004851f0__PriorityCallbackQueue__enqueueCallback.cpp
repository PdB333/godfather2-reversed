// FUNC_NAME: PriorityCallbackQueue::enqueueCallback
// Address: 0x004851f0
// Role: Schedules a callback with a priority (0=immediate, 1-4=deferred queues)

class PriorityCallbackQueue {
    // Internal node structure for callback storage
    struct CallbackNode {
        void (*callback)(void*, void*); // +0x00: function pointer
        void* arg0;                     // +0x04: first argument
        void* arg1;                     // +0x08: second argument
        CallbackNode* next;             // +0x0C: linked list pointer
    };

    CallbackNode* freeList;     // +0x00: head of free node pool
    // Queue arrays: each priority level has a head and tail pointer
    // Layout:
    // +0x04: queue[1].head
    // +0x08: queue[1].tail
    // +0x0C: queue[2].head
    // +0x10: queue[2].tail
    // +0x14: queue[3].head
    // +0x18: queue[3].tail
    // +0x1C: queue[4].head
    // +0x20: queue[4].tail
    CallbackNode* queueHead[4]; // heads for priorities 1-4 (index 0 corresponds to priority 1)
    CallbackNode* queueTail[4]; // tails for priorities 1-4

    void allocateNode(); // FUN_00485280: allocate a new node and add to freeList

public:
    void enqueueCallback(void (*callback)(void*, void*), unsigned int priority, void* arg0, void* arg1) {
        if (priority == 0) {
            // Execute immediately
            callback(arg0, arg1);
            return;
        }

        // Wait until a free node is available
        while (freeList == nullptr) {
            allocateNode();
        }

        // Pop from free list
        CallbackNode* node = freeList;
        freeList = node->next;
        node->next = nullptr;

        // Clamp priority (1..4)
        if (priority > 4) {
            priority = 4;
        }

        // Fill node data
        node->callback = callback;
        node->arg1 = arg1;
        node->arg0 = arg0;

        // Index into queue arrays (0-based for priority 1)
        int idx = priority - 1;
        CallbackNode*& tail = queueTail[idx];
        CallbackNode*& head = queueHead[idx];

        // Append to the tail of the appropriate queue
        if (tail == nullptr) {
            // Empty queue — both head and tail point to new node
            head = node;
            tail = node;
        } else {
            // Link current tail to new node, then update tail
            tail->next = node;
            tail = node;
        }
    }
};
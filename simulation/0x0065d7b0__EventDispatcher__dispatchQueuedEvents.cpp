// FUNC_NAME: EventDispatcher::dispatchQueuedEvents
// 0065d7b0: Processes a linked list of event queues, dispatching each queued event via a virtual function, then freeing the queue structures.
class EventDispatcher {
public:
    struct EventQueueNode {
        QueueStruct* queue;   // +0x04
        EventQueueNode* next; // +0x08
    };

    struct QueueStruct {
        uint32_t* buffer;   // +0x00
        uint32_t capacity;  // +0x04
        uint32_t head;      // +0x08
        uint32_t count;     // +0x0C
    };

    // Virtual function table at offset +0x08 from 'this'
    struct DispatcherVTable {
        void (*handleEvent)(uint32_t param1, uint32_t param2); // index 1 (offset +0x04)
    };

    void dispatchQueuedEvents(EventQueueNode** listHead) {
        EventQueueNode* currentNode;
        if (*listHead == nullptr) {
            currentNode = nullptr;
        } else {
            // Skip the dummy head node
            currentNode = (*listHead)->next;
        }

        while (currentNode != nullptr) {
            QueueStruct* queue = currentNode->queue;
            while (queue->count > 0) {
                // Read event at current head
                uint32_t* eventData = &queue->buffer[queue->head * 2];
                uint32_t param0 = eventData[0];
                uint32_t param1 = eventData[1];

                // Call the dispatcher's virtual function (vtbl index 1)
                DispatcherVTable* vtable = *(DispatcherVTable**)((uint8_t*)this + 0x08);
                vtable->handleEvent(param0, param1);

                // Advance head pointer (circular buffer)
                queue->head = (queue->head + 1) % queue->capacity;
                queue->count--;
            }

            // Free queue buffer and structure
            if (queue->buffer != nullptr) {
                delete[] queue->buffer; // FUN_009c8f10
            }
            delete queue; // FUN_009c8eb0

            currentNode = currentNode->next;
        }

        // Final cleanup
        postQueueCleanup(); // FUN_0065dc00
    }

private:
    void postQueueCleanup(); // Defined elsewhere
};
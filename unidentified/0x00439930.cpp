// FUN_00439930: NodeListManager::clearAll
class NodeListManager {
public:
    void clearAll();

private:
    void* m_internalData;          // +0x00: pointer to internal data block
    int m_activeCount;             // +0x04: number of active items (reset to 0 at end)
    int m_capacity;                // +0x08: capacity of the bucket array
    int m_totalCount;              // +0x10: total items (decremented per node)

    // Node structure (inferred)
    struct ListNode {
        void* field0;              // +0x00: unknown
        void* callbackData;        // +0x04: data passed to callback
        uint8_t pad[8];            // +0x08 to 0x0F
        void (*callback)(void*);   // +0x10: function pointer, called if callbackData != 0
        ListNode* next;            // +0x14: pointer to next node
    };
};

// Helper functions (declared elsewhere)
void destroyNextPointer(void* nextPtr);        // FUN_009c8f10
void freeListNode(ListNode* node);             // FUN_009c8eb0

void NodeListManager::clearAll() {
    // The internal data block at m_internalData contains a bucket array pointer at offset 0x14
    int* bucketArray = *(int**)((char*)m_internalData + 0x14);  // array of node pointers (first element is head)
    ListNode* current = (ListNode*)bucketArray[0];               // head of linked list

    while (current != nullptr) {
        // Save next node before processing
        ListNode* next = current->next;

        // Process the next pointer (unusual: calls helper on the pointer itself)
        destroyNextPointer((void*)current->next);

        // If there is a callback, invoke it
        if (current->callbackData != nullptr) {
            current->callback(current->callbackData);
        }

        // Free the current node
        freeListNode(current);

        // Decrement total count
        m_totalCount--;

        // Move to next node
        current = next;
    }

    // Zero out the entire bucket array
    for (uint32_t i = 0; i <= (uint32_t)m_capacity; i++) {
        bucketArray[i] = 0;
    }

    // Reset active count
    m_activeCount = 0;
}
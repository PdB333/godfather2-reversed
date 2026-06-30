// FUNC_NAME: MessageDispatcher::dispatchMessage
class MessageDispatcher {
public:
    // Offsets relative to this pointer
    // +0x5c: int* m_messageIDs
    // +0x60: int m_numMessageIDs
    // +0x68: HandlerEntry* m_handlers
    // +0x6c: int m_numHandlers

    void dispatchMessage(int messageID, void* messageData) {
        int* messageIDs = *(int**)((uint8_t*)this + 0x5c);
        int numIDs = *(int*)((uint8_t*)this + 0x60);
        uint32_t maskLow = 0;
        uint32_t maskHigh = 0;

        // Find the index of the messageID in the known message ID array
        if (numIDs != 0) {
            for (int idx = 0; idx < numIDs; idx++) {
                if (messageIDs[idx] == messageID) {
                    // Create a 64-bit mask with bit idx set
                    uint64_t bit = 1ULL << idx;
                    maskLow = (uint32_t)(bit & 0xFFFFFFFF);
                    maskHigh = (uint32_t)(bit >> 32);
                    break;
                }
            }
        }

        // Iterate over registered handler entries
        HandlerEntry* handlers = *(HandlerEntry**)((uint8_t*)this + 0x68);
        int numHandlers = *(int*)((uint8_t*)this + 0x6c);

        if (numHandlers != 0) {
            for (int idx = 0; idx < numHandlers; idx++) {
                HandlerEntry* entry = &handlers[idx];

                // Check if the handler's mask matches the message bit
                if ((entry->maskLow & maskLow) != 0 || (entry->maskHigh & maskHigh) != 0) {
                    // Call the handler's method at vtable offset 0x7c
                    void** vtable = *(void***)entry->handler;
                    void (*handlerFunc)(void* handler, void* data) = (void (*)(void*, void*))vtable[0x1F]; // 0x7c / 4 = 31
                    handlerFunc(entry->handler, messageData);
                }
            }
        }
    }

private:
    struct HandlerEntry {
        void* handler;    // +0x00: pointer to handler object (with vtable)
        uint32_t pad;     // +0x04: unknown/alignment
        uint32_t maskLow; // +0x08: lower 32 bits of subscription mask
        uint32_t maskHigh;// +0x0c: upper 32 bits of subscription mask
    };
};
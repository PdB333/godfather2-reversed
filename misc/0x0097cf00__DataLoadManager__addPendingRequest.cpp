// FUNC_NAME: DataLoadManager::addPendingRequest
// Address: 0x0097cf00
// Role: Adds a resource request to the pending queue if total pending count < 8 and request is not a duplicate.

// Assumed class managing asynchronous resource loading with multiple categories.
class DataLoadManager {
public:
    // Adds a request ID to the pending load queue.
    // Returns when the request cannot be added (queue full or duplicate or disabled).
    void addPendingRequest(uint32_t requestId);

private:
    // Offsets (relative to this):
    // +0x30: m_loadingCountA  // number of active loads in category A
    // +0x54: m_loadingCountB  // number of active loads in category B
    // +0x78: m_pendingCount    // number of items in the pending array
    // +0x9c: m_loadingCountC  // number of active loads in category C
    // +0x100: m_flags          // bit 2 = enable flag for this queue
    // +0x58: m_pendingRequests[8] // array of pending request IDs

    int32_t m_loadingCountA;    // at +0x30
    int32_t m_loadingCountB;    // at +0x54
    int32_t m_pendingCount;     // at +0x78
    int32_t m_loadingCountC;    // at +0x9c
    uint8_t m_flags;            // at +0x100 (only byte used)
    uint32_t m_pendingRequests[8]; // at +0x58

    // Checks if the given request ID is already in the queue.
    // Returns negative if not a duplicate, non‑negative otherwise.
    int32_t checkPendingDuplicate(uint32_t requestId); // FUN_0097b7b0

    // Global helper that starts processing the pending requests.
    // Called only when the queue was empty before adding.
    void processPendingQueue(); // FUN_0097c5a0
};

void DataLoadManager::addPendingRequest(uint32_t requestId) {
    // Check if the queue is enabled (bit 2 of flags byte)
    if ((m_flags >> 2) & 1) {
        // Total pending requests across all categories
        uint32_t totalPending = m_loadingCountA + m_loadingCountB + m_loadingCountC + m_pendingCount;
        if (totalPending < 8) {
            // If the request is not already in the queue (negative return)
            if (checkPendingDuplicate(requestId) < 0) {
                // Store the request in the next free slot
                m_pendingRequests[m_pendingCount] = requestId;
                m_pendingCount++;
                // If no other loads are active or pending, trigger processing
                if (totalPending == 0) {
                    processPendingQueue();
                }
            }
        }
    }
}
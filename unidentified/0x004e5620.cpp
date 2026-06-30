// EventManager::setEventData (0x004e5620)
// Sets event parameters from a 4-float data structure into a registered event object.
// Optionally triggers a notification callback if the fourth parameter is below a global threshold.
// Uses a hash map keyed by event ID to locate the target object.

struct EventHashNode {
    uint32_t eventId;          // +0x00
    void* pEventObject;        // +0x04 (object at least 0x30 bytes + 0x98 flag)
    EventHashNode* pNext;      // +0x08
};

struct EventTable {
    int32_t field_0x00;        // +0x00 (unknown)
    EventHashNode** ppBuckets; // +0x04
    uint32_t numBuckets;       // +0x08
};

// Global singleton manager (address 0x01223398)
extern void* g_pEventManager;

// Global threshold float (address 0x00e2e210)
extern float g_fEventThreshold;

// Forward declaration of notification function
void NotifyEvent(void* pContext, float* pEventData, void* pCallback, int, int, int);

void EventManager::setEventData(uint32_t eventId, float* pEventData)
{
    // Retrieve the hash table structure from the manager
    EventTable* pTable = *(EventTable**)((uint8_t*)g_pEventManager + 8);
    EventHashNode* pNode = pTable->ppBuckets[eventId % pTable->numBuckets];

    // Search for the node with matching eventId
    while (pNode != nullptr) {
        if (pNode->eventId == eventId)
            break;
        pNode = pNode->pNext;
    }

    // Event must be registered; if not found, fallback to null (crash-prone) – assume always found.
    if (pNode == nullptr)
        return;

    void* pObject = pNode->pEventObject;

    // Copy the four floats into the object at offsets 0x30–0x3c
    float* pDest = (float*)((uint8_t*)pObject + 0x30);
    pDest[0] = pEventData[0];
    pDest[1] = pEventData[1];
    pDest[2] = pEventData[2];
    pDest[3] = pEventData[3];

    // Mark the event data as set (byte flag at +0x98)
    *(uint8_t*)((uint8_t*)pObject + 0x98) = 1;

    // Check if the fourth component is at or below the global threshold
    if (pDest[3] <= g_fEventThreshold) {
        // Obtain the context object from the thread-local storage (FS segment)
        // This is a typical pattern for accessing the game's main manager.
        void* pContext = *(void**)(*(int32_t*)(**(int32_t**)(__readfsdword(0x2C) + 0x24) + 0x178));
        NotifyEvent(pContext, pDest, (void*)0x004eef20, 0, 0, 0);
    }
}
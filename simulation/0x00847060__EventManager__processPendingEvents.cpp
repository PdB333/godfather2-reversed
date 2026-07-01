// FUNC_NAME: EventManager::processPendingEvents

// Reconstructed from 0x00847060
// Processes pending events by looking up their hash in a global hash table,
// releasing any existing reference, then dispatching the event.

// External functions
void ReleaseObject(void* pObject); // FUN_00404c40
void DispatchEvent(uint eventHash, uint eventType, void* pContext); // FUN_004035f0

// Global event manager pointer (DAT_0122337c)
extern EventManagerGlobal* g_pEventManager;

// Structures (offsets documented)
struct HashNode {
    uint key;       // +0x00
    void* value;    // +0x04
    HashNode* next; // +0x08
};

struct EventEntry {
    uint eventId;   // +0x00 (unused here)
    void* data;     // +0x04 (unused here)
    uint hashKey;   // +0x08
};

struct EventManagerGlobal {
    HashNode** hashTable; // +0x50
    uint hashTableSize;   // +0x54
};

class EventManager {
public:
    EventEntry* m_pPendingEvents; // +0xF0
    uint m_nPendingEvents;        // +0xF4
    // +0x3C is used as context for DispatchEvent

    void processPendingEvents();
};

void EventManager::processPendingEvents() {
    EventEntry* pEntry = m_pPendingEvents;
    EventEntry* pEnd = pEntry + m_nPendingEvents;

    while (pEntry != pEnd) {
        uint hashKey = pEntry->hashKey;
        if (hashKey != 0) {
            // Hash table lookup
            uint bucketIndex = hashKey % g_pEventManager->hashTableSize;
            HashNode* pNode = g_pEventManager->hashTable[bucketIndex];
            while (pNode != nullptr) {
                if (pNode->key == hashKey) {
                    if (pNode->value != nullptr) {
                        ReleaseObject(pNode->value);
                    }
                    break;
                }
                pNode = pNode->next;
            }
            // Dispatch event with type 0x114 and context at this+0x3C
            DispatchEvent(hashKey, 0x114, reinterpret_cast<void*>(reinterpret_cast<uint>(this) + 0x3C));
        }
        pEntry++;
    }
}
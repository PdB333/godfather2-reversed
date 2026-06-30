// FUNC_NAME: ObjectManager::processPendingUpdates

// Reconstructed from address 0x006b3da0
// This function processes pending object addition and removal queues,
// then checks if all queues are empty to signal completion.

#include <cstdint>

// Forward declarations of called functions
extern uint32_t getCurrentNetworkId();                          // FUN_007914e0
extern void lockMutex();                                        // FUN_007915b0
extern void processAddPendingObject(uint32_t objId, void* manager, int flag);  // FUN_008c3a10
extern void processRemovePendingObject(uint32_t objId, void* manager);          // FUN_008c2e50
extern void signalPendingOperationsDone();                       // FUN_004086d0
extern void signalPendingOperationsPending();                     // FUN_00408680

// Globals referenced in the function
extern void* someGlobalVtable;        // PTR_LAB_00d5dbb0
extern uint32_t someGlobalData;       // DAT_0112a5a4

// Temporary scope guard (likely a critical section or sentinel)
struct ScopedGuard;
extern void ScopedGuard_construct(ScopedGuard* guard, void* vtable, uint32_t data, int zero, void* thisPtr); // FUN_00408a00

// Class with fields based on offsets from param_1
class ObjectManager {
public:
    // Offsets (relative to this):
    int32_t m_field_0x40;              // +0x40 – some identifier (e.g., local network ID)
    uint32_t* m_removeQueue;           // +0x84 – array of object IDs to remove
    int32_t m_removeQueueCount;        // +0x88 – number of pending removes
    uint32_t* m_addQueue;              // +0x9c – array of object IDs to add
    int32_t m_addQueueCount;           // +0xa0 – number of pending adds
    int32_t m_pendingCount1;           // +0xac – additional pending counter
    int32_t m_pendingCount2;           // +0xb8 – additional pending counter

    void processPendingUpdates();
};

void ObjectManager::processPendingUpdates() {
    bool bAddedAnything = false;

    // Process pending add queue (loop from end to start)
    for (int i = this->m_addQueueCount - 1; i >= 0; i--) {
        uint32_t objId = this->m_addQueue[i];
        uint32_t currentId = getCurrentNetworkId();
        if (currentId != this->m_field_0x40) {
            lockMutex();
            processAddPendingObject(objId, this, 1);
            bAddedAnything = true;
        }
    }

    // Process pending remove queue (loop from end to start)
    int removeCount = this->m_removeQueueCount;
    if (removeCount > 0) {
        for (int i = removeCount - 1; i >= 0; i--) {
            uint32_t objId = this->m_removeQueue[i];
            lockMutex();
            processRemovePendingObject(objId, this);
        }
    } else {
        // No remove queue, but if nothing was added, return early
        if (!bAddedAnything) {
            return;
        }
    }

    // Temporary scope guard object (initialized on stack)
    ScopedGuard guard;
    ScopedGuard_construct(&guard, &someGlobalVtable, someGlobalData, 0, this);

    // Check if all queues are empty
    if (this->m_removeQueueCount == 0 &&
        this->m_addQueueCount == 0 &&
        this->m_pendingCount1 == 0 &&
        this->m_pendingCount2 == 0)
    {
        signalPendingOperationsDone();
    } else {
        signalPendingOperationsPending();
    }
}
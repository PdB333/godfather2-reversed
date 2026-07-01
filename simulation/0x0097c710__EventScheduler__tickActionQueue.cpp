// FUNC_NAME: EventScheduler::tickActionQueue
// Address: 0x0097c710
// Role: Processes up to four priority queues of scheduled actions, decrementing a skip counter until it reaches zero, then executing the corresponding callback from the action handler table.
// Structure offsets (relative to 'this'):
//   +0x30: uint32_t m_highPriorityCount      // Number of entries in the high-priority queue (count-only)
//   +0x54: uint32_t m_mediumPriorityCount     // Number of entries in the medium-priority queue
//   +0x78: uint32_t m_lowPriorityCount        // Number of entries in the low-priority queue
//   +0x7c: ActionObject** m_dynamicQueueArray // Pointer array for the dynamic queue
//   +0x9c: uint32_t m_dynamicQueueCount       // Number of valid entries in m_dynamicQueueArray
//   +0xe4: CallbackTable* m_callbackTable      // Vtable-like pointer to an array of 4 function pointers (index 0=high,1=medium,2=low,3=dynamic)

#include <cstdint>

class ActionObject; // forward declaration

typedef void (__thiscall *ActionCallback)(void* thisPtr); // callback typedef for the vtable at +0xe4

struct CallbackTable {
    ActionCallback highCallback;    // +0x00
    ActionCallback mediumCallback;  // +0x04
    ActionCallback lowCallback;     // +0x08
    ActionCallback dynamicCallback; // +0x0C
};

class EventScheduler {
public:
    // Counts for the first three queues (no stored objects, just counters)
    uint32_t m_highPriorityCount;      // +0x30
    uint32_t m_mediumPriorityCount;    // +0x54 (offset between 0x30 and 0x54 is 0x24?) Remainder not used but structure padded.
    uint32_t m_lowPriorityCount;       // +0x78

    // Dynamic queue: array of pointers to ActionObject structures
    ActionObject** m_dynamicQueueArray; // +0x7c (pointer to array of pointers)
    uint32_t m_dynamicQueueCount;       // +0x9c

    // Vtable pointer for callbacks
    CallbackTable* m_callbackTable;     // +0xe4

    // External functions called (likely engine helpers)
    static int __stdcall isActionActive(uint32_t actionId); // FUN_008ff310
    static void __stdcall logAction();                       // FUN_008fdfb0
    static void* __stdcall getActionData();                  // FUN_00790610
    static const char* __stdcall getActionString();          // FUN_006b2160 (returns pointer to string)

    // Main processing method: skip 'skipCount' items across all queues, then invoke the matching callback.
    void tickActionQueue(int32_t skipCount);
};

// Action object structure (partial, based on code)
struct ActionObject {
    uint8_t pad_0x00[0x38];      // Unknown fields
    uint32_t m_actionDataId;     // +0x38 - passed to isActionActive
    uint8_t pad_0x3C[0xC4-0x3C]; // Padding to reach +0xC4
    uint32_t m_actionType;       // +0xC4 (compared to 9)
};

// Placeholder implementations for engine functions (assume no-ops or trivial)
int __stdcall EventScheduler::isActionActive(uint32_t actionId) {
    // In actual game: returns 0 if inactive, 1 if active
    return 0; // stub
}

void __stdcall EventScheduler::logAction() {
    // Stub
}

void* __stdcall EventScheduler::getActionData() {
    // Returns pointer to some data structure
    return nullptr;
}

const char* __stdcall EventScheduler::getActionString() {
    // Returns a string pointer; might be empty by default
    static const char* empty = ""; // corresponds to DAT_0120546e
    return empty;
}

void EventScheduler::tickActionQueue(int32_t skipCount) {
    // Process high-priority queue (count-only)
    for (uint32_t i = 0; i < m_highPriorityCount; ++i) {
        if (skipCount == 0) {
            if (m_callbackTable == nullptr) return;
            m_callbackTable->highCallback(this);
            return;
        }
        --skipCount;
    }

    // Process medium-priority queue
    for (uint32_t i = 0; i < m_mediumPriorityCount; ++i) {
        if (skipCount == 0) {
            if (m_callbackTable == nullptr) return;
            m_callbackTable->mediumCallback(this);
            return;
        }
        --skipCount;
    }

    // Process low-priority queue
    for (uint32_t i = 0; i < m_lowPriorityCount; ++i) {
        if (skipCount == 0) {
            if (m_callbackTable == nullptr) return;
            m_callbackTable->lowCallback(this);
            return;
        }
        --skipCount;
    }

    // Process dynamic queue (with stored objects)
    for (uint32_t i = 0; i < m_dynamicQueueCount; ++i) {
        ActionObject* obj = m_dynamicQueueArray[i];
        // Check if object type is 9 (special event?)
        if (obj->m_actionType == 9) {
            // Check if the action is active by its data ID
            if (isActionActive(obj->m_actionDataId) != 0) {
                logAction();
                void* data = getActionData();
                // Fall through to string check
                const char* str = (data != nullptr) ? *(char**)data : getActionString();
                if (str == nullptr) str = getActionString();
                if (*str != '\0') {
                    // If skipCount reaches 0 here, invoke dynamic callback
                    if (skipCount == 0) {
                        if (m_callbackTable == nullptr) return;
                        m_callbackTable->dynamicCallback(this);
                        return;
                    }
                    --skipCount;
                }
            }
        } else {
            // For non-type-9 objects, get the action string and check
            void* data = getActionString(); // Actually calls FUN_006b2160 which returns a string pointer
            const char* str = (data != nullptr) ? *(char**)data : getActionString();
            if (str == nullptr) str = getActionString();
            if (*str != '\0') {
                if (skipCount == 0) {
                    if (m_callbackTable == nullptr) return;
                    m_callbackTable->dynamicCallback(this);
                    return;
                }
                --skipCount;
            }
        }
    }
}
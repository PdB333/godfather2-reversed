// FUN_004293d0: EventManager::processEvent
// Function: 0x004293d0
// Role: Processes an event pair (two 64-bit identifiers) and dispatches to an action handler.
// param_1: Pointer to EventManager instance (this)
// param_2: Pointer to EventKey structure containing 2 QWORD identifiers

#include <cstdint>

struct EventKey {
    uint64_t id1; // +0x0
    uint64_t id2; // +0x8
};

// Forward declarations of called functions
int EventManager::findEventAction(const EventKey* key);
void* EventManager::getEventObject(); // returns some object based on this
void EventManager::executeAction(void* actionObject);

void EventManager::processEvent(void* param_1, const EventKey* param_2) {
    EventKey localKey; // copy of the key
    localKey.id1 = param_2->id1;
    localKey.id2 = param_2->id2;

    int actionIndex = EventManager::findEventAction(&localKey);
    if (actionIndex != 0) {
        void* actionObject = EventManager::getEventObject(); // param_1 is used implicitly via this
        if (actionObject != nullptr) {
            EventManager::executeAction(actionObject);
        }
    }
}
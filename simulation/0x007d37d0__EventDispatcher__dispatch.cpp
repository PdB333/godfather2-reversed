// FUNC_NAME: EventDispatcher::dispatch
#include <cstdint>

// 0x007d37d0: Handles incoming event data by dispatching to appropriate processing based on event type.
// Retrieves a handle from the resource manager (offset +0x58) and passes it to the event's response handler.
// EventData vtable: getType() at offset 0x0, processResponse() at offset 0x30.
class EventData {
public:
    virtual int32_t getType() = 0;          // vtable[0]
    // ... other virtual functions ...
    virtual void processResponse(uint32_t response) = 0; // vtable[12] (0x30 / 4)
};

class EventDispatcher {
public:
    // +0x58: pointer or handle to a resource manager / handle table
    uint32_t m_resourceManager; // offset 0x58

    void __thiscall dispatch(EventData* eventData);
};

// External function: resolves a handle from the manager with a specific type ID
extern uint32_t FUN_007ff880(uint32_t manager, int32_t id);

void __thiscall EventDispatcher::dispatch(EventData* eventData) {
    int32_t eventType = eventData->getType();

    if (eventType == -0x5d3bd48) {
        // Event type: some specific message (e.g., resource request?)
        uint32_t result = FUN_007ff880(this->m_resourceManager, 2);
        eventData->processResponse(result);
    }
    else if (eventType == -0xba4436) {
        // Event type: another message (e.g., alternative request)
        uint32_t result = FUN_007ff880(this->m_resourceManager, 1);
        eventData->processResponse(result);
        return;
    }

    return;
}
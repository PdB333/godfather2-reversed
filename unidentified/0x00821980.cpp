//Function address: 0x00821980
// Role: Sends an event (type=2, size=0x10, param=0) to the EventManager singleton

// FUNC_NAME: EventManager::sendEvent

struct EventData {
    int type;   // +0x00
    int size;   // +0x04
    int param;  // +0x08
};

class EventManager {
public:
    virtual void dispatchEvent(void* sender, EventData* event) = 0;
};

EventManager* GetEventManager(); // FUN_009c89b0

void __thiscall sendEvent(void* this_ptr) {
    EventManager* mgr = GetEventManager();
    EventData event;
    event.type = 2;
    event.size = 0x10;
    event.param = 0;
    mgr->dispatchEvent(this_ptr, &event);
}
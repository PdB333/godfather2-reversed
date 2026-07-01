// FUNC_NAME: Entity::sendEventToManager
// Address: 0x00829d50
// Role: Sends an event command (type=2, param1=0x10, param2=0) to the global EventManager.

// Forward declarations
class EventManager;
EventManager* GetEventManager(); // FUN_009c8f80

// Event data structure
struct EventData {
    int eventType; // +0x00, value 2
    int param1;    // +0x04, value 0x10
    int param2;    // +0x08, value 0
};

// Member function of Entity (or a derived class)
void Entity::sendEventToManager() {
    EventManager* mgr = GetEventManager();
    EventData evt;
    evt.eventType = 2;
    evt.param1 = 0x10;
    evt.param2 = 0;

    // Call the first virtual function of EventManager with this as observer.
    // Equivalent to mgr->vtable[0](this, &evt);
    typedef void (__thiscall *EventManagerMethod)(void* observer, EventData* data);
    uint32_t* vtable = *(uint32_t**)mgr;
    EventManagerMethod method = (EventManagerMethod)(*vtable);
    method(mgr, &evt); // Note: mgr is the this for the virtual call.
}
// FUNC_NAME: GameObject::sendEventToGlobalSystem
// Address: 0x004e0750
// Role: Sends an event with type=2, param1=0x10, param2=0 to the global EventSystem singleton.

struct Event {
    int type;   // +0x00
    int param1; // +0x04
    int param2; // +0x08
};

class EventSystem;

class GameObject {
public:
    void __thiscall sendEventToGlobalSystem(); // 0x004e0750
};

// Global singleton getter (likely returns a pointer to the EventSystem instance)
EventSystem* __cdecl GetEventSystem();

void __thiscall GameObject::sendEventToGlobalSystem() {
    EventSystem* sys = GetEventSystem(); // FUN_009c8f80
    Event evt;
    evt.type   = 2;   // Event type (e.g., MSG_TRIGGER, sound play, etc.)
    evt.param1 = 0x10; // Parameter (e.g., sound ID, duration)
    evt.param2 = 0;    // Flags or additional data
    // Virtual call to the first function in the vtable of EventSystem
    sys->handleEvent(this, &evt);
}
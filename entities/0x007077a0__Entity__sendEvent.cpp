// FUNC_NAME: Entity::sendEvent
// Function at 0x007077a0: Forwards an event (identified by hash 0x9cf94160) to a script handler component.
// The event hash likely corresponds to a specific game event name.
// Component pointer stored at +0x130 handles the event via its vtable entry at +0x44.

void __thiscall Entity::sendEvent(uint32_t param) {
    // +0x130: pointer to a script handler / event receiver component
    void* scriptHandler = *(void**)((uint8_t*)this + 0x130);
    if (scriptHandler != nullptr) {
        // Virtual function at vtable offset 0x44 handles events.
        // Signature: void handleEvent(uint32_t eventHash, uint32_t param)
        typedef void (__thiscall* EventHandler)(void*, uint32_t, uint32_t);
        EventHandler handler = *(EventHandler*)(*(uint32_t**)scriptHandler + 0x44 / 4);
        handler(scriptHandler, 0x9cf94160, param);
    }
}
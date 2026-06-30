// FUNC_NAME: EventManager::sendGameEvent
void __thiscall EventManager::sendGameEvent(void* thisPtr)
{
    // Local structure for event data
    struct EventData {
        uint32_t eventType;   // +0x00 (local_18) = 2
        uint32_t param1;      // +0x04 (local_14) = 0x80
        uint32_t param2;      // +0x08 (local_10) = 0
        uint32_t eventId;     // +0x0C (local_c)  = 0x10002
        uint32_t dataSize;    // +0x10 (local_8)  = 4
    };

    EventData event;  // stack allocated

    event.eventType = 2;
    event.param1 = 0x80;
    event.param2 = 0;
    event.eventId = 0x10002;
    event.dataSize = 4;

    // Call global event dispatcher (DAT_01205870)
    // The dispatcher is stored as a pointer to a function that takes (void* this, EventData*)
    // Note: only the eventId and dataSize fields are actually passed (starting from offset 0x0C)
    // The preceding fields might be part of a larger struct but are not used in the dispatch.
    (**(void(__thiscall**)(void*, uint32_t*))DAT_01205870)(thisPtr, &event.eventId);
}
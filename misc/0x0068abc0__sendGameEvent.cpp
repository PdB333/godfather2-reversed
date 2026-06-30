// FUNC_NAME: sendGameEvent
void sendGameEvent(void* targetObject, int param2, int param3)
{
    // Get the global event manager singleton
    void** eventManager = (void**)FUN_009c8f80(); // likely returns a pointer to a singleton with vtable

    // Build an event data structure on the stack
    struct EventData {
        int field0; // 3
        int field1; // 0
        int field2; // param2
        int field3; // 2
        int field4; // param3
    } eventData;

    eventData.field0 = 3;      // +0x00: event type or code
    eventData.field1 = 0;      // +0x04: flags
    eventData.field2 = param2; // +0x08: first data parameter
    eventData.field3 = 2;      // +0x0C: second data parameter
    eventData.field4 = param3; // +0x10: third data parameter

    // Call the first virtual function of the event manager (likely dispatchEvent)
    // The function takes (targetObject, &eventData)
    (**(void (__thiscall**)(void*, EventData*))*eventManager)(targetObject, &eventData);
}
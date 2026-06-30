// FUNC_NAME: EventManager::postEvent
void EventManager::postEvent(void* target, void* eventData)
{
    // Get the singleton EventManager instance
    EventManager* eventManager = (EventManager*)FUN_009c8f80();

    // Build a small event descriptor on the stack
    // Presumed struct layout: { int type; void* data; int flags; }
    struct EventDescriptor {
        int type;       // +0x00: event type identifier
        void* data;     // +0x04: event data pointer
        int flags;      // +0x08: flags (unused here)
    } eventDesc;

    eventDesc.type = 2;          // Event type constant (e.g., kEventTypeCustom)
    eventDesc.data = eventData;  // Data payload from parameter
    eventDesc.flags = 0;         // No flags

    // Calls the first virtual method of the EventManager (likely dispatchEvent)
    // through the vtable. The method takes (target, &eventDesc) as arguments.
    (eventManager->vtable[0])(target, &eventDesc);
}
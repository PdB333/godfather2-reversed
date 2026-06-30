// FUNC_NAME: EventManager::CreateEvent
void EventManager::CreateEvent(uint eventType, uint* data, uint extraData)
{
    // Allocate a 4-word event structure from the global event pool.
    // The callee (FUN_004550c0) returns a pointer to newly allocated memory.
    uint* eventData = (uint*)AllocateEventData();

    // +0x00: event type identifier
    eventData[0] = eventType;
    // +0x04: first data word (data[0])
    eventData[1] = data[0];
    // +0x08: second data word (data[1])
    eventData[2] = data[1];
    // +0x0C: extra payload
    eventData[3] = extraData;
}
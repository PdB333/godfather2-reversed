// FUNC_NAME: EventManager::dispatchEvent
void EventManager::dispatchEvent(uint param_1, uint param_2, uint param_3)
{
    // Local structure for event data (4 fields: eventId, data1, data2, callback)
    struct EventData {
        int eventId;      // +0x00
        int data1;        // +0x04
        int data2;        // +0x08
        void (*callback)(int); // +0x0C
    } eventData;

    eventData.eventId = 0;
    eventData.data1 = 0;
    eventData.data2 = 0;
    eventData.callback = nullptr;

    // Attempt to parse/retrieve event from parameters
    if (FUN_008bec50(param_1, param_2, param_3, &eventData) != 0) {
        // Process the event data
        FUN_004d3b50(&eventData);
        // Cleanup or further processing
        FUN_00938890(param_1, param_2, param_3, &eventData);
    }

    // If an event ID was set, invoke the callback (if any)
    if (eventData.eventId != 0) {
        eventData.callback(eventData.eventId);
    }
}
// FUNC_NAME: EventManager::sendEvent
void EventManager::sendEvent(int param1, uint8_t eventType, int param2) {
    struct EventData {
        int eventId;      // +0x00
        int param1;       // +0x04
        uint8_t eventType; // +0x08
        int param2;       // +0x0C
    };
    EventData eventData;
    eventData.eventId = 0;
    eventData.param1 = param1;
    eventData.eventType = eventType;
    eventData.param2 = param2;
    internalDispatchEvent(&eventData);
}
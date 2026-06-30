// FUNC_NAME: EventDispatcher::sendEvent
// Address: 0x00715340
// This function constructs a 12-byte event header from the current object state,
// then dispatches it with an event type and data parameter.
// The header buffer might contain a unique identifier, timestamp, or object reference.

class EventDispatcher {
public:
    // No specific fields known; likely includes a vtable pointer at +0x00.
    void sendEvent(uint32_t eventType, uint32_t eventData);
};

void __thiscall EventDispatcher::sendEvent(uint32_t eventType, uint32_t eventData) {
    char headerBuffer[12]; // Event header buffer (12 bytes)

    // Build the header from the object's internal state (e.g., serialize ID/time)
    // Calls: FUN_00712ff0
    serializeEventHeader(this, headerBuffer);

    // Process the event: header + type + data + this pointer
    // Calls: FUN_007151e0
    processEvent(headerBuffer, eventType, eventData, this);
}
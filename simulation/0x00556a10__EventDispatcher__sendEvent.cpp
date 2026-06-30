// FUNC_NAME: EventDispatcher::sendEvent
void __thiscall EventDispatcher::sendEvent(uint eventId, EventTarget* target, void* eventData) {
    // Call to internal setup function (likely verifies event type or preps data)
    FUN_00556ab0(0, 0, eventData, this, /* in_EAX - unknown */);

    // Set target object's event type flags at offset +0x2c
    // High bits (0xC0000000) indicate event pending/active, low 30 bits store event ID shifted right by 2
    *(uint*)(target + 0x2c) = (eventId >> 2) | 0xC0000000;

    // Debug/logging call
    FUN_0043b490();

    // Post event message to system (0x2001 = event message type, eventData, flags=0)
    FUN_009f01f0(0x2001, eventData, 0);
}
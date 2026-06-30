// FUNC_NAME: EventManager::fireEvent
void EventManager::fireEvent(uint32_t* eventData, int entity, uint64_t* payload) // param_1, param_2, param_3
{
    // Get thread-local storage for the event manager (TlsGetValue)
    TlsGetValue(DAT_01139810); // TLS index, result unused?

    // Allocate memory for event data (size 0x160, type 0x31)
    int allocPtr = FUN_00aa2680(0x160, 0x31);
    *(uint16_t*)(allocPtr + 4) = 0x160; // Store allocation size

    // Call a function to set up something from entity data at offset 0x10
    int eventSlot = FUN_009f0c70(*(uint32_t*)(entity + 0x10), &DAT_011397d0, 0); // +0x10 likely entity type/ID

    // Retrieve some internal pointer (unique per event?)
    uint32_t internalPtr = FUN_00559d40();

    uint32_t eventId = *eventData; // First dword of event data is event ID (or a reference)

    // Inform the entity about the event (mark as pending?)
    FUN_00556c80(entity, eventId, 1);

    // Set flags on the allocated slot: combine internalPtr/4 with 0xC0000000
    *(uint32_t*)(allocPtr + 0x2c) = (internalPtr >> 2) | 0xC0000000;

    // Debug/ trace call
    FUN_0043b490();

    // Send event message to system (event type 0x2001)
    FUN_009f01f0(0x2001, eventId, 0);

    // Copy payload data to the internal storage (at internalPtr + 0x4c)
    *(uint64_t*)(internalPtr + 0x4c) = payload[0];          // 8 bytes
    *(uint64_t*)(internalPtr + 0x54) = payload[1];          // 8 bytes
    *(uint32_t*)(internalPtr + 0x5c) = *(uint32_t*)(payload + 2); // 4 bytes (third 64-bit pair low part)

    // Send another event message (event type 0x2002) with the original event data pointer
    FUN_009f01f0(0x2002, eventData, 0);

    // Finalize / commit event queue
    FUN_009f01a0();
}
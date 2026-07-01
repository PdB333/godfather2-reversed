// FUNC_NAME: EventScheduler::createEvent

void EventScheduler::createEvent(uint eventId, uint* outMessage, uint sourceData, uint* guid, uint stringData, uint messageType)
{
    uint* eventObj;
    uint* factoryObj;
    uchar serializedData[48];
    uint guidCopy[4];
    uint msgHandle;
    uint allocSize;

    // Access thread-local storage (per-thread heap?)
    TlsGetValue(DAT_01139810);

    // Allocate a small reference-counted object (0x30 = 48 bytes)
    allocSize = 0x30;
    eventObj = (uint*)FUN_00aa2680(allocSize, 0x27);
    *(ushort*)((int)eventObj + 4) = allocSize;  // store allocation size

    // Retrieve a factory/manager instance (DAT_00ef3a9c is a global singleton pointer)
    factoryObj = (uint*)FUN_00a66df0(sourceData, _DAT_00ef3a9c);

    // Copy the 16-byte GUID from param_4 into local storage
    guidCopy[0] = guid[0];
    guidCopy[1] = guid[1];
    guidCopy[2] = guid[2];
    guidCopy[3] = guid[3];

    // Serialize the string/event data into the 48-byte buffer
    FUN_004b59d0(stringData, serializedData);

    // Register or allocate the message type (0x1f = 31, maybe message class index)
    msgHandle = FUN_00540c60(messageType, 0x1f, 0);

    // Access TLS again (maybe for another allocation context)
    TlsGetValue(DAT_01139810);

    // Allocate the main event/message object (0x160 = 352 bytes)
    allocSize = 0x160;
    eventObj = (uint*)FUN_00aa2680(allocSize, 0x31);
    *(ushort*)((int)eventObj + 4) = allocSize;

    // Create the event object from factory, using serialized data and message handle
    uint newEvent = FUN_009f0c70(factoryObj, serializedData, msgHandle);
    *outMessage = newEvent;

    // Post the event to the event system (eventId = 0x2001 likely "EVENT_CUSTOM" or similar)
    FUN_0043b490();
    FUN_009f01f0(0x2001, eventId, 0);

    // Decrement reference count of the factory object; if it reaches zero, destroy it
    if (*(short*)((int)factoryObj + 2) != 0) {
        *(short*)((int)factoryObj + 6) = *(short*)((int)factoryObj + 6) - 1;
        if (*(short*)((int)factoryObj + 6) == 0) {
            (**(code**)*factoryObj)(1);  // call virtual destructor with arg '1'
        }
    }

    return;
}
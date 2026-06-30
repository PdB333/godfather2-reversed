// FUNC_NAME: EventManager::sendEventWith16BytePayload
void __cdecl sendEventWith16BytePayload(int identifierPart1, int identifierPart2)
{
    struct EventData {
        uint32_t type;     // +0x00: event type identifier
        uint32_t dataSize; // +0x04: expected payload size (0x10 = 16 bytes)
        uint32_t flags;    // +0x08: flags (unused)
    };

    EventData eventData;
    eventData.type = 2;       // type 2: unknown specific event
    eventData.dataSize = 0x10; // 16-byte data block expected
    eventData.flags = 0;

    // Global pointer to engine singleton at DAT_01223410
    void* engineSingleton = *(void**)0x01223410;
    // Offset 0x2d4: function pointer for sending raw events
    typedef void (__cdecl *EventSendFunc)(int combinedId, EventData* data);
    EventSendFunc sendFunc = *(EventSendFunc*)((char*)engineSingleton + 0x2d4);
    sendFunc(identifierPart1 + identifierPart2, &eventData);
}
// FUNC_NAME: MessageSystem::createAndPostMessage
void MessageSystem::createAndPostMessage(const MessageData* data)
{
    // Get thread-local storage (likely for per-thread allocator)
    TlsGetValue(DAT_01139810);

    // Allocate a header block (0x50 bytes, tag 0x27)
    int headerPtr = poolAlloc(0x50, 0x27);
    *(uint16*)(headerPtr + 4) = 0x50; // store allocation size

    // Create data buffer from input (first dword is vtable, second is some resource ID)
    uint32* buffer = allocateDataBlock(*this, this->resourceId);

    // Copy input message data into the object's fields (offset +8, +16, +24)
    *(uint64*)(this + 2) = data->id1;     // +8
    *(uint64*)(this + 4) = data->id2;     // +16
    *(uint32*)(this + 6) = data->id3;     // +24

    // Allocate a larger buffer for internal data (0x160 bytes, tag 0x31)
    int dataPtr = poolAlloc(0x160, 0x31);
    *(uint16*)(dataPtr + 4) = 0x160;

    // Register the message with the engine (pass buffer, global identifier, and encoded pointer to data)
    uint32 encodedPtr = ((uint32)(this + 2) >> 2) | 0x40000000;
    uint32 msgHandle = registerMessageData(buffer, &DAT_011397d0, encodedPtr);
    this->msgHandle = msgHandle;

    // Decrement reference count on the header block; if it hits zero, call its destructor
    if ((*(uint16*)(buffer + 1) != 0) &&
        (*(uint16*)((int)buffer + 6) -= 1,
         *(uint16*)((int)buffer + 6) == 0))
    {
        (**(void (__thiscall**)(int))buffer)(1);
    }

    // Save vtable pointer before posting
    uint32 vtablePtr = *(uint32*)this;

    // Internal logging/trail
    debugTrailLog();

    // Post two messages to the event queue (start and finish?)
    postMessage(0x2001, vtablePtr, 0);
    postMessage(0x2002, this, 0);
}
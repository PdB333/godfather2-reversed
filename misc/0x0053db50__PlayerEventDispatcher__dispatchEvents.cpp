// FUNC_NAME: PlayerEventDispatcher::dispatchEvents
// Function at 0x0053db50: Dispatches a 16-byte data block (likely transform or event payload) to two registered handlers per player index.
// The handlers are stored in global arrays indexed by a player ID (DAT_0121bf30) * 0x1b (27 bytes stride - possibly struct size).
// Each handler receives 16 bytes from the first half (0-15) and second half (16-31) of the 'this' object's data.
// FUN_0060add0 is the actual callback function (signature: void(*)(void* context, void* handler, void* data))

void __thiscall PlayerEventDispatcher::dispatchEvents(void)
{
    // Global handles
    int playerIndex = *(int*)0x0121bf30;              // Current player slot index (0-3?)
    void* context = *(void**)0x0121be9c;              // Engine context / system manager
    void* gDispatcherArrayA = (void*)0x01198e88;      // Base of first handler array
    void* gDispatcherArrayB = (void*)0x01198e8c;      // Base of second handler array (4 bytes after A)

    // Local copy of 16 bytes (first part of this's event data)
    // In actual code, 'this' is passed in ESI and referenced via unaff_ESI
    undefined4 eventData[4];                          // 16 bytes

    // Test first handler: check if non-null
    if (*(unsigned char*)(gDispatcherArrayA + playerIndex * 0x1b) != 0)
    {
        // Copy first 4 dwords (offset 0) from this into local buffer
        eventData[0] = *(undefined4*)this;           // offset +0x00
        eventData[1] = *(undefined4*)(this + 4);     // offset +0x04
        eventData[2] = *(undefined4*)(this + 8);     // offset +0x08
        eventData[3] = *(undefined4*)(this + 12);    // offset +0x0C

        // Call dispatch with first handler
        FUN_0060add0(context, *(void**)(gDispatcherArrayA + playerIndex * 0x1b), eventData);
    }

    // Test second handler (note: different global array but same index)
    if (*(unsigned char*)(gDispatcherArrayB + playerIndex * 0x1b) != 0)
    {
        // Copy next 4 dwords (offset 16) from this into local buffer
        eventData[0] = *(undefined4*)(this + 16);    // offset +0x10
        eventData[1] = *(undefined4*)(this + 20);    // offset +0x14
        eventData[2] = *(undefined4*)(this + 24);    // offset +0x18
        eventData[3] = *(undefined4*)(this + 28);    // offset +0x1C

        FUN_0060add0(context, *(void**)(gDispatcherArrayB + playerIndex * 0x1b), eventData);
    }

    return;
}
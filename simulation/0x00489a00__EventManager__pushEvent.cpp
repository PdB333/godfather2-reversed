// FUNC_NAME: EventManager::pushEvent

void __thiscall EventManager::pushEvent(int this, int eventData) {
    bool isValid;
    int eventPtr;
    int *bufferPtr;

    // Check if the event at this+0x20 is valid to enqueue
    isValid = FUN_00489a80((undefined4 *)(this + 0x20), eventData);
    if (isValid) {
        eventPtr = *(int *)(this + 0x20);                // +0x20: event object pointer
        bufferPtr = (int *)(DAT_01206880 + 0x14);        // Global write buffer ptr (+0x14 from global base)
        **(int **)(DAT_01206880 + 0x14) = &PTR_LAB_01123c60; // Store vtable or type marker
        *bufferPtr = *bufferPtr + 4;                     // Advance buffer
        *(int *)*bufferPtr = eventPtr;                   // Write event pointer
        *bufferPtr = *bufferPtr + 4;                     // Advance buffer again
    }
}
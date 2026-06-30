// FUNC_NAME: EventManager::dispatchToListeners
void __thiscall EventManager::dispatchToListeners(int eventId, void* eventData) {
    // this +0x34: pointer to array of ListenerEntry (8 bytes each)
    // this +0x38: number of listeners (unsigned int)
    unsigned int count = *(unsigned int*)(this + 0x38);
    if (count == 0) return;

    // ListenerEntry structure: [4 bytes unknown, 4 bytes pointer to ListenerObject]
    // Each ListenerObject has an event ID at offset 0x40
    int base = *(int*)(this + 0x34);
    for (unsigned int i = 0; i < count; i++) {
        // Each entry starts at base + 4 + i*8; the second dword is the listener pointer
        int listenerObj = *(int*)(base + 4 + i * 8);
        if (*(int*)(listenerObj + 0x40) == eventId) {
            // Call the static handler with the event data
            FUN_006b5850(eventData);
        }
    }
}
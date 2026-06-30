// FUNC_NAME: Notifier::notify
// Address: 0x0051c530
// Sets a current notification parameter and broadcasts to all registered listeners via vtable method at offset 0x40.

// Assumed structure: Notifier
// +0x80: short listenerCount
// +0xac: int currentNotificationParam (or eventId)
// +0xf4: Array of ListenerEntry (20 bytes each), first 4 bytes = pointer to listener object

struct ListenerEntry {
    void* listener; // +0x00
    // remaining 16 bytes unknown
};

void __thiscall Notifier::notify(int param) {
    // Store the notification parameter
    this->currentNotificationParam = param;

    // Iterate over the listener list
    short count = this->listenerCount;
    if (count > 0) {
        ListenerEntry* entries = (ListenerEntry*)((char*)this + 0xf4);
        for (int i = 0; i < count; i++) {
            if (entries[i].listener != nullptr) {
                // Call virtual function at vtable offset 0x40 (method index 16)
                // This function receives the param as argument (likely a notification ID or data)
                void (*listenerMethod)(int) = *(void (**)(int))(*(int*)entries[i].listener + 0x40);
                listenerMethod(param);
            }
        }
    }
}
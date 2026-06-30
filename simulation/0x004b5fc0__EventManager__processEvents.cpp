// FUNC_NAME: EventManager::processEvents
// Address: 0x004b5fc0
// Role: Sends start and stop events to registered listeners (likely for audio/visual effects)
// Uses: this->m_listenerCount (offset +0x1c) as iteration count
// Called with eventID parameter to trigger start events, then always triggers stop events

__thiscall void EventManager::processEvents(int eventID) {
    int listenerCount = *(int*)(this + 0x1c); // Number of registered listeners

    if (listenerCount == 0) {
        return; // No listeners, nothing to do
    }

    if (eventID != 0) {
        // Send start event (0x2001) to all listeners, calling a per-listener callback beforehand
        int remaining = listenerCount;
        if (remaining != 0) {
            do {
                executeCallback(); // Internal callback (FUN_0043b490)
                sendMessage(0x2001, eventID, 0); // Notify start event (FUN_009f01f0)
                remaining--;
            } while (remaining != 0);
        }
    }

    // Always send stop event (0x2005) to all listeners
    for (int i = listenerCount; i != 0; i--) {
        sendMessage(0x2005, (int)this, 0); // Notify stop event with this as sender
    }
}
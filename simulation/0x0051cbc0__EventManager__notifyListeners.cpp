// FUNC_NAME: EventManager::notifyListeners
// Function address: 0x0051cbc0
// Role: Iterates over registered listeners and calls a virtual method on active ones.
// Structure: this+0x80 = count (short), this+0xf4 = array of ListenerEntry (20 bytes each)
// ListenerEntry: +0x00 flags (int), +0x04 listenerPtr (int*), +0x08..+0x13 unused (3 ints)
// Listener's vtable+0x44 is the callback method taking two parameters.

void __thiscall EventManager::notifyListeners(EventManager* this, undefined4 eventData1, undefined4 eventData2)
{
    int i;
    int* entryPtr; // points to listenerPtr field of each entry

    i = 0;
    if (0 < *(short*)((int)this + 0x80)) {
        entryPtr = (int*)((int)this + 0xf4);
        do {
            // Check flags at entryPtr[-1] (offset -4 from listenerPtr) for bit 0x40000 (active)
            if (((entryPtr[-1] & 0x40000U) != 0) && (*entryPtr != 0)) {
                // Call virtual function at vtable+0x44 on the listener object
                (**(code**)(**(int**)*entryPtr + 0x44))(eventData1, eventData2);
            }
            i = i + 1;
            entryPtr = entryPtr + 5; // each entry is 5 ints (20 bytes)
        } while (i < *(short*)((int)this + 0x80));
    }
    return;
}
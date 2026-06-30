// FUNC_NAME: EventManager::NotifyListeners
void EventManager::NotifyListeners(uint param1, uint param2)
{
    // this+0x10: pointer to listener list container
    ListenerContainer* container = *(ListenerContainer**)((char*)this + 0x10);
    // this+0x0C: processing flag (clear before iteration)
    *(int*)((char*)this + 0x0C) = 0;
    // container+0x08: pointer to array of listener pointers
    ListenerEntry** entryPtr = *(ListenerEntry***)((char*)container + 8);

    // iterate over array until null pointer
    for (ListenerEntry* entry = *entryPtr; entry != nullptr; entry = *entryPtr)
    {
        // call virtual function at vtable index 2 (offset +8)
        // pass (param1, param2, 0, entry->objectPtr, entry->userData)
        (this->vtable[2])(param1, param2, 0, *(uint*)entry, *(uint*)((char*)entry + 4));
        // advance to next entry pointer in array
        entryPtr++;
    }
}
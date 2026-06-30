// FUNC_NAME: EventManager::resetListenerList
void EventManager::resetListenerList()
{
    // Check if there are any entries (count at +0x500)
    if (*(int*)(this + 0x500) == 0)
    {
        *(int*)(this + 0x500) = 0;
        return;
    }

    // If count is 1, just clear the count
    if (*(int*)(this + 0x500) == 1)
    {
        *(int*)(this + 0x500) = 0;
        return;
    }

    // For each entry (except the first? but loop runs from 0 to count-2)
    // Each entry is 40 bytes (10 * sizeof(int)) starting at +0x20
    int* pEntryCallback = (int*)(this + 0x20);  // +0x20: function pointer
    for (unsigned int i = 0; i < *(int*)(this + 0x500) - 1; i++)
    {
        // Check if the listener object is valid (at offset -12 from callback pointer)
        void* pObj = (void*)*(pEntryCallback - 3);  // +0x14: object pointer
        if (pObj != 0)
        {
            // Call the callback (function pointer at +0x20) with the object
            ((void (*)(void*))(*pEntryCallback))(pObj);
        }

        // Mark that we are clearing (set flag at +0x0 to 1)
        *(char*)(this) = 1;   // +0x0: clearing flag

        // Call unknown function (likely a yield or memory barrier)
        FUN_004d9500(0);

        // Clear all entry fields
        *(int*)(pEntryCallback - 3) = 0;   // +0x14: object pointer
        *(int*)(pEntryCallback - 2) = 0;   // +0x18: unknown
        *(int*)(pEntryCallback - 1) = 0;   // +0x1C: unknown
        *pEntryCallback = 0;               // +0x20: callback
        *(char*)(pEntryCallback + 1) = 0;  // +0x24: active flag

        // Move to next entry (40 bytes forward)
        pEntryCallback += 10; // 10 * 4 = 40
    }

    // Reset count to 0
    *(int*)(this + 0x500) = 0;
    return;
}
// FUNC_NAME: SimObject::registerForEvent
// Function address: 0x004a8900
// Purpose: Registers this SimObject with a global event manager for a notification ID (param_1).
// The object is added to a dynamic array of (object*, notificationId) pairs, resizing the array if needed.
// Only proceeds if the object's bit 1 at offset +0x30 is not set (e.g., not already registered).

void __thiscall SimObject::registerForEvent(int notificationId)
{
    // Global event manager singleton (example: g_eventManager)
    struct EventManager* mgr = (struct EventManager*)DAT_0122344c; // +0x00

    // Check if this object is allowed to be registered (bit 1 at +0x30)
    if ((*(uint*)(this + 0x30) >> 1 & 1) == 0)
    {
        int count = *(int*)(mgr + 0x50);    // current number of registrations
        int capacity = *(int*)(mgr + 0x54); // allocated capacity

        // Resize the array if count reaches capacity
        if (count == capacity)
        {
            if (capacity == 0)
                capacity = 1;
            else
                capacity *= 2;
            // Reallocate the data array (function at 0x004555f0 takes new capacity)
            FUN_004555f0(capacity); // likely EventManager::resizeArray(int newCapacity)
        }

        // Get pointer to the new slot (array of 8-byte pairs)
        int* dataArray = *(int**)(mgr + 0x4c); // base pointer
        int* slot = dataArray + count * 2;      // each pair is two ints
        *(int*)(mgr + 0x50) = count + 1;        // increment count

        slot[0] = this;          // store object pointer
        slot[1] = notificationId; // store notification ID/callback key
    }
}
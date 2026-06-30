// FUNC_NAME: CEventManager::fireEvent
// Function address: 0x004a21d0
// Iterates over an array of 12 callback slots at offset 0x88,
// calling the virtual function at vtable+4 on each non-null object with (arg, 1).
// Array stride is 12 bytes (0xC), with a pointer to the target object at the start of each slot.
void __thiscall CEventManager::fireEvent(int arg)
{
    // Pointer to array of 12 callback entries (each 12 bytes) at offset 0x88
    int* pEntry = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x88);
    for (int i = 0; i < 12; ++i)
    {
        // First 4 bytes of entry: pointer to an object (or null)
        int* pObj = reinterpret_cast<int*>(*pEntry);
        if (pObj != 0)
        {
            // vtable is at start of object; second function (vtable+4) is the callback
            void (*callback)(void*, int, int) = reinterpret_cast<void (*)(void*, int, int)>(*(reinterpret_cast<int*>(*pObj) + 1));
            callback(pObj, arg, 1);
        }
        pEntry += 3; // move to next entry (3 ints = 12 bytes)
    }
}
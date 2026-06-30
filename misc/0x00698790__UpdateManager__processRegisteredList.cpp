// FUNC_NAME: UpdateManager::processRegisteredList

// This function iterates over a global array of registered object pointers,
// calling the virtual update() method (vtable offset +0x08) on each.
void processRegisteredList(void)
{
    // Global array begin/end pointers (likely set during registration)
    void** listStart = (void**)DAT_01129f8c;  // Start of array of object pointers
    void** listEnd   = (void**)DAT_01129f90;  // One past last valid entry

    for (void** current = listStart; current != listEnd; ++current)
    {
        // Retrieve object pointer from array
        void* object = *current;

        // Call virtual function at vtable offset 8 (typically "update" or "tick")
        // Cast object to a base class with virtual method table
        (**(void (__thiscall**)(void*))(*((int*)object) + 8))(object);
    }
}
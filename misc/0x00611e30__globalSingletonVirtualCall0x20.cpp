// FUNC_NAME: globalSingletonVirtualCall0x20
// Address: 0x00611e30
// This function checks a global singleton pointer and calls its virtual function at vtable offset 0x20.
void globalSingletonVirtualCall0x20()
{
    // DAT_012058e8 is a pointer to a singleton object (e.g., InputManager, ControllerManager, etc.)
    int* globalSingleton = (int*)DAT_012058e8;  // Actually an object pointer with a vtable
    if (globalSingleton != (int*)0)
    {
        // Get vtable pointer from the object's first member
        int* vtable = (int*)*globalSingleton;
        // vtable entry at offset 0x20 (8th function pointer, assuming 4-byte entries)
        void (*func)(void*) = (void (*)(void*))(*(vtable + 0x20 / sizeof(int)));
        // Call the virtual function with the object as 'this'
        func((void*)globalSingleton);
    }
}
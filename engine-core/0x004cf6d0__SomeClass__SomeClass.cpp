// FUNC_NAME: SomeClass::SomeClass

// Constructor for SomeClass. Takes a byte flag indicating whether to call a virtual cleanup function.
// Calls base class constructor first, then optionally calls a virtual function on a global manager object.
// The global manager's vtable is stored at offset 0x2d4 from g_globalManager.
// The virtual function at vtable offset 4 is invoked with this and 0 if allocFlag's bit 0 is set.
// This pattern is typical for placement new constructors where the flag indicates if the object was heap-allocated.

void __thiscall SomeClass::SomeClass(SomeClass* this, byte allocFlag)
{
    // Call base class constructor
    BaseClass::BaseClass(this);

    // If the allocation flag has bit 0 set, call a virtual cleanup function on the global manager
    if ((allocFlag & 1) != 0)
    {
        // Get vtable pointer from global manager at offset 0x2d4
        void** vtable = *(void***)((char*)g_globalManager + 0x2d4);
        // Call the second virtual function (offset 4) with this and 0
        ((void (__thiscall*)(SomeClass*, int))vtable[1])(this, 0);
    }
}
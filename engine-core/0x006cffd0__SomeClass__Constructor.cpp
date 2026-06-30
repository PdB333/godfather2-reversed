// FUNC_NAME: SomeClass::Constructor
// Address: 0x006cffd0
// Role: Constructor for a class with size approximately 400 bytes (0x190).
// Calls a base constructor (FUN_006cfb00), then conditionally deallocates the object
// if the 'constructorFlags' parameter has bit 0 set (likely a placement-delete guard).
// The operator delete at FUN_0043b960 is called with size 400.

// Note: 'this' is param_1, 'constructorFlags' is param_2.
// The size 400 corresponds to the total object size, including base class members.

__thiscall SomeClass* SomeClass::SomeClass(void* this, byte constructorFlags)
{
    // Call base class constructor (FUN_006cfb00)
    baseConstructor(this);

    // If the low bit of constructorFlags is set, delete the allocated memory
    // (commonly used in MSVC to handle constructor failure in placement new scenarios)
    if ((constructorFlags & 1) != 0)
    {
        operatorDelete(this, 400); // FUN_0043b960
    }

    return this;
}
// FUNC_NAME: SomeClass::Constructor
// Function address: 0x008cd2e0
// Role: Constructor for a class that inherits a base class. The second parameter (byte)
//       is a flag that controls whether a deallocation/cleanup function is invoked.
//       This pattern is typical of EA EARS engine constructors with a "shouldDelete" flag.

void* __thiscall SomeClass::Constructor(void* thisObj, byte flag)
{
    // Call base class constructor (located at 0x008cd1e0)
    ((void (__thiscall*)(void*))0x008cd1e0)(thisObj);

    // If flag has bit 0 set, perform additional cleanup or deallocation
    if (flag & 1)
    {
        ((void (__thiscall*)(void*))0x009c8eb0)(thisObj);
    }

    // Return the constructed object (typical in this calling convention)
    return thisObj;
}
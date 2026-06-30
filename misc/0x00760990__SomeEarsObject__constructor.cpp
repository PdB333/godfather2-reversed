// FUNC_NAME: SomeEarsObject::constructor
// Address: 0x00760990
// This function is a constructor with a flag (param_2) that controls additional initialization.
// FUN_007604a0 is the base class constructor.
// FUN_00624da0 is called conditionally (likely for placement new handling).
__thiscall SomeEarsObject* SomeEarsObject::constructor(SomeEarsObject* this, byte flags)
{
    // Call base class constructor (initializes inherited members)
    baseConstructor(this); // FUN_007604a0
    // If the lowest bit is set, perform extra setup (e.g., mark as heap-allocated or configure something)
    if (flags & 1)
    {
        extraInit(this); // FUN_00624da0
    }
    return this;
}
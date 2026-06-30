// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor (FUN_00480150)
    // Typically initializes base class members
    FUN_00480150();

    // If bit 0 of flags is set, call virtual function at vtable offset 0x04 (first virtual method after vtable base?)
    // The vtable is obtained via global singleton + 0x2d4 (likely a class static vtable pointer)
    if ((flags & 1) != 0)
    {
        // Dereference global at DAT_01223410 + 0x2d4 to get vtable pointer, then call vtable[1] (offset 4) with this and 0
        (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
        // This call often performs additional initialization, e.g., setting a flag or calling a virtual "initialize" method
    }

    return this;
}
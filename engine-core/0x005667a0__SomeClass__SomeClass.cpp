// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x005667a0
// Role: Constructor for SomeClass. Calls base constructor and optionally initializes additional data based on flag.

undefined4 __thiscall SomeClass::SomeClass(SomeClass* this, byte flags)
{
    // Call base class constructor (likely at 0x005667d0)
    FUN_005667d0();

    // If the lowest bit of flags is set, perform additional initialization
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}
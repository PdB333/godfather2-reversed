// FUNC_NAME: SomeClass::constructor
// Function address: 0x007dcff0
// Role: Constructor for SomeClass, with optional memory initialization of size 0x110

undefined4 __thiscall SomeClass::constructor(SomeClass* this, byte flags)
{
    // Call base class constructor or common initialization
    FUN_007dcd30();

    // If the lowest bit of flags is set, perform additional initialization
    // (likely allocate or initialize a buffer of size 0x110)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x110);
    }

    return this;
}
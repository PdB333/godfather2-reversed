// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flag)
{
    // Call base class constructor or common initialization
    FUN_008e6120();
    // If the lowest bit of flag is set, perform additional initialization (or cleanup?)
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return this;
}
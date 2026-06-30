// FUNC_NAME: SomeClass::constructor
// Function at 0x005d85e0: Constructor with optional initialization flag
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
    // Call the base/common initialization (FUN_005d8600)
    SomeClass::initializeBase(this);
    // If flag bit 0 is set, perform additional setup (FUN_009c8eb0)
    if (flags & 1) {
        SomeClass::initializeExtended(this);
    }
    return (undefined4)this;
}
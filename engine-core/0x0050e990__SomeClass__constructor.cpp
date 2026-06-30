// FUNC_NAME: SomeClass::constructor
// Address: 0x0050e990
// Role: Initializes SomeClass instance, calls base class init, and optionally extra init based on flags.
undefined4 __thiscall SomeClass::initialize(byte flags)
{
    this->baseInitialize();  // Likely calls base class constructor (FUN_0050f0d0)
    if ((flags & 1) != 0) {
        this->extraInitialize();  // Additional init when bit 0 set (FUN_009c8eb0)
    }
    return this;
}
// FUNC_NAME: SomeClass::~SomeClass
undefined4 __thiscall SomeClass::~SomeClass(SomeClass *this, byte flags)
{
    // Call base class destructor (FUN_006aace0) on this
    BaseClass::~BaseClass(this);

    // If the "deleting destructor" flag is set (bit 0), deallocate memory of size 0x3CC
    if ((flags & 1) != 0) {
        // Custom operator delete with size (FUN_0043b960)
        operator delete(this, 0x3CC);
    }

    return this; // Return this pointer (compiler pattern for destructor chaining)
}
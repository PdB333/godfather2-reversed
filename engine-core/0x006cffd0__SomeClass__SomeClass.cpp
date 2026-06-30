//FUNC_NAME: SomeClass::SomeClass
// Function address: 0x006cffd0
// Role: Constructor for SomeClass, optionally allocates a 400-byte buffer if flag bit 0 is set.

__thiscall SomeClass::SomeClass(byte flags)
{
    // Call base class constructor or common initialization
    this->initCommon(); // FUN_006cfb00

    // If the lowest bit of flags is set, allocate/initialize a 400-byte buffer
    if (flags & 1)
    {
        this->initBuffer(400); // FUN_0043b960(this, 400)
    }

    return this;
}
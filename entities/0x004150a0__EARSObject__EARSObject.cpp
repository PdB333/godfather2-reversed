// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004150a0
// Constructor for a base EARS object. Calls base initializer, then conditionally
// invokes a cleanup/release routine based on a flag bit.
EARSObject* __thiscall EARSObject::EARSObject(byte flags)
{
    // Call base class constructor or common initialization (0x00415130)
    FUN_00415130();

    // If the lowest bit of flags is set, perform additional cleanup/destruction
    // (likely a placement new or deferred destroy mechanism)
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);  // +0x00: this pointer
    }

    return this;
}
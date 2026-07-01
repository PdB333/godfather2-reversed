// FUNC_NAME: SomeObject::SomeObject
// Address: 0x008d3d60 - Constructor with optional second initialization call based on flags.
// param_1 (this) - pointer to object being constructed.
// param_2 - flags byte; if bit 0 is set, calls additional setup/cleanup function.

undefined4 __thiscall SomeObject::SomeObject(undefined4 this, byte flags)
{
    // Call base or common initialization.
    FUN_008d3cf0();

    // If the low bit of flags is set, perform additional setup.
    if ((flags & 1) != 0)
    {
        // Likely calls a registration, reference count increment, or cleanup function.
        FUN_009c8eb0(this);
    }

    // Return the constructed object.
    return this;
}
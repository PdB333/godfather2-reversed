// FUNC_NAME: EARSObject::constructor
// Address: 0x0064d590
// Role: Constructor for an EARS object. Calls base initialization and optionally a post-construction function based on flags.
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
    // Call base class initializer (likely sets vtable and zeroes members)
    EARSObject::baseInitialize(this);
    // If the lowest bit of flags is set, perform additional setup (e.g., register with manager)
    if ((flags & 1) != 0) {
        EARSObject::postInitialize(this);
    }
    return this;
}
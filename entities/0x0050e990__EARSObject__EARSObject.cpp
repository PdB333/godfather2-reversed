// FUNC_NAME: EARSObject::EARSObject
// Constructor for EARSObject at 0x0050e990.
// Calls base initialization (likely base class constructor) and optionally extra setup if bit 0 of flags is set.
EARSObject::EARSObject(unsigned char flags)
{
    // Call base class constructor (unconditional)
    baseConstructor();
    // If bit 0 is set, perform additional initialization (e.g., allocate resources or set up vtable)
    if (flags & 1)
    {
        extraInitialization();
    }
}
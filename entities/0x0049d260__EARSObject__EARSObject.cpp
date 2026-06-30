// FUNC_NAME: EARSObject::EARSObject
// Reconstructed constructor for EARSObject (EA EARS engine base object)
// param_2 is an initialization flag: bit 0 triggers additional construction steps
EARSObject* __thiscall EARSObject::EARSObject(byte initFlag)
{
    // Call base class constructor (FUN_0049c640)
    BaseClass::BaseClass(); // Base class initialization (e.g., zero memory, set defaults)

    // If bit 0 is set, finalize object construction (FUN_009c8eb0)
    // This may set up vtable pointers, register with manager, etc.
    if (initFlag & 1)
    {
        this->finalizeConstruction(); // Additional initialization step
    }

    return this;
}
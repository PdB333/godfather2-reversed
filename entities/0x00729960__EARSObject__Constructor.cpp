// FUNC_NAME: EARSObject::Constructor
// Function address: 0x00729960
// EARS object constructor with optional registration flag.
// Calls base initialization first, then if param_2 bit 0 is set,
// registers the object with the appropriate manager via FUN_009c8eb0.

undefined4 __thiscall EARSObject::Constructor(byte registrationFlag)
{
    // Base class initialization (e.g., zeroing fields, setting defaults)
    EARSObject::baseConstructor();  // FUN_00729560

    // If the lowest bit is set, register this object with the manager
    if ((registrationFlag & 1) != 0) {
        EARSObject::registerWithManager(this);  // FUN_009c8eb0
    }

    return this;
}
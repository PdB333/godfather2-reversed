// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x006a8b90
// Constructor for a base EARS engine object.
// Calls base class constructor (FUN_006a8530) and optionally performs extra initialization
// based on the 'initialize' flag (param_2 & 1).

undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte initialize)
{
    // Call base constructor (presumably some common initialization)
    FUN_006a8530();

    // If the initialization flag (bit 0) is set, perform additional setup.
    // This might be used for heap-allocated objects requiring extra registration.
    if ((initialize & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}
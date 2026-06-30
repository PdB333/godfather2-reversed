// FUNC_NAME: EARSObject::constructor
// Function address: 0x006a2640
// This function appears to be a constructor that calls a base initializer (FUN_00ab72a0) and optionally calls a cleanup or secondary initializer (FUN_009c8eb0) if the low bit of the flag is set.
// Returns the this pointer.

EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte flag)
{
    // Base class initialization or internal setup
    FUN_00ab72a0(); // Unknown base initializer (likely virtual base constructor or common init)

    if (flag & 1)
    {
        // Optionally call a cleanup or additional initialization based on flag
        FUN_009c8eb0(this); // Unknown function, e.g., resetting prior state
    }

    return this;
}
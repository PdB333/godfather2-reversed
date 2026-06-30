// FUNC_NAME: EARSObject::constructor
// Function at 0x006e6380: Constructor for EARSObject with a byte flag.
// The flag (shouldDestroy) controls whether a destructor-style cleanup (FUN_009c8eb0) is called after initialization.
// This pattern may be used for reinitialization or placement new handling.
undefined4 __thiscall EARSObject::constructor(EARSObject *this, byte shouldDestroy)
{
    // Internal initialization (likely base class or member initializer)
    initialize(); // FUN_006e5af0

    // If the low bit is set, perform an additional cleanup/destructor-like call
    if ((shouldDestroy & 1) != 0) {
        destroy(); // FUN_009c8eb0
    }

    // Return the this pointer (common in EA engine constructors)
    return this;
}
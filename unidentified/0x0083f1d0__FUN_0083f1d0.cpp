// FUNC_NAME: SomeEarsObject::initialize
// Address: 0x0083f1d0
// Role: Constructor with optional allocation based on flag. Calls base init, then if bit0 of flags is set, allocates or initializes a 0x148 (328 bytes) sub-block via FUN_0043b960.
// This: 'this' pointer (implicit)
// Parameter: flags - byte flags (bit0 = allocate/initialize sub-object)
// Returns: this pointer

int __thiscall SomeEarsObject::initialize(int thisPtr, byte flags)
{
    // Call base class constructor/initializer (likely an EARS framework base)
    thisPtr = FUN_0083f0e0(thisPtr);

    // If flag bit 0 set, perform additional allocation or initialization of a 0x148-sized block
    if ((flags & 1) != 0) {
        FUN_0043b960(thisPtr, 0x148); // size likely corresponds to a member object or buffer
    }

    return thisPtr;
}
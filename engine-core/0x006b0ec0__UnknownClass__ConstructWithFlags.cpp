// FUNC_NAME: UnknownClass::ConstructWithFlags
// Function address: 0x006b0ec0
// Role: Constructor that takes an allocation flag. Calls base constructor (0x006b0580) and if (flags & 1) is set, calls a deallocation function (likely operator delete or destructor) on this. Returns this pointer.
// Note: This pattern is typical of a custom memory management scheme where the low bit of the parameter indicates whether the object was heap-allocated and should be freed on failure.

void* __thiscall UnknownClass::ConstructWithFlags(byte flags) {
    // Call base class constructor (unknown, at 0x006b0580)
    FUN_006b0580();

    // If the low bit of flags is set, deallocate this (function at 0x009c8eb0)
    if (flags & 1) {
        FUN_009c8eb0(this);
    }

    return this;
}
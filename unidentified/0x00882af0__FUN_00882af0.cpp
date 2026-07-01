// FUNC_NAME: SomeClass::SomeClass(uint flags)
// Address: 0x00882af0
// This function appears to be a constructor that accepts a flags byte.
// Bit 0 indicates whether to perform an internal cleanup (possibly a destructor or deallocation).
// It first calls the base class constructor (FUN_008825e0), then conditionally calls an internal cleanup function (FUN_00624da0).

SomeClass * __thiscall SomeClass::SomeClass(SomeClass *this, byte flags) {
    // Call base class constructor (likely BaseClass::BaseClass())
    this->baseConstructor(); // FUN_008825e0

    // If the lowest bit is set, perform internal cleanup (e.g., destructor or operator delete)
    if ((flags & 1) != 0) {
        this->internalCleanup(); // FUN_00624da0
    }

    return this;
}
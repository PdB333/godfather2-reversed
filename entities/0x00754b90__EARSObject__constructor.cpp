// FUNC_NAME: EARSObject::constructor
// Function at 0x00754b90: Constructor for a derived EA object. Sets vtable, calls base init, optionally deallocates if flagged.
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte constructorFlags)
{
    // Set vtable pointer (0x00d64c90) - likely a specific class vtable
    *this = &PTR_LAB_00d64c90;
    // Call base class constructor / initializer
    FUN_004ac1e0();
    // If bit 0 is set, call deallocation (e.g., operator delete) on this pointer
    if ((constructorFlags & 1) != 0) {
        FUN_00624da0(this);
    }
    return this;
}
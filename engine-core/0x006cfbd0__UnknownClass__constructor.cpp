// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass_constructor(undefined4 *this, byte allocateFlag)
{
    char cVar1;
    int *allocator;

    // Set vtable pointers:+0x00 and +0x08
    *this = &PTR_UNKNOWN_VTABLE_00d5f1f0;   // +0x00 
    this[2] = &PTR_UNKNOWN_POINTER_00d5f1e8; // +0x08

    // Check global initialization status
    cVar1 = FUN_0089c630(); // Possibly IsEngineInitialized()
    if (cVar1 != '\0') {
        FUN_006915c0(7); // Log or debug output
    }

    // Call base class constructor
    FUN_00473a60(); // BaseClass::BaseClass()

    // If allocation flag bit 0 is set, allocate memory for this object (size 0xB0)
    if ((allocateFlag & 1) != 0) {
        allocator = (int *)FUN_009c8f80(); // Get heap allocator
        (**(code **)(*allocator + 4))(this, 0xb0); // Call allocator's allocate method
    }

    return this;
}
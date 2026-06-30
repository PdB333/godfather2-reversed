// FUNC_NAME: MultiInheritClass::MultiInheritClass

// Constructor at 0x006b9ce0 for a class with multiple vtable pointers and a subobject at +0x98.
// param_2: bit 0 indicates dynamic allocation flag (calls operator delete if set).
MultiInheritClass::MultiInheritClass(byte allocFlag) {
    // Set primary vtable pointer (offset 0x00)
    this->vtable = &Vtable_00d5e668;

    // Set secondary vtable pointer at offset +0x3C (0xF * 4)
    this->field_0x3C = &FuncTable_00d5e658;

    // Set tertiary vtable pointer at offset +0x48 (0x12 * 4)
    this->field_0x48 = &FuncTable_00d5e654;

    // Initialize subobject at offset +0x98 (0x26 * 4)
    // Assuming this is a base class or member of type SomeSubObject
    FUN_004086d0(&this->subobject_0x98);
    FUN_00408310(&this->subobject_0x98);

    // Global/static initialization hook
    FUN_006bcd70();

    // If object was allocated with new (bit 0 set), free it immediately after construction.
    // This pattern is unusual; possibly indicates a temporary or error path.
    if (allocFlag & 1) {
        FUN_0043b960(this, 0xC0); // operator delete(this, size 0xC0)
    }
}
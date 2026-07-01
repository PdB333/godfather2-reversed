// FUNC_NAME: SomeManager::SomeManager
void __thiscall SomeManager::SomeManager(SomeManager* this) {
    // Set vtable pointers for multiple base classes or virtual inheritance
    *this = &PTR_FUN_00d7cae8;              // +0x00: primary vtable
    this[0x0F] = &PTR_LAB_00d7cad8;        // +0x3C: secondary vtable (0xF * 4)
    this[0x12] = &PTR_LAB_00d7cad4;        // +0x48: tertiary vtable (0x12 * 4)

    // Initialize embedded subobject at offset 0x14 (20 bytes)
    // These likely call constructor and initializer for a sub-component
    FUN_004086d0(&this[0x14]);             // subobject constructor
    FUN_00408310(&this[0x14]);             // subobject initialization

    // Global engine-wide initialization (e.g., singleton or module setup)
    FUN_0046c640();
}
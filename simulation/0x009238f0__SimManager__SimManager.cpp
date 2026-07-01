// FUNC_NAME: SimManager::SimManager
void __fastcall SimManager::SimManager(SimManager* this)
{
    // Set vtable pointer (offset 0x00)
    this->vfptr = (VFTable*)&PTR_FUN_00d87350;

    // Initialize other members (offsets: +0x10, +0x4C)
    this->field_0x10 = &PTR_LAB_00d87328;
    this->field_0x4C = &PTR_LAB_00d87324; // First assignment (overwritten below)
    this->field_0x4C = &PTR_LAB_00d87320; // Second assignment (final value)

    // Reset global initialization flag
    g_simManagerInitialized = 0; // DAT_01129c48

    // Call base/sub-system initializer
    FUN_005c16e0(); // Likely initializes sub-components
}
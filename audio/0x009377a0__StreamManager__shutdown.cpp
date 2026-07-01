// FUNC_NAME: StreamManager::shutdown
void __fastcall StreamManager::shutdown(StreamManager* this)
{
    // Set virtual table to base class / parent vtable
    this->vfptr = (StreamManager_vtable*)&PTR_FUN_00d8a218;
    // +0x10: set parent vtable entry?
    this->field_0x10 = (void*)&PTR_LAB_00d8a1f4;
    // +0x4C (0x13 * 4): set another vtable entry
    this->field_0x4C = (void*)&PTR_LAB_00d8a1f0;

    // Free four stream objects (offsets +0x5C, +0x60, +0x64, +0x68)
    FUN_009c8f10(this->field_0x5C);   // +0x5C: stream pointer 1
    FUN_009c8f10(this->field_0x60);   // +0x60: stream pointer 2
    FUN_009c8f10(this->field_0x64);   // +0x64: stream pointer 3
    FUN_009c8f10(this->field_0x68);   // +0x68: stream pointer 4

    // Reset the vtable entry at +0x4C to a different one (post-cleanup)
    this->field_0x4C = (void*)&PTR_LAB_00d8a1ec;

    // Clear global stream count or active flag
    DAT_011305b4 = 0;

    // Perform additional engine-level shutdown
    FUN_005c16e0();
}
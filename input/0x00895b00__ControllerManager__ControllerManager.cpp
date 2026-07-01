// FUNC_NAME: ControllerManager::ControllerManager
ControllerManager* __thiscall ControllerManager::ControllerManager(ControllerManager* this, byte flags) {
    // +0x00: vtable pointer
    *this = (ControllerManagerVtable*)&PTR_FUN_00d779e4;
    // +0x3C (offset 0x0F): function pointer table
    this->field_0x3C = (ControllerManagerFuncPtr*)&PTR_LAB_00d779d4;
    // +0x48 (offset 0x12): function pointer table
    this->field_0x48 = (ControllerManagerFuncPtr*)&PTR_LAB_00d779d0;

    // Register with global controller system
    FUN_004086d0(&DAT_01218048);  // unknown: registerWithManager
    FUN_00408310(&DAT_01218048);  // unknown: initManager
    FUN_0046c640();                // unknown: globalInputSystemInit

    // If flag bit 0 is set, perform additional deallocation or setup (size 0x6C = 108 bytes)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x6C);  // unknown: doExtraInitOrCleanup
    }

    return this;
}
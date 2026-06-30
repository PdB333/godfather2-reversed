// FUNC_NAME: InputManager::shutdown
void __fastcall InputManager::shutdown(int *this) {
    // Offset 0x18: pointer to a sub-object (e.g., controller manager)
    if (this[6] != 0) {
        // Call virtual function at vtable offset 0x28 on the sub-object (likely release/destroy)
        int iVar1 = (*(code **)(*this + 0x28))(this[6]);
        if (iVar1 != 0) {
            // Call virtual function at vtable offset 0x0C on another sub-object (offset 0x14)
            (*(code **)(*(int *)this[5] + 0xc))(iVar1);
            // Global singleton flag (DAT_01205a20)
            g_bInputManagerInitialized = 0;
        }
    }
}
// FUNC_NAME: PlayerControllerState::updateWeaponSelection
void __fastcall PlayerControllerState::updateWeaponSelection(PlayerControllerState* this) {
    char cVar1;
    int iVar2;
    int local_4; // Output of resolveWeaponSlot

    local_4 = (int)this;

    // Check primary weapon slot (offset +0x154): if non-zero and not sentinel (0x48), resolve it
    if (*(int*)((int)this + 0x154) != 0 && *(int*)((int)this + 0x154) != 0x48) {
        iVar2 = *(int*)((int)this + 0x154) - 0x48; // Convert slot index
        cVar1 = resolveWeaponSlot(iVar2, &local_4); // Get new weapon ID
        iVar2 = local_4;
        if (cVar1 != '\0') goto updateValues; // If resolved, jump to update
    }

    // Secondary weapon slot (offset +0x15c)
    if (*(int*)((int)this + 0x15c) == 0) return;
    if (*(int*)((int)this + 0x15c) == 0x48) return;

    iVar2 = getGlobalWeaponManager(); // Singleton
    if (iVar2 == 0) return;

    if (*(int*)((int)this + 0x15c) == 0) {
        iVar2 = getGlobalWeaponManager();
        iVar2 = *(int*)(iVar2 + 0xf8); // Get current weapon ID from manager
    } else {
        iVar2 = getGlobalWeaponManager();
        iVar2 = *(int*)(iVar2 + 0xf8);
    }

updateValues:
    // Compare stored weapon ID (4 bytes at +0x150) with new iVar2
    if ((((*(char*)((int)this + 0x150) == (char)iVar2) &&
          (*(char*)((int)this + 0x151) == (char)((uint)iVar2 >> 8))) &&
         (*(char*)((int)this + 0x152) == (char)((uint)iVar2 >> 0x10))) &&
        (*(char*)((int)this + 0x153) == (char)((uint)iVar2 >> 0x18))) ||
       ((*(uint*)((int)this + 0x11c) >> 0x13 & 1) == 0)) {
        // Set flag bit 0x80000 (need weapon update) and store new ID
        *(uint*)((int)this + 0x11c) |= 0x80000;
        *(int*)((int)this + 0x150) = iVar2;

        // Dispatch based on controller type (array at DAT_00e56a9c, entry size 0x2c, indexed by this->slotIndex at +0x4)
        if (*(int*)((int)&g_controllerTypes + *(int*)((int)this + 4) * 0x2c) == 1) {
            handleGamepadWeaponChange(); // gamepad
            return;
        }
        if (*(int*)((int)&g_controllerTypes + *(int*)((int)this + 4) * 0x2c) == 2) {
            handleKeyboardWeaponChange(); // keyboard
            return;
        }
    }
}
// FUNC_NAME: Character::canPerformAction
int __thiscall Character::canPerformAction() {
    // Check if this has a current interaction target (pointer at +0x18)
    if (*(int*)(this + 0x18) != 0) {
        // Retrieve weapon manager (global singleton)
        int* pWeaponManager = (int*)FUN_0043b870(DAT_0113105c);
        if (pWeaponManager != 0) {
            // Check if the weapon manager's status byte at +0x78 has bit 2 set (e.g., "hasWeaponDrawn")
            if ((*(unsigned char*)((char*)pWeaponManager + 0x78) >> 2 & 1) != 0) {
                return 1;
            }
        }
    }

    // Second check: another global manager (e.g., target manager)
    if (*(int*)(this + 0x18) != 0) {
        int* pTargetManager = (int*)FUN_0043b870(DAT_01131064);
        if (pTargetManager != 0) {
            unsigned char statusByte = *(unsigned char*)((char*)pTargetManager + 0x2c);
            // Bit 0 must be set and the signed char must be non-negative (e.g., "active and not disabled")
            if ((statusByte & 1) != 0 && (char)statusByte > -1) {
                return 1;
            }
        }
    }
    return 0;
}
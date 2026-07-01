// FUNC_NAME: Player::handleWeaponSwitch
void __fastcall Player::handleWeaponSwitch(int thisPtr)
{
    int weaponData;
    
    // Get weapon data from weapon array using current weapon index
    // +0x54: weaponDataArray pointer, +0x60: currentWeaponIndex
    weaponData = FUN_008c74d0(*(undefined4 *)(*(int *)(thisPtr + 0x54) + *(int *)(thisPtr + 0x60) * 4));
    if (weaponData != 0) {
        // Clear bit 7 (0x80) in weapon flags at +0x84
        // This likely marks the weapon as "not equipped" or "holstered"
        *(uint *)(weaponData + 0x84) = *(uint *)(weaponData + 0x84) & 0xffffff7f;
    }
    // Check if weapon switch is allowed (some condition at +0x64)
    if (*(int *)(thisPtr + 100) == 0) {
        // Play weapon switch animation
        // First param: 1 if currentWeaponIndex != 0, else 2 (animation type)
        FUN_00922e20((*(int *)(thisPtr + 0x60) != 0) + 1, 1);
        // Update weapon state
        FUN_00957350();
        return;
    }
    return;
}
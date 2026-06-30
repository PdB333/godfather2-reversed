// FUNC_NAME: Player::getActiveWeaponHandle
// Address: 0x00701340
// Role: Returns a weapon handle if the player has an active weapon. Checks a validity flag at +0x2D0 and retrieves the handle from +0x334 via a conversion function.
int __fastcall Player::getActiveWeaponHandle(Player* this) {
    // +0x2D0: isWeaponActive (bool)
    if (*(int*)((uint8_t*)this + 0x2D0) != 0) {
        // +0x334: weaponHandle (internal handle)
        // FUN_00700090 converts internal handle to game object ID
        return FUN_00700090(*(int*)((uint8_t*)this + 0x334));
    }
    return 0;
}
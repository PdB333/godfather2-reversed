// FUNC_NAME: Player::spawnWeapon
int __thiscall Player::spawnWeapon(void) {
    // Get the weapon object from slot 0 (e.g., current weapon)
    Weapon* weapon = getWeaponByIndex(this, 0);
    if (weapon != nullptr) {
        // Check if the weapon is currently active (bit 21 at offset 0x5C)
        if ((weapon->flags >> 0x15) & 1) {
            removeWeapon(weapon); // Destroy the existing weapon
        }
        // Spawn a new weapon entity with parameters from the player
        // Arguments: weaponType (offset 0x34), weapon object, ammo (offset 0x38),
        //            someValue (offset 0x30), transform (offset 0x40)
        createWeaponEntity(*(int*)(this + 0x34), weapon, *(int*)(this + 0x38),
                           *(int*)(this + 0x30), (void*)(this + 0x40));
        // Set the weapon active state based on a flag at offset 0x1C
        setWeaponActive(*(byte*)(this + 0x1C) & 1);
        // Return the weapon's ID
        return getWeaponID(weapon);
    }
    return -1; // Return error if no weapon found
}
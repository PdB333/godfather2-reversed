// FUN_00493120: PlayerWeapon::setActiveAmmoType(unsigned int newAmmoType)
__thiscall void PlayerWeapon::setActiveAmmoType(unsigned int newAmmoType)
{
    // Store the new ammo type at offset +500 (0x1F4)
    *(unsigned int *)(this + 500) = newAmmoType;

    // Lookup weapon data from the global table (gWeaponData) at index newAmmoType
    // Each entry is 0x38 bytes (56 bytes)
    unsigned char *weaponDef;
    if (newAmmoType < 0x1000) {
        weaponDef = (unsigned char *)&gWeaponData + newAmmoType * 0x38;
    } else {
        weaponDef = nullptr;
    }

    // Read two ushort values from the weapon definition: offset +2 and +4 (likely damage/range)
    // Store as floats at offsets +0x244 and +0x248
    *(float *)(this + 0x244) = (float)*(unsigned short *)(weaponDef + 2);
    if (newAmmoType < 0x1000) {
        weaponDef = (unsigned char *)&gWeaponData + newAmmoType * 0x38;
    } else {
        weaponDef = nullptr;
    }
    *(float *)(this + 0x248) = (float)*(unsigned short *)(weaponDef + 4);

    // If this weapon belongs to the current player (global gCurrentPlayer)
    if (gCurrentPlayer == this) {
        // If the weapon has an active state flag at +0x1F0, update sounds
        if (*(int *)(this + 0x1F0) != 0) {
            updateWeaponSound(); // FUN_006063b0
        }
        // Update visual representation (e.g., ammo counter) with the new floats
        updateWeaponVisual(*(unsigned int *)(this + 0x14),   // some ID at +0x14
                           *(unsigned int *)(this + 0x240), // another parameter at +0x240
                           (float *)(this + 0x244));        // pointer to the two floats
    }
}
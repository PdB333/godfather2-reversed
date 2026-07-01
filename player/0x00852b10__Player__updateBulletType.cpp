// FUNC_NAME: Player::updateBulletType
// Function address: 0x00852b10
// Determines and applies the bullet type for the current weapon based on special ammo capability.
// When useSpecialAmmo is true and the current weapon supports armor-piercing rounds, it switches to that.
// Otherwise uses the weapon's default bullet type or "revolver" as fallback.
// Calls playWeaponSound at the end (sound ID 0x1f?).

void Player::updateBulletType(bool useSpecialAmmo)
{
    // Start constructing bullet string prefix? (debug log or internal builder)
    appendBulletString("bullet_");

    const char* weaponName = nullptr;

    if (useSpecialAmmo)
    {
        const char* temp = getCurrentWeaponName(); // FUN_00707510
        if (temp != nullptr && temp[0] != '\0')
        {
            // Check if the weapon has a special ammo flag (bit 5 at offset 0x8EC)
            WeaponData* wd = getWeaponData(); // FUN_007079c0
            if (wd != nullptr && ((wd->flags >> 5) & 1) != 0)  // +0x8EC bit 5
            {
                appendBulletString("bullet_armour_piercing");
                playWeaponSound(0x1f, 0); // Play sound for armour-piercing?
                return;
            }
            // Fallback: use the weapon name as the bullet suffix
            weaponName = getCurrentWeaponName(); // Re-fetch weapon name (FUN_00707510)
        }
    }
    else
    {
        weaponName = "revolver"; // Default bullet type if no special ammo
    }

    // If we reach here, weaponName is either the current weapon or "revolver"
    applyBulletString(weaponName); // FUN_004d4300
    playWeaponSound(0x1f, 0);
}
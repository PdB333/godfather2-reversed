// Xbox PDB: EARS_Apt_UIHud_ShowWeaponPerks
// FUNC_NAME: WeaponUpgradeVisualManager::updateUpgradeDisplay
// Address: 0x00939d10
// Role: Updates weapon upgrade model visibility (hollowpoint bullets, larger ammo clip, more explosives) based on player data flags.

void __thiscall WeaponUpgradeVisualManager::updateUpgradeDisplay(void* playerData) {
    // Hide all upgrade models initially
    triggerEquipEvent("HideHollowpointBullet", 0, &DAT_00d8a64c, 0);
    triggerEquipEvent("HideLargerAmmoClip", 0, &DAT_00d8a64c, 0);
    triggerEquipEvent("HideMoreExplosives", 0, &DAT_00d8a64c, 0);

    // Clear upgrade-related flags (bits 27 and 28)
    *(uint32_t*)((uint8_t*)this + 0x5C) &= 0xE7FFFFFF;

    // Check player upgrade availability flag at +0x1A8
    if (*(uint8_t*)((uint8_t*)playerData + 0x1A8) == 1) {
        // Set flag for "basic upgrades" category
        *(uint32_t*)((uint8_t*)this + 0x5C) |= 0x08000000;

        // Show hollowpoint bullet if the separate byte flag (+0x5F bit 0) is set
        if ((*(uint8_t*)((uint8_t*)this + 0x5F) & 1) != 0) {
            triggerEquipEvent("ShowHollowpointBullet", 0, &DAT_00d8a64c, 0);
        }

        // Show larger ammo clip if bit 25 of flags (+0x5C) is set
        if ((*(uint32_t*)((uint8_t*)this + 0x5C) >> 0x19 & 1) != 0) {
            triggerEquipEvent("ShowLargerAmmoClip", 0, &DAT_00d8a64c, 0);
            return; // Early exit after showing larger clip
        }
    } else {
        // Check weapon type byte at +0x1AD (values 0x19, 0x1A, 0x1B likely represent explosive types)
        char weaponType = *(char*)((uint8_t*)playerData + 0x1AD);
        if (weaponType == 0x1A || weaponType == 0x19 || weaponType == 0x1B) {
            // Set flag for explosives category
            *(uint32_t*)((uint8_t*)this + 0x5C) |= 0x10000000;

            // Show more explosives if bit 26 of flags (+0x5C) is set
            if ((*(uint32_t*)((uint8_t*)this + 0x5C) >> 0x1A & 1) != 0) {
                triggerEquipEvent("ShowMoreExplosives", 0, &DAT_00d8a64c, 0);
            }
        }
    }
}
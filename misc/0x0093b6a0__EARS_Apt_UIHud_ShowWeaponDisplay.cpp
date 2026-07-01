// Xbox PDB: EARS_Apt_UIHud_ShowWeaponDisplay
// FUNC_NAME: PlayerWeaponDisplay::setActiveWeapon
// Function address: 0x0093b6a0
// Role: Handles showing/hiding the weapon display UI for the player's current weapon.
// Based on decompilation of The Godfather 2 (x86), EARS engine.

void __thiscall PlayerWeaponDisplay::setActiveWeapon(Weapon* weapon, bool autoHide)
{
    // +0x5c: flags (bitmask)
    uint flags = *(uint *)(this + 0x5c);
    
    // Bit 3 (0x8) = transitioning/locked flag; abort if set
    if ((flags >> 3) & 1) {
        return;
    }

    if (weapon == nullptr) {
        // Hide weapon display
        postUIEvent("HideWeaponDisplay", 0, &DAT_00d8a64c, 0);
        // Clear bits 6 (0x40) and 7 (0x80) and some higher bits (0x18000000? via mask 0xe7ffff3f)
        *(uint *)(this + 0x5c) = flags & 0xe7ffff3f;
    }
    else {
        // Set weapon asset ID from weapon object
        uint weaponAssetId = getWeaponAssetId(weapon); // FUN_00704860
        *(uint *)(this + 0xd4) = weaponAssetId;

        // Get weapon display name (+0x1b8 in weapon object, typically a string pointer)
        char* weaponName = *(char**)(weapon + 0x1b8);
        if (weaponName == nullptr) {
            weaponName = &DAT_0120546e; // default "NoName"
        }

        // Show weapon display with the weapon name
        postUIEvent("ShowWeaponDisplay", 0, &DAT_00d8a64c, 1, weaponName);
        
        // Set bit 6 (0x40) – weapon visible
        *(uint *)(this + 0x5c) |= 0x40;

        // Additional weapon state updates
        updateWeaponGraphics(weapon);   // FUN_00939d10
        updateWeaponAmmo(weapon);       // FUN_0093a7e0
        updateWeaponAttachments(weapon);// FUN_00939c50

        if (!autoHide) {
            // No auto-hide: clear bit 7 (0x80)
            *(uint *)(this + 0x5c) &= ~0x80;
            return;
        }

        // Reset hide timer count (+0xe8)
        *(int *)(this + 0xe8) = 0;

        // Check if auto-hide timer is already running (bit 7)
        if (!(*(uint *)(this + 0x5c) >> 7 & 1)) {
            // Start timer at +0x10 (timer object) with callback address 0x0093a1c0 and delay 1 (seconds?)
            startTimer((Timer*)(this + 0x10), &LAB_0093a1c0, 1);
            // Set bit 7 (0x80) – timer running
            *(uint *)(this + 0x5c) |= 0x80;
        }
    }
}
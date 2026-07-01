// Xbox PDB: EARS_Apt_UIHud_ShowWeaponWheel
// FUNC_NAME: WeaponWheelManager::resetWeaponWheel
// Address: 0x0093d4c0
// Reconstructed from Ghidra decompilation of The Godfather 2 (EARS engine)
// This function initializes/resets the weapon wheel state, showing/hiding UI elements.

void __fastcall WeaponWheelManager::resetWeaponWheel(int this)
{
    // Get global manager pointer (likely a singleton)
    int* pGlobalManager = **(int***)(DAT_012233a0 + 4);
    if (pGlobalManager == 0 || pGlobalManager == (int*)0x1f30)
        return;

    // Set a flag at offset 0x570 (e.g., some state flag)
    *(uint*)(pGlobalManager + 0x570 / 4) |= 0x100000;

    // Default weapon slot index (10 = probably "fists" or "unarmed")
    *(int*)(this + 0xd4) = 10;

    // Check a bit at the base of the global manager structure
    // pGlobalManager points to a field at offset 0x1650 from the base
    int* basePtr = pGlobalManager - 0x1650 / 4; // Recover base pointer
    if ((*(uint*)basePtr >> 10 & 1) != 0)
    {
        // Access another field at base - 0x194 (offset -0x194 from base)
        int* somePtr = *(int**)(basePtr - 0x194 / 4);
        if (somePtr != 0)
        {
            int* weaponData = somePtr - 0x48 / 4; // Adjust pointer
            uint weaponIndex = FUN_00704860(weaponData); // Get weapon index from slot
            if (weaponIndex < 0xb) // 11 weapon slots
            {
                *(int*)(this + 0xd4) = weaponIndex; // Override default weapon
            }
        }
    }

    // Clear other fields
    *(int*)(this + 0xd8) = 0;
    *(int*)(this + 0xdc) = 0;

    // Determine weapon wheel mode based on game mode
    int gameMode = FUN_007a5f40(); // Returns 2 for some mode, else other
    if (gameMode == 2)
        *(int*)(this + 0xec) = 4; // Mode 4
    else
        *(int*)(this + 0xec) = 3; // Mode 3

    FUN_006913c0(*(int*)(this + 0xec)); // Apply weapon wheel mode

    // Clear more fields
    *(int*)(this + 0xf0) = 0;
    *(int*)(this + 0xf4) = 0;

    // Show weapon wheel UI
    FUN_005a04a0("ShowWeaponWheel", 0, &DAT_00d8a64c, 0);

    // Unknown function (maybe play sound or update)
    FUN_005c1ad0();

    // Set a color or vector (DAT_01130398 is likely a color constant)
    struct { uint color; int zero; int zero2; } localColor;
    localColor.color = DAT_01130398;
    localColor.zero = 0;
    localColor.zero2 = 0;
    FUN_00408a00(&localColor, 0);

    // Update weapon wheel display
    FUN_0093b610();

    // Set flag at offset 0x5c (bit 3 = 0x8)
    *(uint*)(this + 0x5c) |= 8;

    // Set a timer/callback with this+0x10 as context, callback at LAB_0093d180, interval 1
    FUN_005c0260(this + 0x10, &LAB_0093d180, 1);

    // If bit 6 is set, hide weapon display and clear relevant flags
    if ((*(uint*)(this + 0x5c) >> 6 & 1) != 0)
    {
        FUN_005a04a0("HideWeaponDisplay", 0, &DAT_00d8a64c, 0);
        *(uint*)(this + 0x5c) &= 0xe7ffff3f; // Clear bits 6 and 0x16? Actually mask clears bits 6 and 22? Check: 0xe7ffff3f = ~(0x180000C0) but let's keep as is.
    }

    // If bit 22 (0x16) is set, hide reward message and clear flag
    if ((*(uint*)(this + 0x5c) >> 0x16 & 1) != 0)
    {
        FUN_005a04a0("HideRewardMessage", 0, &DAT_00d8a64c, 0);
        *(uint*)(this + 0x5c) &= 0xffbfffff; // Clear bit 22
    }

    // Check another global pointer; if non-zero, hide weapon wheel entirely
    if (*(int*)(DAT_01223484 + 0xc) != 0)
    {
        FUN_0094dc50(0);
    }
}
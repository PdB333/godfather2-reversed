// FUNC_NAME: WeaponManager::updateWeaponSelection
void __fastcall WeaponManager::updateWeaponSelection(int playerIndex, int slotIndex, int weaponType)
{
    // Global state for current weapon selection
    g_weaponType = weaponType;

    if (weaponType == 3) {
        // Pistol type
        g_weaponCategoryIdx = 0;
        g_weaponIdx = 0x12; // 18
    } else if (weaponType == 4) {
        // Shotgun type
        g_weaponCategoryIdx = 2;
        g_weaponIdx = 0x13; // 19
    } else {
        // General weapon type
        g_weaponCategoryIdx = (slotIndex == 1) ? 1 : 0;
        // Compute weapon index: if playerIndex == 1, add 9 offset + weaponType*3 + slotIndex
        int baseOffset = (playerIndex == 1) ? 9 : 0;
        g_weaponIdx = baseOffset + (unsigned char)weaponType * 3 + (unsigned char)slotIndex;
    }

    // Retrieve weapon data from lookup tables
    g_weaponData1 = s_weaponCategoryTable[g_weaponCategoryIdx];
    g_weaponData2 = *(int *)((int)&s_weaponIndexTable + g_weaponIdx * 4);

    // Store raw input parameters
    g_lastSlotIndex = slotIndex;
    g_lastPlayerIndex = playerIndex;

    // If the weapon manager singleton is active, trigger sound/visual update
    if (g_weaponManager == (WeaponManager*)&s_weaponManagerInstance) {
        playWeaponSound(g_weaponData2);
        playWeaponSound(g_weaponData1);
    }
}
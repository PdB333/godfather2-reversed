// Xbox PDB: EARS_Apt_UIHud_FillWeaponWheelIcons
// FUNC_NAME: WeaponWheelManager::addAllWeaponIcons
void weaponWheelManager_addAllWeaponIcons(void) {
    // Check global game state pointer is valid and not a special sentinel (0x1f30)
    int* globalStatePtr = *(int**)(*(int*)0x012233a0 + 4);
    if (globalStatePtr == nullptr || *globalStatePtr == 0x1f30) {
        return;
    }

    // Iterate through 11 weapon slots (0 to 10)
    for (int weaponIndex = 0; weaponIndex < 11; weaponIndex++) {
        // Get weapon data object by index (likely WeaponData*)
        WeaponData* weapon = (WeaponData*)getWeaponDataByIndex(weaponIndex); // FUN_00705ab0
        if (weapon == nullptr) {
            continue;
        }

        // Build a string identifier for this weapon slot
        // local_10 is an array of 3 pointers; first is output string pointer
        const char* weaponIconId = nullptr;
        formatString(&weaponIconId, 1, "weapon_icon_%d", weaponIndex); // FUN_004d4a60

        // Get the icon texture name from the weapon object (offset 0x1b8)
        const char* iconName = (const char*)weapon->iconName; // +0x1b8
        if (iconName == nullptr) {
            iconName = ""; // DAT_0120546e - empty string fallback
        }

        // Use the generated ID or fallback to empty string
        const char* idToUse = weaponIconId;
        if (idToUse == nullptr) {
            idToUse = ""; // DAT_0120546e
        }

        // Call Lua function to register the icon in the weapon wheel HUD
        // Parameters: function name, some flag, Lua function ref, type (2), ID, icon name
        luaCall("AddWeaponWheelIcon", 0, &DAT_00d8a64c, 2, idToUse, iconName); // FUN_005a04a0

        // Clean up the temporary string – the decompiler shows a function pointer call
        // (local_4) on the string pointer. This is likely a destructor or free function.
        // Note: local_4 was never assigned in the decompiled output, assumed to be
        // set by formatString or a previous call. Keeping as a placeholder.
        if (weaponIconId != nullptr) {
            // (*local_4)(weaponIconId); // Hypothetical cleanup
        }
    }
}
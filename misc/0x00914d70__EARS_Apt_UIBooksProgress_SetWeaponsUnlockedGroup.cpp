// Xbox PDB: EARS_Apt_UIBooksProgress_SetWeaponsUnlockedGroup
// FUNC_NAME: ProgressBookWeapons::populateWeaponList
void __fastcall ProgressBookWeapons::populateWeaponList(ProgressBookWeapons* this)
{
    char groupIndex;
    uint weaponId;
    int slotIndex;
    uint groupAndSlot;
    int slot;
    char* weaponName;
    byte local_99;
    int local_98;
    float unlockProgress;
    undefined4 local_90; // unused constant
    uint local_8c;
    undefined1* weaponStringBuffer;
    undefined4 local_84;
    undefined4 local_80;
    code* weaponStringDeallocator;
    int local_78; // alias for this
    int keyBuffer[3];
    code* keyDeallocator;

    local_78 = (int)this;
    // Initialize the weapon progress group in the UI
    FUN_005a04a0("ProgressSetGroup", 0, &DAT_00d84448, 1, "$dv_menu_books_progress_weapons");
    this->weaponCount = 0; // +0x04
    local_90 = DAT_01129954;
    local_99 = 0;
    do {
        local_8c = (uint)local_99;
        slot = 0;
        local_98 = 5; // 5 weapon slots per group
        do {
            // Get weapon ID for current group and slot
            if (local_99 == 0) {
                weaponId = FUN_007aa2f0(slot); // Group 0 weapons
            } else {
                weaponId = FUN_007aa340(local_8c, slot); // Groups 1 and 2
            }
            int entityHandle = FUN_004461c0(weaponId, 0);
            weaponName = 0;
            uint stringKey = 0;
            if (entityHandle != 0) {
                FUN_0043aff0(entityHandle, 0x4ecfbe13); // Set database context (hash)
                FUN_0043af00(0); // Seek to field 0
                char flag = FUN_0043b120(); // Check if name is locked?
                if (flag == 0) {
                    FUN_0043b210();
                    weaponName = (char*)FUN_0043ab90(); // Get localized name
                    stringKey = FUN_004dafd0(weaponName); // Hash or normalize
                }
            }
            // Build key for unlock progress lookup
            uint unlockedKey = FUN_004db3a0(stringKey, "_UNLOCKED", 9);
            unlockProgress = 0.0;
            FUN_008934e0(unlockedKey, &unlockProgress); // Get progress value (0.0-1.0)
            // Build weapon display string from ID
            weaponStringBuffer = 0;
            local_84 = 0;
            local_80 = 0;
            weaponStringDeallocator = 0;
            FUN_004d4ad0(&weaponStringBuffer, &PTR_LAB_00d78708, weaponId);
            // Build key for UI (e.g., "type05" for group 0, slot 0? Actually "type%d%d")
            keyBuffer[0] = 0;
            keyBuffer[1] = 0;
            keyBuffer[2] = 0;
            keyDeallocator = 0;
            FUN_004d4ad0(keyBuffer, "type%d%d", slot, local_8c + 1);
            undefined1* displayName = weaponStringBuffer;
            if (unlockProgress == _DAT_00d577a0) { // Special value (e.g., 0.0 for locked)
                if (weaponStringBuffer == 0) {
                    displayName = &DAT_0120546e; // Empty string
                }
                weaponName = "Unknown"; // Locked weapon label
            } else if (weaponStringBuffer == 0) {
                displayName = &DAT_0120546e;
            }
            // Add weapon to progress book UI
            FUN_005a04a0("ProgressAddWeapon", 0, &DAT_00d84448, 2, weaponName, displayName);
            this->weaponCount++; // +0x04
            // Free temporary strings
            if (keyBuffer[0] != 0) {
                (*keyDeallocator)(keyBuffer[0]);
            }
            if (weaponStringBuffer != 0) {
                (*weaponStringDeallocator)(weaponStringBuffer);
            }
            slot++;
            local_98--;
        } while (local_98 != 0);
        local_99++;
    } while (local_99 < 3);
    return;
}
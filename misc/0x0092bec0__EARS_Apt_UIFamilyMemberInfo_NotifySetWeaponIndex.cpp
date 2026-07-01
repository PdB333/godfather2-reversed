// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_NotifySetWeaponIndex
// FUNC_NAME: PlayerWeaponManager::updateCurrentWeaponDisplay
void __thiscall PlayerWeaponManager::updateCurrentWeaponDisplay(void) {
    uint weaponIndex = *(uint *)(this + 0x12c); // current weapon index
    if (weaponIndex < *(uint *)(this + 0x128)) { // max weapons
        byte weaponType = *(byte *)(weaponIndex + 0x154 + this); // weapon type array
        byte isAltWeapon = *(byte *)(weaponIndex + 0x168 + this); // alt weapon flag
        
        uint weaponId; // combined weapon identifier
        if (isAltWeapon == 0) {
            weaponId = getWeaponName(weaponType); // FUN_007aa2f0
        } else {
            weaponId = getWeaponNameWithAlt(isAltWeapon, weaponType); // FUN_007aa340
        }
        
        // Get localized weapon name string
        char *weaponNameStr = nullptr;
        getLocalizedString(weaponId, &weaponNameStr); // FUN_007aa5c0
        char *namePtr = weaponNameStr;
        if (namePtr == nullptr) {
            namePtr = &DAT_0120546e; // empty string
        }
        
        // Get weapon icon texture ID
        uint iconTextureId = getTextureID(namePtr); // FUN_004dafd0
        *(uint *)(this + 0x130) = iconTextureId;
        
        // Determine weapon state (0=unavailable,1=available,2=equipped,3=?)
        char state = isWeaponAvailable(weaponId, weaponType); // FUN_0092b030
        if (state == '\0') {
            state = isWeaponEquipped(*(uint *)(this + 0x130)); // FUN_0092afa0
            if (state == '\0') {
                *(uint *)(this + 0x134) = 0; // unavailable
            } else {
                char altState = getWeaponAltState(weaponId); // FUN_0092b0e0
                *(uint *)(this + 0x134) = (altState != '\0') ? 3 : 1; // 3=alt equipped, 1=equipped
            }
        } else {
            *(uint *)(this + 0x134) = 2; // available
        }
        
        // Update HUD weapon icon if enabled
        if (*(char *)(this + 0x17c) != '\0') { // showWeaponIcon flag
            int *weaponDataPtr = (int *)(this + 0x138); // pointer to weapon data
            *(uint *)(this + 0x140) = isAltWeapon + 1; // ammo count? or slot?
            
            // Free previous weapon data if not null and not special value 0x48
            if ((*weaponDataPtr != 0) && (*weaponDataPtr != 0x48)) {
                int offset = (*weaponDataPtr == 0) ? 0 : (*weaponDataPtr - 0x48);
                freeMemory(offset + 0x3c); // FUN_004088c0
            }
            
            // Get weapon data object
            int weaponData = getWeaponData(weaponId, 0, 0, 0, 0); // FUN_00856780
            validateWeaponData(weaponData); // FUN_007686d0
            
            if ((weaponData == 0) || (*weaponDataPtr == 0) || (*weaponDataPtr == 0x48)) {
                // Clear weapon icon
                setHUDWeaponIcon("ClearWeaponIcon", 0, &DAT_00d88708, 0); // FUN_005a04a0
            } else {
                // Set weapon icon with name from weapon data
                char *iconName = *(char **)(weaponData + 0x1b8);
                if (iconName == nullptr) {
                    iconName = &DAT_0120546e;
                }
                setHUDWeaponIcon("SetWeaponIcon", 0, &DAT_00d88708, 1, iconName);
                
                // Copy weapon stats from weapon data
                int base = (*weaponDataPtr == 0) ? 0 : (*weaponDataPtr - 0x48);
                *(uint *)(this + 0x148) = *(uint *)(base + 0x518); // damage
                *(uint *)(this + 0x14c) = *(uint *)(base + 0x51c); // range
                *(uint *)(this + 0x144) = *(uint *)(base + 0x520); // fire rate
                if (*weaponDataPtr == 0) {
                    *(uint *)(this + 0x150) = uRam00000524; // unknown constant
                } else {
                    *(uint *)(this + 0x150) = *(uint *)(*weaponDataPtr + 0x4dc); // ammo capacity
                }
            }
            
            // Update ammo count display if not in menu
            if (*(int *)(this + 0x50) == 0) { // not in menu
                char *ammoStr = nullptr;
                float ammoFloat = getWeaponAmmoCount(*(uint *)(this + 0x130)); // FUN_0092aff0
                uint ammoInt = (uint)(longlong)ROUND(ammoFloat);
                formatIntegerToString(ammoInt, &ammoStr, 1); // FUN_00604000
                char *strPtr = ammoStr;
                if (strPtr == nullptr) {
                    strPtr = &DAT_0120546e;
                }
                setUIText(*(uint *)(this + 0x110), strPtr, 0x10, 0); // FUN_005c4660
                *(bool *)(this + 0x64) = ammoInt <= *(uint *)(this + 0x60); // low ammo flag
                if (ammoStr != nullptr) {
                    freeString(ammoStr); // (*local_14)(local_20)
                }
            }
        }
        
        if (weaponNameStr != nullptr) {
            freeString(weaponNameStr); // (*local_4)(local_10)
        }
    }
}
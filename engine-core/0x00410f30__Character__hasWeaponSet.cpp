// FUNC_NAME: Character::hasWeaponSet
int __thiscall Character::hasWeaponSet(void* thisPtr)
{
    // Check if the character has weapons enabled (flag at offset +0x52C)
    if (*(char*)((int)thisPtr + 0x52C) != 0) {
        // Call an update function (likely seeds/checks internal state)
        updateWeaponCheckState();

        // Check the primary weapon slot (offset +0x567)
        uchar primaryWeaponID = *(uchar*)((int)thisPtr + 0x567);
        if (primaryWeaponID != 0x12) {
            // Look up weapon data by ID; result is a pointer to a WeaponInfo struct
            WeaponInfo* pWeaponInfo = (WeaponInfo*)getWeaponInfo(primaryWeaponID);
            if (pWeaponInfo != nullptr && pWeaponInfo->type == 2) {
                return 1;
            }
        }

        // If primary weapon condition didn't match, check secondary weapon slot (offset +0x566)
        // Only if the weapons-enabled flag is still true
        if (*(char*)((int)thisPtr + 0x52C) != 0) {
            updateWeaponCheckState();
            uchar secondaryWeaponID = *(uchar*)((int)thisPtr + 0x566);
            if (secondaryWeaponID != 0x12) {
                WeaponInfo* pWeaponInfo = (WeaponInfo*)getWeaponInfo(secondaryWeaponID);
                if (pWeaponInfo != nullptr && pWeaponInfo->type == 3) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
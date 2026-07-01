// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_BuyWeapon
// FUNC_NAME: Player::updateEquippedWeapon
// Address: 0x0092b130
// This function checks if the player has a weapon to equip and updates the equipped weapon.
// It iterates through weapon slots (offset 0x128 = maxSlots, offset 300 = currentSlotIndex).
// For each slot, it retrieves weapon data and equips if valid and allowed.

void __fastcall Player::updateEquippedWeapon(int thisObj)
{
    int weaponData;
    char weaponType;
    char someFlag;
    int *pWeaponData;
    float timeValue;
    int slotIndex;

    // Check if current slot index is within valid range
    if (*(unsigned int *)(thisObj + 300) < *(unsigned int *)(thisObj + 0x128))
    {
        slotIndex = thisObj + *(unsigned int *)(thisObj + 300);
        weaponType = *(char *)(slotIndex + 0x154);   // weapon type/ID
        someFlag = *(char *)(slotIndex + 0x168);     // flag (e.g., is weapon unlocked?)

        // Retrieve weapon data based on flag
        if (someFlag == '\0')
        {
            pWeaponData = (int *)FUN_007aa2f0(weaponType);
        }
        else
        {
            pWeaponData = (int *)FUN_007aa340(someFlag, weaponType);
        }

        // Check if weapon data is valid (non-null and first 4 ints not all zero)
        if (pWeaponData != (int *)0x0 &&
            ((pWeaponData[0] != 0 || pWeaponData[1] != 0 || pWeaponData[2] != 0 || pWeaponData[3] != 0)))
        {
            // Check if equipping is allowed (e.g., not in vehicle, not dead)
            if (FUN_00445250() != '\0')
            {
                // Equip the weapon
                FUN_0090a7e0(pWeaponData);

                // Get current time or cooldown value
                timeValue = (float)FUN_0092aff0(*(unsigned int *)(thisObj + 0x130));

                // Update weapon state (slot 9 maybe for current weapon)
                FUN_0092a900(timeValue, 9);

                // Log the event
                FUN_005a04a0("UpdateEquippedWeapon", 0, &DAT_00d88708, 0);

                // Notify UI or network
                FUN_00894c90(0x5b859ffc);
            }
        }
    }
    return;
}
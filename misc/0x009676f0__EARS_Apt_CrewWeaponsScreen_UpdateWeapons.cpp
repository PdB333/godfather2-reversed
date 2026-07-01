// Xbox PDB: EARS_Apt_CrewWeaponsScreen_UpdateWeapons
// FUNC_NAME: WeaponManager::updateWeaponList
void __fastcall WeaponManager::updateWeaponList(int this)
{
    byte weaponIndex;
    undefined4 weaponId;
    uint i;
    uint currentWeapon;
    uint weaponCount;
    undefined4 weaponData;
    undefined4 weaponName;
    undefined4 *pWeaponName;
    undefined1 *pWeaponData;
    undefined1 local_d;
    undefined4 local_c;
    undefined4 local_8;
    int local_4;

    currentWeapon = 0;
    local_4 = this;
    FUN_005a04a0("ClearWeaponsList", 0, &DAT_00d8cdec, 0); // Clear the weapon list UI
    *(undefined4 *)(this + 0x14) = 0; // Reset weapon count

    // Check if we have any weapons to process
    if ((*(uint *)(DAT_01129930 + 0x2b4) < *(uint *)(DAT_0112b9b4 + 0x2c)) && (DAT_011308b6 != 0)) {
        weaponId = *(undefined4 *)(*(int *)(DAT_0112b9b4 + 0x28) + *(uint *)(DAT_01129930 + 0x2b4) * 4);
        local_8 = DAT_01129908;
        DAT_011308b7 = 0x14; // Reset selected weapon index

        do {
            bVar1 = (&DAT_011308a0)[currentWeapon]; // Get weapon slot index
            uVar3 = *(uint *)(&DAT_00d8dcac + (uint)bVar1 * 0x10); // Get required level for weapon
            uVar4 = FUN_008bcf60(weaponId); // Get player's current level
            if (uVar3 <= (uVar4 & 0xff)) { // Check if player has required level
                weaponName = *(undefined4 *)(&DAT_00d8dca4 + (uint)bVar1 * 0x10); // Get weapon name
                pWeaponData = &local_d;
                pWeaponName = &local_c;
                local_c = 0;
                weaponData = 0x9677a7;
                FUN_006039d0(weaponName, pWeaponName, pWeaponData); // Get weapon data
                FUN_004d3bc0(local_c); // Add weapon to list
                FUN_009674a0(weaponData, weaponName, pWeaponName, pWeaponData); // Show weapon in UI
                if (DAT_011308b7 == 0x14) {
                    DAT_011308b7 = (char)currentWeapon; // Set first available weapon as selected
                }
            }
            currentWeapon = currentWeapon + 1;
        } while (currentWeapon < DAT_011308b6);
    }
    FUN_005a04a0("ShowWeaponsList", 0, &DAT_00d8cdec, 0); // Show the updated weapon list
    return;
}
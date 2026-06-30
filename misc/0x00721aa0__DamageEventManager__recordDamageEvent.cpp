// FUNC_NAME: DamageEventManager::recordDamageEvent
void DamageEventManager::recordDamageEvent(int character, float time, int damageInfo)
{
    int weaponId;
    int weaponData;
    int damageEvent;

    if ((character != 0) && (g_lastDamageTimestamp < time)) {
        if (*(int *)(damageInfo + 8) == 0) {
            weaponId = 0;
        }
        else {
            weaponId = *(int *)(damageInfo + 8) + -0x48;
        }
        damageEvent = FUN_00721a30(); // Allocate damage event slot
        *(undefined4 *)(damageEvent + 0x10) = 0; // Flags
        FUN_0044b210(weaponId); // Possibly getWeaponFromEntity
        *(float *)(damageEvent + 8) = time; // Timestamp
        *(undefined4 *)(damageEvent + 0xc) = *(undefined4 *)(damageInfo + 0x20); // Damage value
        if (*(char *)(damageInfo + 0x1c) == '\0') {
            if (weaponId != 0) {
                weaponData = FUN_00471610(); // Get weapon data from character
                *(undefined8 *)(damageEvent + 0x14) = *(undefined8 *)(weaponData + 0x30);
                *(undefined4 *)(damageEvent + 0x1c) = *(undefined4 *)(weaponData + 0x38);
            }
        }
        else {
            *(undefined8 *)(damageEvent + 0x14) = *(undefined8 *)(damageInfo + 0x10); // Position?
            *(undefined4 *)(damageEvent + 0x1c) = *(undefined4 *)(damageInfo + 0x18); // Direction?
        }
        if ((*(byte *)(character + 0x5c) >> 4 & 1) != 0) { // Bit 4: headshot flag
            *(uint *)(damageEvent + 0x10) = *(uint *)(damageEvent + 0x10) | 4;
            *(undefined4 *)(damageEvent + 0x20) = *(undefined4 *)(damageEvent + 0xc); // Copy damage
        }
        if ((*(byte *)(character + 0x5c) >> 2 & 1) != 0) { // Bit 2: critical flag
            *(uint *)(damageEvent + 0x10) = *(uint *)(damageEvent + 0x10) | 8;
        }
    }
}
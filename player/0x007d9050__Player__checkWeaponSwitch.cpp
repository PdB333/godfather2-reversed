// FUNC_NAME: Player::checkWeaponSwitch
int __fastcall Player::checkWeaponSwitch(int this) {
    uint32_t currentWeapon = in_EAX;
    uint32_t result = currentWeapon >> 8;

    // Check if the inventory component flags have bit 2 set
    InventoryComponent* invComp = *(InventoryComponent**)(this + 0x74);  // +0x74
    if (invComp && (*(uint8_t*)((int)invComp + 4) & 4)) {
        // Get the current system state (e.g., targeting or action state)
        result = getSystemState();  // FUN_007ab160

        // Check if the system state also has the flag and global conditions
        if ((*(uint8_t*)(result + 4) & 4) &&
            (g_globalPtr == nullptr || *(int*)(g_globalPtr + 0x5c) == 0)) {
            // Read weapon slot from player data
            WeaponData* weaponData = *(WeaponData**)(this + 0x58);  // +0x58
            uint32_t weaponSlotA = *(uint32_t*)((int)weaponData + 0x24b4);  // +0x24b4
            if (weaponSlotA != 0 && weaponSlotA != 0x48) {
                uint32_t weaponSlotB = *(uint32_t*)((int)weaponData + 0x74c);  // +0x74c
                uint32_t weaponSlotBAdj = (weaponSlotB == 0) ? 0 : (weaponSlotB - 0x48);
                uint32_t weaponSlotAAdj = weaponSlotA - 0x48;

                // If the adjusted slots differ, signal a weapon switch
                if (weaponSlotAAdj != weaponSlotBAdj) {
                    return (weaponSlotBAdj >> 8) << 8 | 1;  // low byte = 1 indicates change
                }
            }
        }
        result >>= 8;
    }
    return result << 8;
}
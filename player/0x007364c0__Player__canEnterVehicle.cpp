// FUNC_NAME: Player::canEnterVehicle
uint __thiscall Player::canEnterVehicle(int *pTargetObject) {
    // pTargetObject is the object to check (e.g., a vehicle)
    // Returns a flag indicating whether the player can enter it
    if (pTargetObject == nullptr) {
        return 0;
    }
    int *vtable = *pTargetObject;
    // Query for a specific interface (GUID 0x55859efa)
    // The function pointer at vtable+0x10 is likely QueryInterface
    int result = reinterpret_cast<int (__stdcall *)(uint, int**)>(vtable[4])(0x55859efa, &pTargetObject);
    if ((result & 0xFF) && g_pPlayer != nullptr) {
        // +0x1ed8: pointer to current vehicle (or other entity)
        // Subtract 0x48 to get base entity pointer
        int entityPtr = (this->field_0x1ed8 == 0) ? 0 : this->field_0x1ed8 - 0x48;
        int weaponPtr = (this->field_0x2178 == 0) ? 0 : this->field_0x2178 - 0x48;
        // Check flags at +0x84 (bit 1) and +0x54 (a hash)
        if (((~(*(uint *)(entityPtr + 0x84) >> 1) & 1) == 0) &&
            ((*(int *)(entityPtr + 0x54) != 0x637b907) ||
             (weaponPtr == 0) ||
             ((*(uint *)(weaponPtr + 0x5c) >> 0x1d) & 1) == 0)) {
            // Check player state at g_pPlayer +0xff8 and +0x8e4
            if ((*(char *)(g_pPlayer + 0xff8) != 2) &&
                ((*(uint *)(g_pPlayer + 0x8e4) >> 0x16) & 1) == 0) {
                result = FUN_00806550(g_pPlayer);
                return result;
            }
        }
    }
    return 0;
}
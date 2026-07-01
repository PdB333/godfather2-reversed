// Xbox PDB: EARS_Apt_UIHud_UpdateWeaponInfo
// FUNC_NAME: Player::updateWeaponInfo
// Address: 0x0093b610
// Reconstructed from Ghidra decompilation

extern uint8_t* g_pGameState; // +0x4 holds pointer to game state flags, e.g., menu/loading check

void Player::updateWeaponInfo()
{
    // Access global game state via double pointer: *(int**)(g_pGameState+4)
    int* pGameStateFlag = *(int**)(g_pGameState + 4);
    if (pGameStateFlag != nullptr && *pGameStateFlag != 0x1f30)
    {
        // +0xd4: current weapon index/handle (probably uint32)
        int weaponHandle = FUN_00705ab0(*(undefined4*)(this + 0xd4));
        if (weaponHandle == 0)
        {
            // +0xe0: weapon name buffer (128 bytes)
            _memset(*(void**)(this + 0xe0), 0, 0x80);
            // +0xe4: weapon description/short name buffer (128 bytes)
            _memset(*(void**)(this + 0xe4), 0, 0x80);
        }
        else
        {
            // Populate weapon data into the player's weapon info
            FUN_00939c50(weaponHandle);
            FUN_0093a7e0(weaponHandle);
        }
        // Debug/log event: "UpdateWeaponInfo"
        FUN_005a04a0("UpdateWeaponInfo", 0, &DAT_00d8a64c, 0);
    }
}
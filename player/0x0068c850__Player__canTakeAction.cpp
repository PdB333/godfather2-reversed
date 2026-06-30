// FUNC_NAME: Player::canTakeAction

bool __fastcall Player::canTakeAction(Player* this)
{
    // Check if this player slot is active (offset +0x15: m_bActive or m_bEnabled)
    if (this->field_0x15 == 0)
        return false;

    // Global input manager / game state check
    if (g_pGameStateManager != nullptr)
    {
        // Bit 5 (0x20) of flags at +0x4c indicates input is locked (menu, pause, etc.)
        if ((g_pGameStateManager->flags & 0x20) != 0)
            return false;

        // Check if a full‑screen UI (e.g. codec, pause menu) is active
        if (IsMenuActive())
            return false;
    }

    // Check if the game simulation is in a playable state
    if (IsGameActive())
    {
        // If the player is not in a restricted state (e.g. alive and on foot),
        // allow the action immediately. (+0x54 on g_pPlayer: m_restrictedState flag)
        if (g_pPlayer->field_0x54 == 0)
            return true;

        // Player is in a normally controllable state (e.g. on foot, not ragdoll)
        if (IsPlayerControllable())
        {
            // Allow action if player is engaged in combat
            if (IsPlayerInCombat())
                return true;

            // Allow action if player is driving a vehicle (+0x6c is pointer to vehicle handle)
            if (g_pPlayerVehicleManager->vehicle != nullptr)
                return true;
        }
    }

    return false;
}

// External helper functions (simple declarations, not defined here)
extern bool __cdecl IsMenuActive();               // FUN_00842870
extern bool __cdecl IsGameActive();               // FUN_00982670
extern bool __cdecl IsPlayerControllable();       // FUN_0068c530
extern bool __cdecl IsPlayerInCombat();           // FUN_0040edb0

// Global singleton pointers (assumed to be defined elsewhere)
extern GameStateManager* g_pGameStateManager;     // DAT_01129948
extern Player* g_pPlayer;                         // DAT_01223394
extern VehicleManager* g_pPlayerVehicleManager;   // DAT_0112982c
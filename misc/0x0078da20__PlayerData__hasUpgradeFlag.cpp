// FUNC_NAME: PlayerData::hasUpgradeFlag
// Address: 0x0078da20
// This function checks if a specific ability/upgrade flag is set for the player,
// considering the current game state to determine which ability slot to use.

bool __thiscall PlayerData::hasUpgradeFlag(PlayerData* this, uint32 abilityFlag)
{
    int32 slotIndex;

    // Determine which ability slot to use based on global game state.
    // s_pPlayerManager is a singleton managing the active player character.
    // s_pMissionManager is a singleton for mission/difficulty state.
    if (s_pPlayerManager != nullptr && *(void**)((uint8*)s_pPlayerManager + 0xD8) != nullptr)
    {
        // Slot 2: Active player has a valid character (e.g., during free roam or main game)
        slotIndex = 2;
    }
    else if (s_pMissionManager != nullptr &&
             *(int32*)((uint8*)s_pMissionManager + 100) > 7 &&
             *(int32*)((uint8*)s_pMissionManager + 100) < 20)
    {
        // Slot 1: Mission difficulty/level is in a specific range (8 to 19 inclusive)
        // Possibly indicates an in-mission or special state.
        slotIndex = 1;
    }
    else
    {
        // Slot 0: Default or menu / non-game state
        slotIndex = 0;
    }

    // Check if the requested ability flag is set in the selected slot.
    // m_upgradeFlags is an array of 3 DWORDs at offset 0xF0, each 0x38 bytes apart.
    uint32 slotFlags = *(uint32*)((uint8*)this + 0xF0 + slotIndex * 0x38);
    return (slotFlags & abilityFlag) != 0;
}
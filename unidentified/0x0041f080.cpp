// FUN_0041f080: PlayerManager::activatePlayerSlot
// Address: 0x0041f080
// This function attempts to activate a player's team member slot.
// Returns 1 on success, 0 on failure or if activation is globally disabled.

#include <cstdint>

class PlayerManager
{
public:
    static bool activatePlayerSlot(int playerIndex, int teamMemberIndex);

private:
    // +0x01205378: Global flag indicating if gameplay is active
    static bool g_gameActive;

    // +0x01163820: Array of player data structs (size 0x84 each, indexed by playerIndex * 0x84 + teamMemberIndex)
    // The struct is at least 0x84 bytes; member at offset +0x80 is used in the animation setup call.
    static uint8_t g_playerData[];

    // +0x0116384c: Secondary array of player fields (size 0x84 per slot)
    static uint8_t g_playerField4c[];

    // +0x01163850: Tertiary array of player fields (size 0x84 per slot)
    static uint8_t g_playerField50[];

    // +0x0116382c: Flag array per player per team member (stride 0x210 per player, sub-index teamMemberIndex)
    // This byte indicates whether the specific team member is currently active.
    static uint8_t g_playerActiveFlags[];
};

bool PlayerManager::activatePlayerSlot(int playerIndex, int teamMemberIndex)
{
    // Check global gameplay active flag
    if (g_gameActive)
    {
        // Validate the player/team member slot
        // FUN_0044cc60 is likely a validation function that checks if the slot is permissible
        bool isValid = FUN_0044cc60(&g_playerData[playerIndex * 0x84 + teamMemberIndex],
                                    teamMemberIndex,
                                    &g_playerField4c[playerIndex * 0x84],
                                    &g_playerField50[playerIndex * 0x84]);

        if (isValid)
        {
            // Mark this team member as active
            g_playerActiveFlags[playerIndex * 0x210 + teamMemberIndex] = 1;

            // Update player state and notify game systems
            FUN_004236f0(); // Likely updates internal player state
            FUN_00423aa0(); // Possibly dispatches a notification

            // Set up animation or visual state (e.g., equip weapon, activate model)
            // Third argument 2 might indicate a specific state ID
            FUN_00433430(g_unknownGlobal, &g_playerData[playerIndex * 0x84 + teamMemberIndex] + 0x80, 2);

            return true;
        }
    }

    // If activation fails, mark as inactive
    g_playerActiveFlags[playerIndex * 0x210 + teamMemberIndex] = 0;
    return false;
}
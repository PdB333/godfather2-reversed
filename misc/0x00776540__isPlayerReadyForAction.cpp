// FUNC_NAME: isPlayerReadyForAction
// Address: 0x00776540
// Returns 1 if the player is not in a special state (e.g., mission, cutscene) and a component is present.
// Likely used to check if player can accept new missions or start interactions.

bool isPlayerReadyForAction()
{
    // Get the singleton player manager or game manager (returns pointer to an object)
    void* playerManager = reinterpret_cast<void*>(FUN_00800a90());
    if (playerManager != nullptr)
    {
        // Get the player object or a specific component (e.g., player state)
        void* playerState = reinterpret_cast<void*>(FUN_007013c0());
        if (playerState != nullptr)
        {
            // Check a flag at offset 0x328 (e.g., isInMission, isInCutscene, isInDialog)
            if (*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(playerManager) + 0x328) == 0)
            {
                return true;
            }
        }
    }
    return false;
}
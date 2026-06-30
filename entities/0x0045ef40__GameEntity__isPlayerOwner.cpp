// FUNC_NAME: GameEntity::isPlayerOwner
// Address: 0x0045ef40
// Checks if this entity is owned by a specific player, based on current state.
// Returns true when: m_manager != null, certain global state is valid, and the given playerId matches the current entity owner ID.

bool __thiscall GameEntity::isPlayerOwner(int thisPtr, int playerId)
{
    char globalStateValid;
    int currentOwnerId;

    // Check if the manager pointer at +0x218 is non-null
    if (*(int *)(thisPtr + 0x218) == 0)
    {
        return false;
    }

    // Check some global state (e.g., is the game in a multiplayer session?)
    globalStateValid = FUN_00573440();   // likely returns bool (0/1)
    if (globalStateValid != 0)
    {
        // Get the current owner ID from some system (e.g., network player ID)
        currentOwnerId = FUN_00572780();
        // Compare given playerId with the owner ID
        return playerId == currentOwnerId;
    }

    return false;
}
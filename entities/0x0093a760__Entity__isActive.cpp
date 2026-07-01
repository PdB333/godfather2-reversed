// FUNC_NAME: Entity::isActive
// Address: 0x0093a760
// Role: Checks if the entity is active/controllable based on flags and global state.

bool __thiscall Entity::isActive(Entity* thisEntity)
{
    bool bHasActivePlayer;
    char bSomeGlobalState;

    // Check if there is an active player/manager
    if ((gPlayerManager != 0) && (*(int*)(gPlayerManager + 0x5c) != 0)) {
        bHasActivePlayer = true;
    } else {
        bHasActivePlayer = false;
    }

    // Check if a global state (e.g., cutscene or menu) is active
    if ((*(char*)(gInputManager + 0x568) == 0x12) && (isGamePaused() != 0)) {
        return true;
    }

    // Check entity-specific flags
    if ((((*(byte*)(thisEntity + 0x49) & 0x0A) == 0) &&          // Not dead/disabled
        (*(int*)(thisEntity + 0x60) == 0) &&                      // No active action
        ((*(uint*)(thisEntity + 0x5c) & 0x20082410) == 0)) &&     // Not in special state
        (!bHasActivePlayer))                                      // No active player
    {
        return false;
    }

    return true;
}
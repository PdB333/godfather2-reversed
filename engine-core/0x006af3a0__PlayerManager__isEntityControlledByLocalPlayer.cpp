// FUNC_NAME: PlayerManager::isEntityControlledByLocalPlayer
// Function address: 0x006af3a0
// Logic: Checks if the given entity is either unowned (with a valid local player) or owned by the local player.
// Offset 0x184 in "this" is localPlayerId.
// Offset 0x1ee8 in param_2 (entity) is ownerId.
// Callee 0x00471610 returns a pointer to the current local player (or some entity).
// Callee 0x006aed40 checks if an entity at a given offset is valid/alive (offset 0x30 from the local player pointer).

bool __thiscall PlayerManager::isEntityControlledByLocalPlayer(PlayerManager *this, void *entity) {
    int localPlayerId; // from this+0x184
    int ownerId;       // from entity+0x1ee8
    char isValid;      // result from helper

    ownerId = *(int *)((char *)entity + 0x1ee8);
    if (ownerId == 0) {
        // No owner: check if local player exists and is valid
        void *localPlayer = GetLocalPlayer(); // FUN_00471610
        isValid = IsPlayerActive((int)((char *)localPlayer + 0x30)); // FUN_006aed40, offset 0x30 might be a component or state
        if (isValid != '\0') {
            return true;
        }
    }
    else if (ownerId == *(int *)((char *)this + 0x184)) {
        // Owned by local player
        return true;
    }
    return false;
}
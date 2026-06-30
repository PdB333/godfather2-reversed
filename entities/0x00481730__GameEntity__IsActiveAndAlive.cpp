// FUNC_NAME: GameEntity::IsActiveAndAlive

// Reconstructed from 0x00481730
// Checks if a game entity is active and alive, with respect to a global debug overlay.

bool __thiscall GameEntity::IsActiveAndAlive(int thisPtr)
{
    // +0x0C: pointer to entity data block (e.g., character stats, state)
    int entityData = *(int *)(thisPtr + 0x0C);

    if (entityData == 0)
        return false;

    // +0x30: flags word, bit 1 indicates dead/unconscious
    if ((*(unsigned int *)(entityData + 0x30) >> 1) & 1)
        return false;

    // +0x3C: flags byte, bit 0 indicates destroyed/removed
    if ((*(unsigned char *)(entityData + 0x3C) & 1) != 0)
        return false;

    // +0x50: pointer to health component or state machine (must be non-null)
    if (*(int *)(entityData + 0x50) == 0)
        return false;

    // DAT_01205a20: global – non-zero when a debug overlay (e.g., menu, pause) is active
    extern int g_debugOverlayActive; // DAT_01205a20
    if (g_debugOverlayActive != 0)
    {
        // FUN_0064d860: returns 1 if interaction is allowed, 0 if blocked (e.g., cinematics)
        bool interactionAllowed = (FUN_0064d860() != 0);
        if (!interactionAllowed)
            return false;
    }

    return true;
}
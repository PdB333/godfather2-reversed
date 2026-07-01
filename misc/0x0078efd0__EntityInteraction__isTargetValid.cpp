// FUNC_NAME: EntityInteraction::isTargetValid
// Function at 0x0078efd0 checks if a given entity (param_2) is valid relative to stored target references.
// Returns 0 if the entity should be ignored, 1 otherwise.
// Logic: if the interaction has stored targets (m_targetA or m_targetB), the entity must match the primary (m_targetA)
// and not equal the secondary (m_targetB) to be considered valid. If no stored targets, any entity is valid.

bool __thiscall EntityInteraction::isTargetValid(int thisPtr, int entity) {
    int primaryTarget;
    int secondaryTarget;
    int playerEntity;

    primaryTarget = *(int *)(thisPtr + 0x18);   // +0x18 m_targetA (primary)
    secondaryTarget = *(int *)(thisPtr + 0x1c); // +0x1c m_targetB (secondary)

    // Check flags at +0x28 bit 0: if set, override primary with the current player's target
    if ((*(byte *)(thisPtr + 0x28) & 1) != 0) {
        playerEntity = getCurrentPlayerEntity(); // calls FUN_0078e110()
        if (playerEntity != 0) {
            primaryTarget = *(int *)(playerEntity + 0x188); // +0x188 (e.g., m_interactionTarget)
        }
    }

    // Check flags at +0x28 bit 1: if set, override secondary with the current player's target
    if ((*(uint *)(thisPtr + 0x28) >> 1 & 1) != 0) {
        playerEntity = getCurrentPlayerEntity();
        if (playerEntity != 0) {
            secondaryTarget = *(int *)(playerEntity + 0x188);
        }
    }

    // Validate entity: if any target is stored, the entity must match primary and not equal secondary
    if (((primaryTarget != 0 || secondaryTarget != 0) && (entity != primaryTarget)) &&
        ((secondaryTarget == 0 || (entity == secondaryTarget)))) {
        return false; // entity is invalid (should be ignored)
    }
    return true; // entity is valid
}
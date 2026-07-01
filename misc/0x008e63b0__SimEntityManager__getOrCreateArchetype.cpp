// FUNC_NAME: SimEntityManager::getOrCreateArchetype
// Function address: 0x008e63b0
// Role: Selects an entity archetype (template) from a list based on a weighted random selection.
// Uses a static random seed table (DAT_010c2680) and a simple LCG counter (DAT_012054b4) to pick indices.
// Parameter: param_2 specifies whether to skip already-in-use archetypes (like marking as "claimed").

int __thiscall SimEntityManager::selectArchetype(int this, char bSkipClaimed)
{
    uint uCount = *(uint *)(this + 0x18); // +0x18: number of archetype entries
    if (uCount == 0) {
        return 0; // no archetypes available
    }

    // Seed index based on global random table and incrementing counter
    uint uSeedIdx = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1; // simple increment, no wrapping needed for LCG

    if (bSkipClaimed != '\0') {
        // Skip claimed (already used?) archetypes. Loop until we find an unclaimed one.
        float fWeight = (float)(int)(uCount - 1);
        if ((int)(uCount - 1) < 0) {
            fWeight = fWeight + DAT_00e44578; // handle negative, probably a floating-point adjustment for unsigned
        }
        uint uIndex = (uint)(longlong)ROUND(fWeight * *(float *)(&DAT_010c2680 + uSeedIdx * 4));

        uint uTried = 0;
        while (uTried < uCount) {
            int iArchetype = *(int *)(*(int *)(this + 0x14) + uIndex * 4); // +0x14: array of archetype pointers
            if (*(char *)(iArchetype + 0x1a5) == '\0') { // +0x1a5: 'claimed' flag (0=available)
                return iArchetype;
            }
            uTried++;
            uIndex = (uIndex + 1) % uCount;
        }
        return 0; // all claimed
    }

    // No skip claimed: just pick one based on weight and return.
    float fWeight = (float)(int)(uCount - 1);
    if ((int)(uCount - 1) < 0) {
        fWeight = fWeight + DAT_00e44578;
    }
    uint uIndex = (uint)(longlong)ROUND(fWeight * *(float *)(&DAT_010c2680 + uSeedIdx * 4));

    *(uint *)(this + 0x48) = uIndex; // +0x48: store last selected index (maybe for debug or rollback)
    return *(int *)(*(int *)(this + 0x14) + uIndex * 4);
}
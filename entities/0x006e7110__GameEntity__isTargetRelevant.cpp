// FUNC_NAME: GameEntity::isTargetRelevant

// Function at 0x006e7110: Checks if a given target (by ID) is relevant for this entity,
// based on distance to the player and component ownership.

// Offsets:
// this+0x44 - position x
// this+0x48 - position y
// this+0x4c - position z
// this+0x60 - pointer to a child component or owner (with vtable or size 0x48)
// this+0x8a - flags (bit 0: relevant check enabled)

// External helper: gets pointer to player's position (or some global actor)
extern Vector3* getPlayerPosition(); // assumed from FUN_00471610

// Global threshold for distance comparison
extern float g_relevanceDistanceThreshold; // _DAT_00d5fb0c

bool __thiscall GameEntity::isTargetRelevant(int thisPtr, int targetId)
{
    // Check if the relevance check is enabled
    if ((*(unsigned char*)(thisPtr + 0x8a) & 1) == 0)
    {
        // Flag not set -> treat as always relevant
        return true;
    }

    // Get the ID of this entity's component (owner/child at +0x60)
    int componentPtr = *(int*)(thisPtr + 0x60);
    int componentId;
    if (componentPtr == 0)
    {
        componentId = 0;
    }
    else
    {
        // The component pointer points to an object with a header;
        // subtracting 0x48 yields an ID (maybe offset in a pool)
        componentId = componentPtr - 0x48;
    }

    // If component ID matches the target, it's relevant
    if (componentId == targetId)
    {
        return true;
    }

    // If component pointer is null and no match, not relevant
    if (*(int*)(thisPtr + 0x60) == 0)
    {
        return false;
    }

    // If component size is exactly 0x48, skip distance test (treated as not relevant)
    if (*(int*)(thisPtr + 0x60) == 0x48)
    {
        return false;
    }

    // Get player position (first call, redundant but preserved from original)
    Vector3* playerPos = getPlayerPosition();
    float dx1 = playerPos->x - *(float*)(thisPtr + 0x44);
    float dy1 = playerPos->y - *(float*)(thisPtr + 0x48);
    float dz1 = playerPos->z - *(float*)(thisPtr + 0x4c);

    // Second call (same function) – seems to be identical; kept for structure
    playerPos = getPlayerPosition();
    float dx2 = playerPos->x - *(float*)(thisPtr + 0x44);
    float dy2 = playerPos->y - *(float*)(thisPtr + 0x48);
    float dz2 = playerPos->z - *(float*)(thisPtr + 0x4c);

    // Compute squared distance from player to this entity
    float distSq = dx1*dx1 + dy1*dy1 + dz1*dz1;

    // Compute offset distance from threshold (using second set)
    float rawDist = sqrtf(dx2*dx2 + dy2*dy2 + dz2*dz2) - g_relevanceDistanceThreshold;
    float adjustedSq = 0.0f;
    if (rawDist > 0.0f)
    {
        adjustedSq = rawDist * rawDist;
    }

    // If this entity is closer to the player than the adjusted range, it's relevant
    return distSq < adjustedSq;
}
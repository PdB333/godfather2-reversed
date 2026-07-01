// FUNC_NAME: CombatPerception::evaluateTarget
// Address: 0x0083b370
// This function evaluates a target position relative to the entity's position,
// checking distance thresholds and line-of-sight conditions.
// Returns 2 if condition met, 3 otherwise.

int __thiscall CombatPerception::evaluateTarget(
    void* thisPtr,
    float* targetPos,      // position of the target (3 floats)
    float* selfPos,        // position of this entity (3 floats)
    float minDistSq,       // minimum squared distance threshold
    float maxDistSq,       // maximum squared distance threshold
    float closeDistSq,     // threshold for close range (no LOS needed)
    float farDistSq,       // threshold for far range (LOS needed)
    uint flags             // additional flags (bit0 used for LOS override)
)
{
    float dx = targetPos[0] - selfPos[0];
    float dy = targetPos[1] - selfPos[1];
    float dz = targetPos[2] - selfPos[2];
    float distSq = dx*dx + dy*dy + dz*dz;

    // Check if distance is within the main range
    if (minDistSq <= distSq && distSq <= maxDistSq)
    {
        // Check if line-of-sight should be considered
        // Bit2 at offset 0xa8 indicates "ignore LOS" flag
        uint flagsAtA8 = *(uint*)((char*)thisPtr + 0xa8);
        bool ignoreLOS = (flagsAtA8 >> 2) & 1;
        bool losOverrideFlag = (flags & 0xFF) == 0; // low byte zero?

        if (!ignoreLOS && losOverrideFlag)
        {
            // Override LOS flag with bit18 from thisPtr+0xa8
            uint newFlags = (flags & 0xFFFFFF00) | ((flagsAtA8 >> 0x12) & 1);
            char losResult = checkLineOfSight(targetPos, 1, newFlags);
            if (losResult == 0)
            {
                // LOS failed: return based on close distance
                if (distSq > closeDistSq)
                    return 2;
                else
                    return 3;
            }
        }

        // LOS succeeded (or not required): return based on far distance
        if (distSq <= farDistSq)
            return 2;
    }

    return 3;
}
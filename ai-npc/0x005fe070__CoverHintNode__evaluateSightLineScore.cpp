// FUNC_NAME: CoverHintNode::evaluateSightLineScore
// Address: 0x005fe070
// Role: Computes a score for a sight line between two entities relative to this cover node's position.
// The score is based on dot product of direction vectors, with randomization and flag-based sign inversion.

int __thiscall CoverHintNode::evaluateSightLineScore(
    int *entityA,   // +0x00: index/id, +0x08: pointer to position (float[3])
    int *entityB    // same structure
) {
    float dotProduct;
    float randomFactor;
    float score;

    // Check internal state at +0xbc (possibly activity flag or reference count)
    int state = *(int *)(this + 0xbc);
    if (state == 0) {
        // No valid data, return random score
        int randVal = rand();
        return (int)((float)randVal * DAT_00e44590 * DAT_00e44670);
    }

    if (state > 0 && state < 3) {
        float dirA[3];
        if (state == 2) {
            // Use function that computes direction from this position to some target
            if (FUN_005fe020(&dirA) == 0) {
                return FUN_005fe000();
            }
        } else { // state == 1
            dirA[0] = *(float *)(this + 0x30);
            dirA[1] = *(float *)(this + 0x34);
            dirA[2] = *(float *)(this + 0x38);
        }

        // Get position of entityA
        float *posA;
        if (*entityA == 0) {
            posA = nullptr;
        } else {
            posA = (float *)entityA[2]; // +0x08 -> pointer
        }

        // Compute vector from entityA to this node's reference point
        float vecToThis[3];
        vecToThis[0] = dirA[0] - *posA;
        vecToThis[1] = dirA[1] - posA[1];
        vecToThis[2] = dirA[2] - posA[2];

        // Get position of entityB
        float *posB;
        if (*entityB == 0) {
            posB = nullptr;
        } else {
            posB = (float *)entityB[2];
        }

        // Compute vector from entityA to entityB
        float vecAToB[3];
        vecAToB[0] = *posB - *posA;
        vecAToB[1] = posB[1] - posA[1];
        vecAToB[2] = posB[2] - posA[2];

        // Normalize both vectors (FUN_0044d680 likely normalizes in place)
        FUN_0044d680(vecToThis, vecToThis);
        FUN_0044d680(vecAToB, vecAToB);

        // Dot product of the two normalized vectors
        dotProduct = vecAToB[0] * vecToThis[0] + 
                     vecAToB[1] * vecToThis[1] + 
                     vecAToB[2] * vecToThis[2];

        // Flag at +0xb4 bit 2 (value 0x4) indicates inverted direction
        if ((*(uint *)(this + 0xb4) >> 2 & 1) != 0) {
            dotProduct = DAT_00e44564 - dotProduct; // DAT_00e44564 likely 1.0
        }

        // Randomization based on field +0xb8 (probably a spread/randomization angle)
        float randomThreshold = *(float *)(this + 0xb8);
        if (DAT_00e2b05c < randomThreshold) {
            float r1 = FUN_005fd720();
            if (r1 < randomThreshold) {
                if (randomThreshold < DAT_00e2cd54) {
                    randomFactor = FUN_005fd720();
                } else {
                    randomFactor = DAT_00e2cd54 - FUN_005fd720();
                }
                dotProduct *= randomFactor;
            }
        }

        // Map dot product to an integer score
        score = dotProduct * DAT_00e44858 + DAT_00e44858;
        return (int)score;
    }

    return 0;
}
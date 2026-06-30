// FUNC_NAME: TargetingManager::selectTarget
int __thiscall TargetingManager::selectTarget(int targetType, char bRemove, const float* queryPosition, float minDistanceSq, bool (**filterFunc)(void*), float maxDistanceSq)
{
    int bestTarget = 0;                                      // local_40 - best candidate found
    float bestDistance = 999999.0f;                          // local_48 - best squared distance to query

    if (targetType == 0) {
        return 0;
    }

    // Get player physics object (position at offsets +0x30, +0x34, +0x38)
    int* playerPhysics = reinterpret_cast<int*>(getPlayerPhysics());
    float dirToQueryX = queryPosition[0] - *(float*)(playerPhysics + 0x30 / 4);   // +0x30
    float dirToQueryY = queryPosition[1] - *(float*)(playerPhysics + 0x34 / 4);   // +0x34
    float dirToQueryZ = queryPosition[2] - *(float*)(playerPhysics + 0x38 / 4);   // +0x38
    float dummy = 0.0f;
    normalizeVector(&dirToQueryX, &dirToQueryX);             // FUN_0056afa0

    // Iterate over entity list (array at +0x18, count at +0x1c)
    for (uint i = 0; i < *(uint*)(this + 0x1c); ++i) {
        int entity = *(int*)(*(int*)(this + 0x18) + i * 4);
        if (entity == 0) continue;
        if (*(char*)(entity + 0xa8) == 0) continue;         // +0xa8: active/alive flag

        int* typeField = reinterpret_cast<int*>(entity + 0x98);  // +0x98: category/type
        int effectiveType = 0;
        if ((*typeField != 0) && (*typeField != 0x48)) {
            if (*typeField == 0) {
                effectiveType = 0;
            } else {
                effectiveType = *typeField - 0x48;          // type = raw - 0x48 (except special 0x48)
            }
            if (effectiveType != targetType) {
                goto nextEntity;                            // type mismatch
            }
        }

        // Optional filter function
        if ((filterFunc != nullptr) && ((*filterFunc)(reinterpret_cast<void*>(entity)) == false)) {
            goto nextEntity;
        }

        // If bRemove flag set, remove the entity from the list (decrement count) if type matches
        if (bRemove != 0) {
            int tempType = 0;
            if (*typeField != 0) {
                tempType = *typeField - 0x48;
            }
            if (tempType == targetType) {
                if (*typeField != 0) {
                    decrementRefCount(typeField);            // FUN_004daf90
                    *typeField = 0;                         // clear type
                }
                (*(char*)(entity + 0xa8))--;                // +0xa8: decrement active count
                continue;
            }
        }

        // Compute squared distance from queryPosition to entity
        float dx = queryPosition[0] - *(float*)(entity + 0x6c);  // +0x6c: position X
        float dy = queryPosition[1] - *(float*)(entity + 0x70);  // +0x70: position Y
        float dz = queryPosition[2] - *(float*)(entity + 0x74);  // +0x74: position Z
        float distSqToQuery = dx*dx + dy*dy + dz*dz;

        if (distSqToQuery > maxDistanceSq) continue;       // outside max range
        if (distSqToQuery < minDistanceSq) continue;       // too close

        // Random chance based on entity's probability at +0xa0
        float chance = *(float*)(entity + 0xa0);            // +0xa0: probability/aggression
        float randVal = static_cast<float>(rand()) * (1.0f / RAND_MAX);  // DAT_00e44590 is likely 1.0f/RAND_MAX
        if (randVal >= chance) continue;                    // not selected by RNG

        // Compute direction from player to this entity
        float dirToEnemyX = *(float*)(entity + 0x6c) - *(float*)(playerPhysics + 0x30 / 4);
        float dirToEnemyY = *(float*)(entity + 0x70) - *(float*)(playerPhysics + 0x34 / 4);
        float dirToEnemyZ = *(float*)(entity + 0x74) - *(float*)(playerPhysics + 0x38 / 4);
        normalizeVector(&dirToEnemyX, &dirToEnemyX);        // FUN_0043a210

        float distSqToPlayer = dirToEnemyX*dirToEnemyX + dirToEnemyY*dirToEnemyY + dirToEnemyZ*dirToEnemyZ;

        // Check if entity is within player-relative distance limit
        float playerDistLimit = *(float*)(entity + 0xa4);   // +0xa4: max distance from player
        if (distSqToPlayer > playerDistLimit) continue;

        if (distSqToPlayer > bestDistance) continue;        // already have a closer candidate

        // Compute dot product between direction-to-query and direction-to-enemy (both from player)
        float dot = dirToQueryX * dirToEnemyX + dirToQueryY * dirToEnemyY + dirToQueryZ * dirToEnemyZ;
        // DAT_00d5fb04 is likely a threshold for the angle (e.g. -0.5 for 120 degrees)
        if (dot > -0.5f) continue;                          // require enemy to be opposite to query direction?

        // If enemy is very close to player, select immediately
        if (distSqToPlayer < 4.0f) {                        // DAT_00d5ddec = some small distance squared
            return entity;
        }

        // Otherwise update best candidate
        bestDistance = distSqToQuery;
        bestTarget = entity;

nextEntity:
        ;
    }
    return bestTarget;
}
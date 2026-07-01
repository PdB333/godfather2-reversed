// FUNC_NAME: CombatPerception::checkVisibility
bool CombatPerception::checkVisibility(int targetObj, int* queryParams, uint* outFlags)
{
    // +0x8 in targetObj: type ID (0 = invalid, 0x48 = special?)
    int typeId = *(int*)(targetObj + 8);
    if (typeId == 0 || typeId == 0x48)
        return false;

    // Adjust typeId by subtracting 0x48 (if not zero)
    int adjustedTypeId = (typeId == 0) ? 0 : (typeId - 0x48);

    // Compare with queryParams[0x1f] (31) - likely a specific type filter
    bool typeMatch = queryParams[0x1f] == adjustedTypeId;

    // Get observer position (local_34, local_30, local_2c) - XYZ order?
    float observerX, observerY, observerZ;
    FUN_00819200(&observerX);  // fills local_34, local_30, local_2c (likely via pointer output)

    // If type doesn't match, compute squared distance to target
    if (!typeMatch)
        return typeMatch; // early exit if type mismatch

    // Compute squared distance between observer and target (target pos at queryParams[0xf..0x11])
    float targetX = (float)queryParams[0x0f]; // 15
    float targetY = (float)queryParams[0x10]; // 16
    float targetZ = (float)queryParams[0x11]; // 17
    float dx = observerX - targetX;
    float dy = observerY - targetY;
    float dz = observerZ - targetZ;
    float sqDist = dx*dx + dy*dy + dz*dz;

    // Maximum allowed squared distance from queryParams[0x2e] (46)
    float maxDistSq = (float)queryParams[0x2e];
    if (maxDistSq <= sqDist && sqDist != maxDistSq)
        return false;

    // Another distance threshold from global _DAT_00d577a0
    float thresholdDist = (float)(*(int*)0x00d577a0);  // global
    if (thresholdDist <= sqDist && sqDist < maxDistSq && ((queryParams[0x1c] & 6) == 0))
    {
        // Check for special ID match (queryParams[0x1f] vs target type)
        int idQuery = (queryParams[0x1f] == 0) ? 0 : (queryParams[0x1f] - 0x48);
        int result = FUN_007450a0(idQuery, &typeId);  // compare IDs
        if (result != 0)
            return false;
    }

    // Check flag: if bit 1 (0x2) is set in queryParams[0x1b], return true immediately
    if ((queryParams[0x1b] & 2) != 0)
        return typeMatch;

    // Additional early exit: if sqDist <= global DAT_00d73238 and thresholdDist < global threshold
    if (sqDist <= *(float*)0x00d73238 && sqDist < thresholdDist)
        return typeMatch;

    // Compute vector from observer to target
    float vecToTarget[3];
    vecToTarget[0] = observerX - (float)queryParams[3]; // observer position from queryParams[3-5] ?
    vecToTarget[1] = observerY - (float)queryParams[4];
    vecToTarget[2] = observerZ - (float)queryParams[5];

    // Access per-object data array at this +0x24, indexed by queryParams[0] * 0x1c
    int* objectDataBase = *(int**)(this + 0x24);
    int index = queryParams[0];
    int* objectEntry = &objectDataBase[index * 0x1c]; // 0x1c = 28 bytes per entry

    // Transform vector into local space using rotation matrix at queryParams+9
    float transformed[3];
    FUN_004a07f0(&transformed, vecToTarget, &queryParams[9]); // rotate by matrix
    FUN_0043a210(&transformed, &transformed); // normalize

    // Compute dot product with forward direction (queryParams[6],[7],[8])
    float forwardDot = (float)queryParams[6] * transformed[0] +
                       (float)queryParams[7] * transformed[1] +
                       (float)queryParams[8] * transformed[2];

    // Clamp forwardDot to [DAT_00d5ccf8, _DAT_00d5780c]
    float minDot = *(float*)0x00d5ccf8;
    float maxDot = *(float*)0x00d5780c;
    if (forwardDot < minDot)
    {
        *outFlags |= 1;
        forwardDot = minDot;
    }
    else if (forwardDot > maxDot)
    {
        forwardDot = maxDot;
    }

    // Apply per-object type modifier based on byte at objectEntry+0x14
    byte flags = *(byte*)(objectEntry + 0x14); // +0x14: flags/type info
    if ((flags & 3) == 3)
    {
        forwardDot = (float)((uint)forwardDot & *(uint*)0x00e44680); // bitwise AND on float?
    }
    else if ((flags & 2) == 2)
    {
        forwardDot = forwardDot * minDot; // scale by minDot (global)
    }

    // Compare with threshold at objectEntry+4
    float threshold1 = *(float*)(objectEntry + 4);
    double threshold1Double = (double)threshold1;
    FUN_00b99e20(); // presumably converts double to float? Or does nothing?
    if (forwardDot < (float)threshold1Double)
    {
        if ((queryParams[0x1b] & 0x20) == 0)
            return false;
        *outFlags |= 1;
    }

    // Second orientation test: using another rotation matrix at queryParams+0xc
    float transformed2[3];
    FUN_004a07f0(&transformed2, vecToTarget, &queryParams[0xc]);
    FUN_0043a210(&transformed2, &transformed2);

    float forwardDot2 = (float)queryParams[6] * transformed2[0] +
                        (float)queryParams[7] * transformed2[1] +
                        (float)queryParams[8] * transformed2[2];

    // Clamp again
    if (forwardDot2 < minDot)
        forwardDot2 = minDot;
    else if (forwardDot2 > maxDot)
        forwardDot2 = maxDot;

    double threshold2Double = (double)*(float*)(objectEntry + 8);
    FUN_00b99e20();
    if (forwardDot2 < (float)threshold2Double)
    {
        if ((queryParams[0x1b] & 0x20) == 0)
            return false;
        *outFlags |= 1;
    }

    return typeMatch;
}
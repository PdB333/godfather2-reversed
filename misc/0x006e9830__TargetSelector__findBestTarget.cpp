// FUNC_NAME: TargetSelector::findBestTarget
// Address: 0x006e9830
// Reconstructed from Ghidra decompilation of The Godfather 2 (2008, EA EARS engine, x86)
// Role: Finds the best target among a list of candidate entities for an owner, with optional filter and removal of owned targets.

int __thiscall TargetSelector::findBestTarget(int this, int ownerEntity, char bRemoveIfOwned, int (*pFilterCallback)(int targetEntity))
{
    float *targetPos;
    float dist;
    float bestDist;
    char isValid;
    int *pOwner;
    int numEntities;
    int entityIdx;
    int entityPtr;
    int bestTarget;
    int cameraTransform;
    float *cameraPos;
    int playerTransform2;
    float dirVector1[3];
    float dirVector2[3];
    float toTarget[3];
    float dot1, dot2;
    float bestDistSq = 1e30f; // Actually stored at local_34, initialized from DAT_00d5f6f0 (some large float)
    int bestTargetOut = 0;

    // Initialize bestDist from a global constant (maybe max search distance?)
    bestDist = DAT_00d5f6f0; // Global float constant

    if (ownerEntity == 0)
        return 0;

    // Determine the owner's team/group ID from the entity at +0x24c4
    int *pOwnerGroup = *(int **)(ownerEntity + 0x24c4);
    int ownerGroupId;
    if (pOwnerGroup == 0)
    {
        // Fallback: get from global singleton (maybe player's crew leader)
        int *pGlobal = (int *)FUN_00722220();
        if (pGlobal != 0)
        {
            if (*pGlobal == 0)
                ownerGroupId = 0;
            else
                ownerGroupId = *pGlobal - 0x48; // Subtract base offset
        }
        else
            ownerGroupId = 0;
    }
    else
    {
        ownerGroupId = (int)(pOwnerGroup - 0x48); // Subtract base offset (0x48)
        if (ownerGroupId != 0)
            goto LAB_006e988e;
        // If zero, fallback to global
        int *pGlobal = (int *)FUN_00722220();
        if (pGlobal != 0)
        {
            if (*pGlobal == 0)
                ownerGroupId = 0;
            else
                ownerGroupId = *pGlobal - 0x48;
        }
    }

LAB_006e988e:
    // Get a pointer to a list of all entities (maybe from SimManager via global pointer)
    int *entityList = **(int ***)(DAT_012233a0 + 4); // Global pointer chain
    if (entityList == 0 || entityList == (int *)0x1f30)
        return 0;

    // Get total entity count from virtual function at offset 0xc (likely getCount())
    numEntities = (*(int (__thiscall **)(int *))(*(int *)entityList + 0xc))(entityList);
    if (numEntities == 0 || ownerGroupId == 0)
        return 0;

    // Get two transforms (player/camera positions) - possibly current and previous?
    cameraTransform = FUN_00471610();
    cameraPos = (float *)(cameraTransform + 0x30); // Position offset
    playerTransform2 = FUN_00471610();
    // Compute direction vector from first to second (or from camera to something?)
    dirVector1[0] = *(float *)(playerTransform2 + 0x30) - *cameraPos;
    dirVector1[1] = *(float *)(playerTransform2 + 0x34) - *(float *)(cameraTransform + 0x34);
    dirVector1[2] = *(float *)(playerTransform2 + 0x38) - *(float *)(cameraTransform + 0x38);
    FUN_0043a210(dirVector1, dirVector1); // Normalize

    // Do it again (maybe for a different reference?)
    playerTransform2 = FUN_00471610();
    dirVector2[0] = *(float *)(playerTransform2 + 0x30) - *cameraPos;
    dirVector2[1] = *(float *)(playerTransform2 + 0x34) - *(float *)(cameraTransform + 0x34);
    dirVector2[2] = *(float *)(playerTransform2 + 0x38) - *(float *)(cameraTransform + 0x38);
    FUN_0043a210(dirVector2, dirVector2); // Normalize

    // Iterate over all candidate targets stored in this->list (array of pointers at +0x18, count at +0x1c)
    for (int i = 0; i < *(int *)(this + 0x1c); i++)
    {
        entityPtr = *(int *)(*(int *)(this + 0x18) + i * 4);
        targetPos = (float *)(entityPtr + 0x6c); // Target position offset

        if (bRemoveIfOwned != 0)
        {
            // Handle removal of targets owned by this owner
            pOwner = (int *)(entityPtr + 0x98);
            int entityOwnerId;
            if (*(int *)(entityPtr + 0x98) == 0)
                entityOwnerId = 0;
            else
                entityOwnerId = *(int *)(entityPtr + 0x98) - 0x48;

            if (entityOwnerId == ownerEntity)
            {
                // Clear the owner pointer and decrement a count
                if (*pOwner != 0)
                {
                    FUN_004daf90(pOwner); // Likely decrements reference or removes entry
                    *pOwner = 0;
                }
                *(char *)(entityPtr + 0xa8) -= 1; // Decrement some counter (e.g., reference count)
                // Fall through to normal evaluation (or continue? Actually goes to LAB_006e99df)
            }
            // If owner doesn't match, still evaluate normally
            goto LAB_006e99df;
        }

LAB_006e99df:
        // Check if target is valid
        if (entityPtr != 0 &&
            (isValid = FUN_006e9300(ownerEntity), isValid != 0) &&
            (isValid = FUN_00718d40(targetPos), isValid != 0) &&
            (pFilterCallback == 0 || (*(int (__thiscall **)(int))*pFilterCallback)(entityPtr) == 0))
        {
            // Compute squared distance from camera to target
            dist = (float)FUN_0045c470(cameraPos, targetPos);

            // If distance is less than 1 (very close), immediately return this target
            if (dist < 1.0f)
                return entityPtr;

            // Check if target is within vertical tolerance
            float dy = *(float *)(cameraTransform + 0x34) - *(float *)(entityPtr + 0x70);
            if (fabsf(dy) < DAT_00d5eee4 && // Vertical angle threshold
                (float)_rand() * DAT_00e44590 < *(float *)(entityPtr + 0xa0) && // Probability check
                dist < *(float *)(entityPtr + 0xa4) && // Target's max range
                dist < bestDist) // Better than current best
            {
                // Compute direction vector to target
                toTarget[0] = *targetPos - *cameraPos;
                toTarget[1] = *(float *)(entityPtr + 0x70) - *(float *)(cameraTransform + 0x34);
                toTarget[2] = *(float *)(entityPtr + 0x74) - *(float *)(cameraTransform + 0x38);
                FUN_0043a210(toTarget, toTarget); // Normalize

                // Check dot product: target must be within certain cone (forward direction)
                dot1 = toTarget[1] * dirVector1[1] + toTarget[0] * dirVector1[0] + toTarget[2] * dirVector1[2];
                if (dot1 < DAT_00d5fb04 && // Cone threshold 1
                    (ownerGroupId == numEntities || 
                     (dot2 = toTarget[1] * dirVector2[1] + toTarget[0] * dirVector2[0] + toTarget[2] * dirVector2[2],
                      dot2 < DAT_00d5fb04))) // Cone threshold 2 (applies if owner group != numEntities)
                {
                    bestTargetOut = entityPtr;
                    bestDist = dist;
                }
            }
        }
    }

    return bestTargetOut;
}
// FUNC_NAME: AIState::ShouldConsiderTarget
uint __thiscall AIState::ShouldConsiderTarget(AIState *thisState, PotentialTargetInfo *targetInfo)
{
    int iVar3;
    uint uVar2;
    float distanceSquared;
    float threshold;
    uint targetHandle1;
    uint targetHandle2;

    // Compute handle from targetInfo->entity2 (offset +0x0c)
    if (targetInfo->entity2 == (Entity *)0x0) {
        uVar2 = 0;
    }
    else {
        // Convert entity pointer to handle by subtracting 0x48
        uVar2 = (uint)targetInfo->entity2 - 0x48;
    }

    // Check if current stored handle matches this
    if (uVar2 != thisState->currentHandle) { // offset +0x10
        // Recompute using entity1 (+0x04)
        if (targetInfo->entity1 == (Entity *)0x0) {
            uVar2 = 0;
        }
        else {
            uVar2 = (uint)targetInfo->entity1 - 0x48;
        }
        if (uVar2 != thisState->currentHandle) {
            // Neither handle matches the stored handle, proceed to distance check

            // Get camera/player transform (FUN_00471610) and compute squared distance to target position
            Transform *pTransform = GetCameraTransform(); // returns pointer to 3 floats at +0x30, +0x34, +0x38
            float dx = pTransform->x - targetInfo->position.x; // +0x18
            float dy = pTransform->y - targetInfo->position.y; // +0x1c
            float dz = pTransform->z - targetInfo->position.z; // +0x20
            distanceSquared = dx*dx + dy*dy + dz*dz;

            // Compute threshold squared based on targetInfo->radius (+0x14) and global multiplier
            float baseRadius = targetInfo->radius;
            float globalMultiplier = *(float*)0x00e5175c; // DAT_00e5175c
            float threshold = (float)FUN_007131b0(*(undefined4 *)&baseRadius, globalMultiplier);
            // Note: FUN_007131b0 likely returns squared threshold? We'll treat its result as radius, then compare squares.

            // Check game state conditions
            bool bSkipCondition = false;
            if (thisState->currentHandle == 0 ||
                (iVar3 = FUN_0043b870(DAT_0113105c), iVar3 == 0) ||
                (iVar3 = FUN_009b2900(), iVar3 == 0))
            {
                // Falls into this branch: set iVar3 = 0 and keep current distanceSquared
                iVar3 = 0;
            }
            else
            {
                // Game is not paused and player exists: get player handle
                iVar3 = FUN_009b2900(); // presumably returns player handle
            }

            // Compare squared threshold with actual squared distance
            if ((threshold * threshold) <= distanceSquared) {
                // Target is far enough (distance >= threshold): check entity validity
                // Compute handles again from targetInfo
                uint handleFromEntity1 = (targetInfo->entity1 != (Entity *)0x0) ? ((uint)targetInfo->entity1 - 0x48) : 0;
                uint handleFromEntity2 = (targetInfo->entity2 != (Entity *)0x0) ? ((uint)targetInfo->entity2 - 0x48) : 0;

                // If iVar3 (player handle) doesn't match entity1 handle
                if (iVar3 != handleFromEntity1) {
                    // And also doesn't match entity2 handle
                    if (iVar3 != handleFromEntity2) {
                        // Check if entity1 is valid; if not, check entity2
                        // Note: iVar3 is being reused; the code sets iVar3 = handleFromEntity1
                        uint handleToCheck;
                        if (targetInfo->entity1 != (Entity *)0x0) {
                            handleToCheck = (uint)targetInfo->entity1 - 0x48;
                        }
                        else {
                            handleToCheck = 0;
                        }
                        bool bEntity1Valid = FUN_007167e0(handleToCheck); // IsEntityAlive
                        if (bEntity1Valid == false) {
                            if (targetInfo->entity2 != (Entity *)0x0) {
                                handleToCheck = (uint)targetInfo->entity2 - 0x48;
                            }
                            else {
                                handleToCheck = 0;
                            }
                            bool bEntity2Valid = FUN_007167e0(handleToCheck);
                            if (bEntity2Valid == false) {
                                // Neither entity is valid -> irrelevant
                                return 0;
                            }
                        }
                    }
                }
                // At least one condition satisfied -> relevant
                return 1;
            }
            // Distance is less than threshold -> still relevant
            return 1;
        }
    }
    // Stored handle matches one of the target handles -> return high bits of handle (?) 
    // This path is returning uVar2 & 0xffffff00, potentially a flag
    return uVar2 & 0xffffff00;
}
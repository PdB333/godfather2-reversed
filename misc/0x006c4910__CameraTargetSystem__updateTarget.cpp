// FUNC_NAME: CameraTargetSystem::updateTarget

void CameraTargetSystem::updateTarget(float *outputSmoothParam, float *currentPos, int *transformMatrix, float *targetPos, float *lookAtPos, float speedMult, float distDivisor)
{
    // Stack locals for vector operations
    float crossX, crossY, crossZ;
    float dummy0, dummy1, dummy2;
    float normalizedDir[3];
    float local_90[3]; // transformed direction
    float local_30[3]; // from earlier operations
    float local_28[3];
    float local_d0[3]; // cross product
    float local_a4; // computed distance factor
    float local_a0; // final length
    float local_b4; // clamped value

    // Initialize globals used as constants
    float maxThreshold = _DAT_00d5780c; // e.g., 1.0
    float minThreshold = DAT_00d5ef88;
    float scaleFactor = _DAT_00d5eff0;
    float clampFactor = _DAT_00e50f8c;
    uint bitmask = DAT_00e44680; // maybe for float-to-int bit manipulation
    float earlyReturnDist = DAT_00e50de4;
    float blendSpeedHigh = _DAT_00e50f84;
    float blendSpeedLow = _DAT_00e50f88;

    // Zero out initial vectors
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = maxThreshold;

    // Get a reference direction (likely world up or forward)
    FUN_00425060(&local_68, 0); // zero local_68 ? (local_68, local_60, local_5c etc)
    FUN_0056b8a0(local_64, local_68, local_60, local_50); // compute something

    local_d0[0] = local_30[0];
    local_d0[1] = 0.0f;
    local_d0[2] = local_28[2];
    FUN_0056afa0(&local_d0, &local_d0); // normalize

    // Cross product: local_d0 x (0,1,0) => local_cc, local_c8, local_d0 new
    float fVar3 = local_cc * 0.0f;
    float fVar4 = fVar3 - local_c8;
    local_cc = local_c8 * 0.0f - local_d0[0] * 0.0f;
    local_c8 = local_d0[0] - fVar3;
    local_d0[0] = fVar4;
    // The above is (local_d0 x {0,1,0})
    FUN_0056afa0(&local_d0, &local_d0); // normalize again

    // Compute distance between targetPos and lookAtPos
    float dx = targetPos[0] - lookAtPos[0];
    float dy = targetPos[1] - lookAtPos[1];
    float dz = targetPos[2] - lookAtPos[2];
    float dist = sqrtf(dx*dx + dy*dy + dz*dz) / distDivisor;

    if (dist > 0.0f) {
        if (dist >= maxThreshold) {
            local_a4 = (maxThreshold - minThreshold) * scaleFactor;
            goto LAB_006c4ab7;
        }
        if (dist > minThreshold) {
            local_a4 = (dist - minThreshold) * scaleFactor;
            goto LAB_006c4ab7;
        }
    }
    local_a4 = 0.0f;

LAB_006c4ab7:
    local_a4 *= speedMult;

    // Transform vector (probably local direction to world)
    FUN_006c0dd0(&local_90, currentPos, transformMatrix);
    local_78 = local_90[0] - currentPos[0];
    local_74 = local_90[1] - currentPos[1];
    local_70 = local_90[2] - currentPos[2];

    // Get some global singleton (maybe camera or player) and read its position/offset
    int *globalPtr = FUN_00471610();
    float globalX = *(float *)(globalPtr + 0x30);
    float globalZ = *(float *)(globalPtr + 0x38); // note: offset 0x38 is likely Y, but variable names depend on engine

    local_b0 = (float)(double)(globalX);
    local_b0 += local_78;
    fStack_ac = local_74 + currentPos[1];
    local_9c = local_d0[0] * local_a4 + local_b0;
    local_98 = local_cc * local_a4 + fStack_ac;
    local_a8 = globalZ + local_70;
    local_94 = local_c8 * local_a4 + local_a8;

    // Compare two functions to get a minimum factor
    float result1 = FUN_006c9b00(&local_b0, &local_9c, 0, 0);
    float result2 = FUN_006c9cc0(&local_b0, &local_9c, 2);
    local_b4 = result2;
    if (result2 < result1) {
        result1 = local_b4;
    }

    // Compute offset from predicted position to original target
    local_8c = local_98 - fStack_ac;
    local_88 = local_94 - local_a8;
    local_90[0] = local_9c - local_b0;
    local_90[1] = local_8c;
    local_90[2] = local_88;
    local_a0 = sqrtf(local_88*local_88 + local_8c*local_8c + local_90[0]*local_90[0]);
    local_84 = 0;
    FUN_0056afa0(&local_90, &local_90); // normalize direction

    if (result1 < maxThreshold) {
        result1 *= clampFactor;
    }

    local_a0 *= result1;
    // Final look-at position
    local_9c = local_d0[0] * local_a0 + local_b0;
    local_98 = local_cc * local_a0 + fStack_ac;
    local_94 = local_c8 * local_a0 + local_a8;

    // Clamp movement
    local_6c = (float)((uint)(local_a4) & bitmask);
    local_b4 = local_6c;
    if (local_a0 < local_6c) {
        local_b4 = local_a0;
    }

    // Call virtual function on transformMatrix (offset 0x4c) - likely setPosition or setLookAt
    (**(code **)(*transformMatrix + 0x4c))(local_5c); // note: local_5c is undefined? Might be a struct.

    float fVar3_local = local_a8;
    if ((float)((uint)(*outputSmoothParam) & bitmask) <= fStack_b8) {
        if (sqrtf(fStack_58 * fStack_58 + local_60 * local_60) <= earlyReturnDist) {
            return;
        }
        // else fall through with uVar5 = blendSpeedHigh
    }
    else {
        // uVar5 = blendSpeedLow
        if ((float)((uint)(local_a4) & bitmask) < local_70) {
            fVar3_local = local_a4;
        }
    }

    float blendFactor = FUN_006c89b0(*outputSmoothParam, fVar3_local, uVar5); // uVar5 chosen above
    *outputSmoothParam = blendFactor;
}
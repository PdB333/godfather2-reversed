// FUNC_NAME: PathFollower::advance
int __thiscall PathFollower::advance(int this, float remainingDistance, char bDoCollision, char bUseSliding, float *pOutCollisionData)
{
    int *piVar1;
    undefined4 *puVar2;
    float *pfVar3;
    undefined4 *puVar4;
    int iVar5;
    float fVar6;
    float fVar7;
    undefined4 uVar8;
    undefined4 uVar9;
    undefined4 uVar10;
    float fVar11;
    float fVar12;
    float local_68; // remaining distance (scaled)
    float local_64; // used as temporary
    int local_60; // return status
    float local_5c, local_58, local_54; // target position components
    float local_50, local_4c, local_48; // delta components
    float local_44; // temp for collision
    undefined4 local_40;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    float local_30, local_2c, local_28, local_24; // interpolated position
    float local_20, fStack_1c, fStack_18; // saved position components
    undefined4 uStack_14; // saved position w

    // +0x88: pointer to path data? If null, fail and set flag 0x8001
    if (*(int *)(this + 0x88) == 0) {
        *(uint *)(this + 0xb4) |= 0x8001;
        return 4; // 4 = no path
    }

    // +0xb0: speed scale factor
    remainingDistance = *(float *)(this + 0xb0) * remainingDistance;
    fVar6 = 0.0f;
    puVar2 = *(undefined4 **)(this + 0x90); // +0x90: path point array
    local_60 = 0;
    local_68 = remainingDistance;

    if (remainingDistance > 0.0f) {
        while( true ) {
            fVar7 = *(float *)(this + 0xc0) + remainingDistance; // +0xc0: current segment distance
            *(float *)(this + 0xc0) = fVar7;
            // Check if we can advance without exceeding segment length
            if ((fVar7 < *(float *)(this + 0xc4)) && // +0xc4: segment length
                (((*(uint *)(this + 0xb4) >> 0xc & 1) == 0) ||
                 (DAT_00e2b04c <= *(float *)(this + 0xc4) - fVar7))) break;

            // Segment completed: zero out velocity (+0x20..0x2c)
            *(float *)(this + 0x2c) = 0.0f;
            *(float *)(this + 0x28) = 0.0f;
            *(float *)(this + 0x24) = 0.0f;
            *(float *)(this + 0x20) = 0.0f;

            // Save current position (this +0x10..0x1c)
            fVar7 = *(float *)(this + 0x10);
            uVar8 = *(undefined4 *)(this + 0x14);
            uVar9 = *(undefined4 *)(this + 0x18);
            uVar10 = *(undefined4 *)(this + 0x1c);
            local_20 = fVar7;
            fStack_1c = (float)uVar8;
            fStack_18 = (float)uVar9;
            uStack_14 = uVar10;

            // +0x40: flag indicating if we are interpolating along a path? (byte)
            if ((*(char *)(this + 0x40) == '\0') || ((*(uint *)(this + 0xb4) >> 0xc & 1) != 0)) {
                local_60 = FUN_005ff4b0(&local_68); // get next segment, returns status (0,1,2?)
                if ((*(uint *)(this + 0xb4) >> 0xc & 1) == 0) {
                    if (local_60 == 1) {
                        fVar6 = 0.0f;
                        break;
                    }
                }
                else {
                    // Save target position for collision detection
                    *(float *)(this + 0x60) = local_20;
                    *(float *)(this + 0x64) = fStack_1c; // +0x64 = 100? Actually 0x64 = 100 decimal
                    *(float *)(this + 0x68) = fStack_18;
                    *(undefined4 *)(this + 0x6c) = uStack_14;
                    // Clear bit 0xc (4096) in flags
                    *(uint *)(this + 0xb4) &= 0xffffefff;
                    *(undefined4 *)(this + 0xc0) = DAT_00e2fc48; // reset segment distance
                    // Compute new segment length
                    fVar11 = *(float *)(this + 0x68) - *(float *)(this + 0x18);
                    fVar7 = *(float *)(this + 0x64) - *(float *)(this + 0x14);
                    fVar6 = *(float *)(this + 0x60) - *(float *)(this + 0x10);
                    *(float *)(this + 0xc4) = SQRT(fVar11 * fVar11 + fVar7 * fVar7 + fVar6 * fVar6);
                }
                fVar6 = 0.0f;
                remainingDistance = local_68;
            }
            else {
                // Clean up previous path segment
                piVar1 = (int *)(this + 0x44);
                *(undefined1 *)(this + 0x40) = 0;
                if (*piVar1 != 0) {
                    FUN_004daf90(piVar1); // free/delete?
                    *piVar1 = 0;
                }
                // Determine alternative path source
                if (*(int *)(this + 0x7c) == 0) {
                    puVar4 = (undefined4 *)0x0;
                }
                else {
                    puVar4 = *(undefined4 **)(this + 0x84);
                }
                // Set current position from path point array
                *(undefined4 *)(this + 0x10) = *puVar2;
                *(undefined4 *)(this + 0x14) = puVar2[1];
                *(undefined4 *)(this + 0x18) = puVar2[2];
                if ((puVar4 == (undefined4 *)0x0) || (bUseSliding != '\0')) {
                    // No secondary path: just reset segment
                    *(float *)(this + 0xc0) = 0.0f;
                    *(float *)(this + 0x60) = fVar7; // fVar7 still has old position x?
                    *(undefined4 *)(this + 0x64) = uVar8;
                    *(undefined4 *)(this + 0x68) = uVar9;
                    *(undefined4 *)(this + 0x6c) = uVar10;
                    // Recompute segment length
                    fVar12 = *(float *)(this + 0x68) - *(float *)(this + 0x18);
                    fVar11 = *(float *)(this + 0x64) - *(float *)(this + 0x14);
                    fVar7 = *(float *)(this + 0x60) - *(float *)(this + 0x10);
                    *(float *)(this + 0xc4) = SQRT(fVar12 * fVar12 + fVar11 * fVar11 + fVar7 * fVar7);
                    *(undefined4 *)(this + 0xe0) = 0; // counter?
                }
                else {
                    // Use secondary path (sliding)
                    *(undefined4 *)(this + 0x60) = *puVar4;
                    *(undefined4 *)(this + 0x64) = puVar4[1];
                    *(undefined4 *)(this + 0x68) = puVar4[2];
                    // Recompute segment length from new target
                    fVar12 = *(float *)(this + 0x68) - *(float *)(this + 0x18);
                    fVar11 = *(float *)(this + 0x64) - *(float *)(this + 0x14);
                    fVar7 = *(float *)(this + 0x60) - *(float *)(this + 0x10);
                    *(float *)(this + 0xc4) = SQRT(fVar12 * fVar12 + fVar11 * fVar11 + fVar7 * fVar7);
                    // Prepare for collision line test
                    local_44 = local_20;
                    local_40 = fStack_1c;
                    local_3c = fStack_18;
                    local_5c = *(float *)(this + 0x60);
                    local_58 = *(float *)(this + 0x64);
                    local_54 = *(float *)(this + 0x68);
                    local_30 = *(float *)(this + 0x10);
                    local_2c = *(float *)(this + 0x14);
                    local_28 = *(float *)(this + 0x18);
                    local_50 = fVar6; // 0.0
                    local_4c = fVar6;
                    local_48 = fVar6;
                    FUN_005fd8d0(&local_44); // maybe adjust for collision?
                    // Set segment distance: length of delta + constant
                    *(float *)(this + 0xc0) = SQRT((local_54 - local_48) * (local_54 - local_48) +
                                                   (local_58 - local_4c) * (local_58 - local_4c) +
                                                   (local_5c - local_50) * (local_5c - local_50)) + DAT_00e2b1a4;
                    fVar6 = 0.0f;
                    *(undefined4 *)(this + 0xe0) = 0;
                    remainingDistance = local_68;
                }
            }
            // Check if we still have distance to move
            if (remainingDistance <= fVar6) {
                return local_60;
            }
            // Check stop flag (bit 0)
            if ((*(byte *)(this + 0xb4) & 1) != 0) {
                return local_60;
            }
        } // end while

        // Handle break case: segment not fully traversed
        if (*(char *)(this + 0x40) == '\0') {
            // Set position from path point array (safe position)
            *(undefined4 *)(this + 0x10) = *puVar2;
            *(undefined4 *)(this + 0x14) = puVar2[1];
            *(undefined4 *)(this + 0x18) = puVar2[2];
        }
        fVar7 = fVar6; // 0.0
        fVar11 = fVar6;
        fVar12 = fVar6;
        if (fVar6 < *(float *)(this + 0xc4)) {
            // Interpolate between current and target based on progress ratio
            FUN_004f1ce0(this + 0x60, this + 0x10,
                         *(float *)(this + 0xc0) / *(float *)(this + 0xc4), &local_30);
            fVar6 = local_30;
            fVar7 = local_2c;
            fVar11 = local_28;
            fVar12 = local_24;
        }
        local_24 = fVar12;
        local_28 = fVar11;
        local_2c = fVar7;
        local_30 = fVar6;
        local_5c = local_30;
        local_58 = local_28;

        if (*(int *)(this + 0x88) != 0) {
            // Save original path point
            pfVar3 = *(float **)(this + 0x90);
            local_68 = *pfVar3;
            fStack_1c = pfVar3[1];
            local_64 = pfVar3[2];
            local_20 = local_68;
            fStack_18 = local_64;

            // Collision detection (if requested)
            if ((bDoCollision != '\0') && ((*(byte *)(this + 0xb6) & 1) == 0)) {
                local_44 = 0.0f;
                local_40 = 0;
                local_3c = DAT_00e4458c;
                local_38 = 0;
                local_34 = 0xffffffff;
                if (pOutCollisionData == (float *)0x0) {
                    pOutCollisionData = &local_44;
                }
                if (bUseSliding == '\0') {
                    iVar5 = FUN_005ffeb0(&local_5c, &local_68, &local_30, pOutCollisionData); // wall collision?
                }
                else {
                    iVar5 = FUN_005ffc10(&local_5c, &local_68, &local_20, pOutCollisionData); // floor collision?
                }
                if (iVar5 == 2) {
                    return 2; // collision impact
                }
            }
            local_60 = 1; // movement completed
            FUN_005ff0e0(); // finalize movement (e.g., apply to physics)
            return local_60;
        }
    }
    return 0; // no movement (or already at target)
}
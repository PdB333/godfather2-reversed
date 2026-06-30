// FUNC_NAME: SimNpc::updatePhysics
// Address: 0x006c5ee0
// This function is the main per-frame physics update for an NPC (SimNpc) in The Godfather 2.
// It handles position, velocity, rotation, state transitions, collision, and AI behavior.
// The object has an extensive set of fields (offsets documented in comments).

void __thiscall SimNpc::updatePhysics(uint thisPtr, float dt)
{
    float *pfVar1;
    ulonglong uVar2;
    bool bVar3;
    char cVar4;
    byte uVar5;
    int iVar6;
    undefined4 uVar7;
    int *piVehicle;
    int iVar9;
    char *pcVar10;
    bool bVar11;
    float10 fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    double dVar16;
    double dVar17;
    float fVar18;
    float local_c4;
    float local_c0;
    char local_b9; // stored as byte in float mantissa hack
    undefined4 local_b8;
    char local_b1;
    float local_b0;
    undefined8 local_ac; // 3-component vector unpacked
    float local_a4;
    float local_a0;
    float local_9c;
    float local_98; // packed flags
    char local_92;
    char local_91;
    float local_90;
    float local_8c;
    float local_88;
    float local_84;
    undefined8 local_80;
    float local_78;
    undefined4 uStack_74;
    int *local_64;
    float local_60;
    undefined4 local_5c; // packed flags
    float local_58;
    float local_54;
    undefined8 local_50;
    float local_48;
    undefined4 local_44;
    float local_34; // forward vector?
    float local_30; // right vector?
    float local_2c; // up vector?
    float local_28;
    float local_24;
    undefined4 local_20;
    float local_1c;
    float local_18;
    float local_14;

    // +0x2d0: some stored time/physics param
    // +0x2cc: current speed magnitude
    local_58 = (g_dtOneMinusFactor - *(float *)(thisPtr + 0x2d0)) * dt +
               *(float *)(thisPtr + 0x2cc) * *(float *)(thisPtr + 0x2d0);
    *(float *)(thisPtr + 0x2cc) = local_58;

    // +0xe8: pointer to underlying character/vehicle (maybe VehicleBrain or Havok vehicle)
    if (*(int *)(thisPtr + 0xe8) == 0) {
        return;
    }
    piVehicle = (int *)(*(int *)(thisPtr + 0xe8) + -0x48);
    if (piVehicle == (int *)0x0) {
        return;
    }
    local_64 = piVehicle;

    // Invalidate some internal state?
    FUN_006c85e0(local_58);

    // +0x6c: maybe alive/can-collide flag? -1 means disabled?
    if (*(int *)(thisPtr + 0x6c) == -1) {
        if (*(int *)(thisPtr + 0xe8) == 0) {
            iVar6 = 0;
        }
        else {
            iVar6 = *(int *)(thisPtr + 0xe8) + -0x48;
        }
        FUN_006ca8e0(iVar6);
    }

    // +0x1e0, +0x1e4: orientation parameters
    local_a0 = *(float *)(thisPtr + 0x1e0);
    local_b8 = *(undefined4 *)(thisPtr + 0x1e4);
    cVar4 = FUN_00410f30(); // check if game paused?
    if (cVar4 != 0) {
        local_b8 = 0;
        local_a0 = 0.0;
    }

    // Extract forward/right/up vectors from orientation
    FUN_006ca040(&local_34, &local_24, &local_9c, &local_90, local_a0, local_b8,
                 &local_91, &local_20);

    FUN_006c54e0(local_20, *(undefined4 *)(thisPtr + 0x2cc));

    cVar4 = FUN_00410eb0(); // some condition (e.g., on ground)
    if (cVar4 == 0) {
        local_9c = (float)((uint)local_9c & g_bitMask) * local_9c; // hack: mantissa flags
    }
    cVar4 = FUN_00410eb0();
    if (cVar4 == 0) {
        // Apply desired horizontal velocity relative to object's local axes
        FUN_006c8a60(&local_9c, &local_90,
                     *(undefined4 *)(thisPtr + 0xd4), *(undefined4 *)(thisPtr + 0xd8));
    }

    // +0xf0: flag to allow movement? 0 = no velocity
    if (*(char *)(thisPtr + 0xf0) == 0) {
        local_90 = 0.0;
        local_9c = 0.0;
        local_91 = 0;
        local_98 = (float)((uint)local_98 & 0xffffff00); // clear mantissa byte
    }
    else if ((local_9c == 0.0) && (local_90 == 0.0)) {
        local_98 = (float)((uint)local_98._1_3_ << 8); // shift mantissa
    }
    else {
        local_98 = (float)CONCAT31(local_98._1_3_, 1); // set flag byte
        *(uint *)(thisPtr + 0x2f8) = g_cooldownResetValue; // reset some timer
    }

    fVar12 = (float10)FUN_006c93c0(piVehicle); // get vehicle speed
    local_60 = (float)fVar12;
    if ((((float10)g_speedThreshold < fVar12) || (local_34 != 0.0)) || (local_24 != 0.0)) {
        cVar4 = 1;
    }
    else {
        cVar4 = 0;
    }
    local_5c = CONCAT31(local_5c._1_3_, cVar4); // pack flag into local_5c mantissa

    local_b9 = 0;
    local_92 = 0;

    // +700 (0x2bc): flag for "in car" or "driving"?
    if ((*(char *)(thisPtr + 700) != 0) && (g_drivingFlagGlobal == 0)) {
        if ((cVar4 == 0) || (cVar4 = FUN_00410eb0(), cVar4 == 0)) {
            if ((0.0 < g_storedInputX * g_storedInputX) ||
                (0.0 < g_storedInputY * g_storedInputY)) {
                local_9c = g_storedInputX;
                local_90 = g_storedInputY;
                local_b9 = g_storedInputFlag;
                local_92 = g_storedInputFlag;
            }
            g_storedInputX = 0.0;
            g_storedInputY = 0.0;
            g_storedInputFlag = 0;
            FUN_006daa50(); // reset some input state
        }
        else {
            local_b9 = g_storedInputFlag;
            fVar12 = (float10)FUN_006c0600(*(undefined4 *)(thisPtr + 0x2cc), local_9c);
            local_9c = (float)fVar12;
            fVar12 = (float10)FUN_006c0600(*(undefined4 *)(thisPtr + 0x2cc), local_90);
            local_90 = (float)fVar12;
        }
    }

    // Apply rotation
    FUN_006c99c0(thisPtr + 0xc0, thisPtr + 0x27c, local_9c,
                 *(undefined4 *)(thisPtr + 0x2cc), g_one);

    fVar14 = g_rotationMaxSpeed;
    local_54 = 0.0;
    local_58 = 0.0;

    if (*(char *)(thisPtr + 700) != 0) {
        if (local_60 <= g_rotationChangeSpeed) {
            fVar14 = *(float *)(thisPtr + 0x2f0) - g_rotationDeceleration * dt;
            if (fVar14 < 0.0) {
                fVar14 = 0.0;
            }
            *(float *)(thisPtr + 0x2f0) = fVar14;
        }
        else {
            fVar13 = *(float *)(thisPtr + 0x2f0) + dt;
            *(float *)(thisPtr + 0x2f0) = fVar13;
            if (fVar14 < fVar13) {
                *(float *)(thisPtr + 0x2f0) = fVar14;
            }
        }
        fVar12 = (float10)FUN_006c91c0(*(undefined4 *)(thisPtr + 0x2f0),
                                       g_minTurn, g_maxTurn, 0, g_one);
        local_54 = (float)fVar12;
        fVar12 = (float10)FUN_006c91c0(*(undefined4 *)(thisPtr + 0x2f0),
                                       g_turnA, g_turnB, 0, g_one);
        local_58 = (float)fVar12;
    }

    FUN_006ca4b0(piVehicle, local_5c, local_98, *(undefined4 *)(thisPtr + 0x2cc));

    iVar6 = FUN_00471610(); // get player position
    local_48 = *(float *)(iVar6 + 0x38) - *(float *)(thisPtr + 0x240);
    local_50 = (ulonglong)(uint)(*(float *)(iVar6 + 0x30) - *(float *)(thisPtr + 0x238));
    local_44 = 0;
    FUN_0056afa0(&local_50, &local_50); // maybe normalize?

    // Smooth follow camera?
    FUN_006c5740(&local_ac); // get desired position offset
    fVar14 = *(float *)(thisPtr + 0x60) * g_lerpFactor;
    // +0x288,0x28c,0x290: smooth position error
    *(float *)(thisPtr + 0x288) =
        ((float)local_ac - *(float *)(thisPtr + 0x288)) * fVar14 + *(float *)(thisPtr + 0x288);
    *(float *)(thisPtr + 0x28c) =
        (local_ac._4_4_ - *(float *)(thisPtr + 0x28c)) * fVar14 + *(float *)(thisPtr + 0x28c);
    fVar14 = (local_a4 - *(float *)(thisPtr + 0x290)) * fVar14 + *(float *)(thisPtr + 0x290);
    *(float *)(thisPtr + 0x290) = fVar14;

    fVar13 = *(float *)(thisPtr + 0x28c) * local_50._4_4_ +
             (float)local_50 * *(float *)(thisPtr + 0x288) + fVar14 * local_48;
    fVar14 = g_minClamp;
    if ((g_minClamp < fVar13) && (fVar14 = fVar13, g_oneClamp <= fVar13)) {
        fVar14 = g_oneClamp;
    }
    dVar16 = (double)fVar14;
    FUN_00b9b988(); // sin/cos?
    fVar15 = (float)dVar16 - g_offset;
    fVar14 = (float)local_ac * 0.0 + local_ac._4_4_ + local_a4 * 0.0;
    fVar13 = g_minClamp;
    if ((fVar14 <= g_minClamp) || (fVar13 = g_oneClamp, g_oneClamp <= fVar14)) {
        fVar14 = fVar13;
    }
    dVar16 = (double)fVar14;
    FUN_00b9b988();
    dVar16 = (double)(float)dVar16;
    FUN_00b99fcb();
    local_78 = *(float *)(thisPtr + 0x228);
    pfVar1 = (float *)(thisPtr + 0x220);
    fVar14 = (float)dVar16;
    local_80 = *(ulonglong *)pfVar1;
    iVar6 = FUN_00471610();
    local_a4 = *(float *)(iVar6 + 0x38);
    local_ac = *(undefined8 *)(iVar6 + 0x30);
    fVar12 = (float10)FUN_006c55d0(); // maybe get actor speed?
    local_b0 = *(float *)(thisPtr + 0x184);
    local_a0 = *(float *)(thisPtr + 0x188);
    if (0.0 < local_a0) {
        if (g_oneClamp <= local_a0) {
            local_a0 = g_oneClamp;
        }
    }
    else {
        local_a0 = 0.0;
    }
    local_c0 = 0.0;
    if (g_someThreshold < *(float *)(thisPtr + 0x60)) {
        local_c0 = ((float)(fVar12 + (float10)local_ac._4_4_) - *(float *)(thisPtr + 0x224)) /
                    *(float *)(thisPtr + 0x60) + fVar14 * g_angularFactor;
    }
    local_ac._4_4_ = (float)(fVar12 + (float10)local_ac._4_4_);
    fVar12 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x268), local_c0, local_b0);
    local_b0 = (float)fVar12;
    fVar13 = local_b0 - local_b0 * local_a0;
    *(float *)(thisPtr + 0x268) = fVar13;
    fVar13 = fVar13 * *(float *)(thisPtr + 0x60) + *(float *)(thisPtr + 0x224);
    *pfVar1 = (float)local_ac;
    *(float *)(thisPtr + 0x228) = local_a4;
    *(float *)(thisPtr + 0x224) = fVar13;
    fVar13 = fVar13 - local_ac._4_4_;
    if (g_angularEpsilon < (float)((uint)fVar13 & g_bitMask)) {
        if (0.0 <= fVar13) {
            local_ac._4_4_ = local_ac._4_4_ + g_angularEpsilon;
        }
        else {
            local_ac._4_4_ = local_ac._4_4_ - g_angularEpsilon;
        }
        *(float *)(thisPtr + 0x224) = local_ac._4_4_;
    }
    local_a4 = *(float *)(thisPtr + 0x228);
    local_ac = *(ulonglong *)pfVar1;

    // Collision detection/response with world geometry
    FUN_006c4910(thisPtr + 0x2f4, pfVar1, local_64, thisPtr + 0x238, &local_ac,
                 *(undefined4 *)(thisPtr + 0x1b8), *(undefined4 *)(thisPtr + 0x108));
    FUN_006c4dc0(thisPtr + 0x2f4, pfVar1, thisPtr + 0x238, &local_ac,
                 *(undefined4 *)(thisPtr + 0x1b8), *(undefined4 *)(thisPtr + 0x108));

    // +700 (driving flag?) or AI override
    if (((*(char *)(thisPtr + 700) == 0) || (*(int *)(thisPtr + 0x2c8) == 0)) ||
        (g_drivingFlagGlobal == 0)) {
        FUN_006c44c0(&local_30, &local_80); // default movement
    }
    else {
        FUN_006c1de0(&local_30, local_64, *(int *)(thisPtr + 0x2c8), local_9c, local_34,
                     *(undefined4 *)(thisPtr + 0x27c), *(undefined4 *)(thisPtr + 0x2cc), local_60);
    }

    // Check if within cooldown window (maybe for attack/ability)
    if ((g_cooldownMax <= *(uint *)(thisPtr + 0x204)) ||
        (local_b1 = 1, *(uint *)(thisPtr + 0x204) <= g_cooldownMax - *(int *)(thisPtr + 0x2f8))) {
        local_b1 = 0;
    }

    if (*(char *)(thisPtr + 0x270) == 0) { // not in cover?
        if (*(char *)(thisPtr + 0x278) != 0) { // in some special state
            *(undefined4 *)(thisPtr + 0x280) = 0;
            uVar7 = *(undefined4 *)(thisPtr + 0x15c);
            goto LAB_006c67ac;
        }
        (**(code **)(*local_64 + 0x4c))(&local_50); // get vehicle forward?
        if ((SQRT(local_48 * local_48 + (float)local_50 * (float)local_50) < g_approachDist) ||
            (local_b1 != 0)) {
            FUN_006c9880(thisPtr + 0xc0, thisPtr + 0x280, local_90,
                         *(undefined4 *)(thisPtr + 0x2cc), g_one);
            fVar12 = (float10)FUN_006c8900(*(undefined4 *)(thisPtr + 0x280),
                                           *(undefined4 *)(thisPtr + 0x2cc));
            *(float *)(thisPtr + 0x284) = (float)(fVar12 + (float10)*(float *)(thisPtr + 0x284));
        }
        else {
            fVar12 = (float10)FUN_006c1120(fVar15, local_90);
            fVar13 = g_angularLow;
            local_b0 = (float)fVar12;
            fVar18 = fVar15 * g_angularFactor2;
            *(float *)(thisPtr + 0x284) = fVar18;
            if ((fVar13 < fVar15) || (fVar15 < g_angularHigh)) {
                local_c0 = g_angularMin;
                fVar13 = g_angularMax;
                goto LAB_006c68f9;
            }
            else {
                fVar15 = *(float *)(thisPtr + 0x298);
                fVar13 = 0.0;
                if ((0.0 < fVar15) && (fVar13 = g_oneClamp, fVar15 < g_oneClamp)) {
                    fVar13 = fVar15;
                }
                local_a0 = *(float *)(thisPtr + 0x1b0) * g_scaleFactor;
                fVar13 = *(float *)(thisPtr + 0x1b4) * g_scaleFactor * fVar13;
                local_c0 = fVar13;
                if (fVar13 < local_a0) {
LAB_006c68f9:
                    local_a0 = fVar13;
                }
            }
            fVar13 = (float)((uint)local_a0 & g_bitMask);
            if ((float)((uint)local_a0 & g_bitMask) <= (float)((uint)local_c0 & g_bitMask)) {
                fVar13 = (float)((uint)local_c0 & g_bitMask);
            }
            if (g_globalFlag == 0) {
                *(float *)(thisPtr + 0x284) = fVar13 * local_90 + fVar18;
            }
            else {
                *(float *)(thisPtr + 0x284) = fVar18 - fVar13 * local_90;
            }
            if (*(char *)(thisPtr + 700) != 0) {
                fVar12 = (float10)FUN_006c91c0(local_60, g_turnClampLow, g_turnClampHigh,
                                               g_turnParamA, g_turnParamB);
                *(float *)(thisPtr + 0x284) =
                     (float)(fVar12 * (float10)local_54 + (float10)*(float *)(thisPtr + 0x284));
            }
            fVar13 = *(float *)(thisPtr + 0x284);
            fVar15 = local_a0;
            if ((local_a0 < fVar13) && (fVar15 = local_c0, fVar13 < local_c0)) {
                fVar15 = fVar13;
            }
            *(float *)(thisPtr + 0x284) = fVar15;
            FUN_006c8c10((float *)(thisPtr + 0x284), thisPtr + 600, thisPtr + 0x25c, local_b0,
                         *(undefined4 *)(thisPtr + 0x2cc));
        }
        fVar15 = *(float *)(thisPtr + 0x130) * g_scaleFactor;
        fVar13 = g_clampLimit - fVar15;
        if (*(float *)(thisPtr + 0x284) <= fVar13 && fVar13 != *(float *)(thisPtr + 0x284)) {
            *(float *)(thisPtr + 0x284) = fVar13;
            fVar13 = *(float *)(thisPtr + 0x280);
            if (0.0 <= fVar13) {
                fVar13 = 0.0;
            }
            *(float *)(thisPtr + 0x280) = fVar13;
        }
        if (fVar15 < *(float *)(thisPtr + 0x284)) {
            fVar13 = *(float *)(thisPtr + 0x280);
            *(float *)(thisPtr + 0x284) = fVar15;
            if (fVar13 <= 0.0) {
                fVar13 = 0.0;
            }
            *(float *)(thisPtr + 0x280) = fVar13;
        }
    }
    else {
        // In cover/state
        *(undefined4 *)(thisPtr + 0x280) = 0;
        uVar7 = *(undefined4 *)(thisPtr + 0x154);
LAB_006c67ac:
        fVar12 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x284), fVar15 * g_angularScale,
                                       uVar7);
        *(float *)(thisPtr + 0x284) = (float)fVar12;
    }

    // Compute final rotation contribution
    fVar12 = (float10)FUN_006c3c90(); // get some multiplier
    local_1c = local_2c * 0.0 - local_28;
    local_18 = local_28 * 0.0 - local_30 * 0.0;
    local_14 = local_30 - local_2c * 0.0;
    FUN_004a0370(&local_30, &local_30, &local_1c,
                 (float)(fVar12 * (float10)g_scaleFactor + (float10)*(float *)(thisPtr + 0x284)));

    fVar12 = (float10)FUN_006c3640(*(byte *)(thisPtr + 0x270)); // get cover state factor
    local_a0 = (float)fVar12;

    if ((((char)local_5c != 0) || (local_98._0_1_ != 0)) ||
        (*(float *)(thisPtr + 0x298) <= g_oneClamp && g_oneClamp != *(float *)(thisPtr + 0x298))) {
        // Apply jumping/landing forces
        local_c4 = g_oneClamp - fVar14 * g_jumpFactor1;
        fVar13 = g_oneClamp - fVar14 * g_jumpFactor2;
        fVar12 = (float10)FUN_006c3910((float)fVar12, local_60, local_54);
        fVar12 = ((float10)1 - (float10)fVar14 * (float10)g_jumpFactor3) * fVar12;
        local_b0 = (float)fVar12;
        if (*(float *)(thisPtr + 0x2b0) <= local_b0) {
            local_c4 = (g_oneClamp - *(float *)(thisPtr + 0x298)) +
                       *(float *)(thisPtr + 0x124) * fVar13;
            if (0.0 < local_c4) goto LAB_006c6c2d;
            local_c4 = 0.0;
        }
        else {
            local_c4 = *(float *)(thisPtr + 0x120) * local_c4;
            if (0.0 < local_c4) {
LAB_006c6c2d:
                if (g_oneClamp <= local_c4) {
                    local_c4 = g_oneClamp;
                }
            }
            else {
                local_c4 = 0.0;
            }
        }
        fVar12 = (float10)FUN_006c89b0(*(float *)(thisPtr + 0x2b0), (float)fVar12, local_c4);
        *(float *)(thisPtr + 0x2b0) = (float)fVar12;
        fVar12 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x2ec), 0,
                                       *(undefined4 *)(thisPtr + 500));
        *(float *)(thisPtr + 0x2ec) = (float)fVar12;
    }

    fVar12 = (float10)FUN_006c11c0(); // get interpolation factor
    local_b0 = (float)(((float10)*(float *)(thisPtr + 0x2ec) +
                        (float10)*(float *)(thisPtr + 0x2b0)) * fVar12);

    local_88 = (local_b0 * local_2c + *(float *)(thisPtr + 0x224)) - *(float *)(thisPtr + 0x224);
    local_ac = CONCAT44(local_ac._4_4_, *(float *)(thisPtr + 0x214) - (float)local_80);
    local_a4 = *(float *)(thisPtr + 0x21c) - local_78;
    local_8c = (local_b0 * local_30 + *pfVar1) - *pfVar1;
    local_84 = (local_b0 * local_28 + *(float *)(thisPtr + 0x228)) - *(float *)(thisPtr + 0x228);

    dVar16 = (double)(g_clampLimit - local_8c);
    FUN_00b9a9fa(); // clamp?
    local_b0 = (float)dVar16;
    dVar16 = (double)(g_clampLimit - (float)local_ac);
    FUN_00b9a9fa();
    fVar12 = (float10)FUN_004a1580(local_b0 - (float)dVar16);
    FUN_004a0370(&local_8c, &local_8c, &g_verticalUp,
                 (float)(fVar12 * (float10)*(float *)(thisPtr + 0x138)));

    local_ac._0_4_ = local_8c + *pfVar1;
    local_ac._4_4_ = *(float *)(thisPtr + 0x224) + local_88;
    local_a4 = *(float *)(thisPtr + 0x228) + local_84;

    fVar12 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x13c),
                                   *(undefined4 *)(thisPtr + 0x140), local_a0);
    local_b0 = (float)fVar12;
    if (local_b0 <= *(float *)(thisPtr + 0x2a8)) {
        uVar7 = *(undefined4 *)(thisPtr + 0x148);
    }
    else {
        uVar7 = *(undefined4 *)(thisPtr + 0x144);
    }
    fVar12 = (float10)FUN_006c89b0(*(float *)(thisPtr + 0x2a8), (float)fVar12, uVar7);
    fVar14 = g_oneClamp;
    *(float *)(thisPtr + 0x2a8) = (float)fVar12;
    if (*(float *)(thisPtr + 0x298) <= fVar14 && fVar14 != *(float *)(thisPtr + 0x298)) {
        *(undefined4 *)(thisPtr + 0x2a8) = *(undefined4 *)(thisPtr + 0x140);
    }

    local_80 = *(ulonglong *)(thisPtr + 0x214);
    local_78 = *(float *)(thisPtr + 0x21c);
    fVar14 = *(float *)(thisPtr + 0x2a8) * *(float *)(thisPtr + 0x60);
    *(float *)(thisPtr + 0x214) =
         ((float)local_ac - *(float *)(thisPtr + 0x214)) * fVar14 + *(float *)(thisPtr + 0x214);
    *(float *)(thisPtr + 0x218) =
         (local_ac._4_4_ - *(float *)(thisPtr + 0x218)) * fVar14 + *(float *)(thisPtr + 0x218);
    *(float *)(thisPtr + 0x21c) =
         (local_a4 - *(float *)(thisPtr + 0x21c)) * fVar14 + *(float *)(thisPtr + 0x21c);

    if (local_b1 != 0) {
        uVar7 = *(undefined4 *)(thisPtr + 0x218);
        *(float *)(thisPtr + 0x214) = *pfVar1 + *(float *)(thisPtr + 0x2fc);
        *(float *)(thisPtr + 0x218) = *(float *)(thisPtr + 0x224) + *(float *)(thisPtr + 0x300);
        *(float *)(thisPtr + 0x21c) = *(float *)(thisPtr + 0x228) + *(float *)(thisPtr + 0x304);
        *(undefined4 *)(thisPtr + 0x218) = uVar7;
    }

    uVar7 = FUN_00471610();
    FUN_0056c180(uVar7, thisPtr + 0x2a0, thisPtr + 0x29c, thisPtr + 0x2a4); // update player references

    local_88 = *(float *)(thisPtr + 0x218) - *(float *)(thisPtr + 0x224);
    local_8c = *(float *)(thisPtr + 0x214) - *pfVar1;
    local_84 = *(float *)(thisPtr + 0x21c) - *(float *)(thisPtr + 0x228);

    dVar16 = (double)(g_clampLimit - local_8c);
    FUN_00b9a9fa();
    fVar12 = (float10)FUN_004a1580(*(float *)(thisPtr + 0x2a0) - (float)dVar16);
    fVar14 = (float)fVar12;

    if (local_91 == 0) {
LAB_006c709e:
        if (((char)local_5c == 0) && (local_98._0_1_ == 0)) {
            if (*(float *)(thisPtr + 0x158) <= *(float *)(thisPtr + 0x274) &&
                *(float *)(thisPtr + 0x274) != *(float *)(thisPtr + 0x158)) {
                *(uint *)(thisPtr + 0x26c) = (uint)fVar14 & g_bitMask;
                *(byte *)(thisPtr + 0x278) = 1;
            }
        }
        else {
            *(undefined4 *)(thisPtr + 0x274) = 0;
            *(byte *)(thisPtr + 0x278) = 0;
            if (*(char *)(thisPtr + 0x270) == 0) {
                *(undefined4 *)(thisPtr + 0x26c) = 0;
            }
        }
    }
    else {
        if (*(uint *)(thisPtr + 0x204) < *(uint *)(thisPtr + 0x2f8)) {
            *(uint *)(thisPtr + 0x2f8) = *(uint *)(thisPtr + 0x2f8) - *(uint *)(thisPtr + 0x204);
        }
        if ((local_34 != 0.0) || (local_24 != 0.0)) goto LAB_006c709e;
        *(undefined4 *)(thisPtr + 0x274) = 0;
        *(byte *)(thisPtr + 0x278) = 0;
        *(uint *)(thisPtr + 0x26c) = (uint)fVar14 & g_bitMask;
        *(byte *)(thisPtr + 0x270) = 1;
    }

    if ((local_34 != 0.0) || (local_24 != 0.0)) {
        *(undefined4 *)(thisPtr + 0x26c) = 0;
        *(byte *)(thisPtr + 0x270) = 0;
        *(undefined4 *)(thisPtr + 0x274) = 0;
        *(byte *)(thisPtr + 0x278) = 0;
    }

    // State machine transitions for cover/falling
    if (((*(char *)(thisPtr + 0x270) != 0) || (*(char *)(thisPtr + 0x278) != 0)) ||
        (0.0 < *(float *)(thisPtr + 0x26c))) {
        if (((*(float *)(thisPtr + 0x26c) <= g_epsilon && g_epsilon != *(float *)(thisPtr + 0x26c)
             ) && ((float)((uint)fVar14 & g_bitMask) < g_epsilon)) &&
           ((float)(*(uint *)(thisPtr + 0x284) & g_bitMask) < g_epsilon)) {
            *(undefined4 *)(thisPtr + 0x26c) = 0;
            *(byte *)(thisPtr + 0x270) = 0;
            *(undefined4 *)(thisPtr + 0x274) = 0;
            *(byte *)(thisPtr + 0x278) = 0;
        }
        if (*(char *)(thisPtr + 0x270) == 0) {
            uVar7 = *(undefined4 *)(thisPtr + 0x15c);
        }
        else {
            uVar7 = *(undefined4 *)(thisPtr + 0x154);
        }
        fVar12 = (float10)FUN_006c8900(uVar7, *(undefined4 *)(thisPtr + 0x2cc));
        local_c4 = (float)(fVar12 * (float10)fVar14);
        fVar14 = *(float *)(thisPtr + 0x26c) - (float)((uint)local_c4 & g_bitMask);
        if (fVar14 < 0.0) {
            fVar14 = 0.0;
        }
        *(float *)(thisPtr + 0x26c) = fVar14;
    }
    else if (g_globalFlag2 == 0) {
        fVar12 = (float10)FUN_006c8900(*(undefined4 *)(thisPtr + 0x27c),
                                       *(undefined4 *)(thisPtr + 0x2cc));
        local_c4 = (float)fVar12;
    }
    else {
        local_c4 = 0.0;
    }

    if ((local_b9 == 0) && (g_drivingFlagGlobal == 0)) {
        FUN_004a0370(&local_8c, &local_8c, &g_verticalUp, local_c4);
    }

    fVar13 = *(float *)(thisPtr + 0x224) + local_88;
    local_a4 = *(float *)(thisPtr + 0x228) + local_84;
    local_ac = CONCAT44(fVar13, *pfVar1 + local_8c);
    fVar14 = local_a4;
    uVar2 = local_ac;

    if (((char)local_5c == 0) && (local_98._0_1_ == 0)) {
        fVar15 = (float)local_80 - (*pfVar1 + local_8c);
        fVar13 = local_80._4_4_ - fVar13;
        if ((local_78 - local_a4) * (local_78 - local_a4) + fVar13 * fVar13 + fVar15 * fVar15 <
            g_snapDist) {
            fVar14 = local_78;
            uVar2 = local_80;
        }
    }
    *(ulonglong *)(thisPtr + 0x214) = uVar2;
    *(float *)(thisPtr + 0x21c) = fVar14;

    fVar12 = (float10)FUN_004a1580(*(float *)(thisPtr + 0x20c) + local_c4);
    *(float *)(thisPtr + 0x20c) = (float)fVar12;

    local_84 = *(float *)(thisPtr + 0x21c) - *(float *)(thisPtr + 0x228);
    local_8c = *(float *)(thisPtr + 0x214) - *pfVar1;
    fVar14 = *(float *)(thisPtr + 0x218) - *(float *)(thisPtr + 0x224);
    local_98 = SQRT(local_8c * local_8c + local_84 * local_84);
    dVar16 = (double)(g_clampLimit - local_8c);
    local_88 = fVar14;
    FUN_00b9a9fa();
    local_b0 = (*(float *)(thisPtr + 0x150) - *(float *)(thisPtr + 0x14c)) * local_a0 +
               *(float *)(thisPtr + 0x14c);
    fVar12 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x2ac), local_b0, g_lerpLimit);
    dVar17 = (double)fVar14;
    *(float *)(thisPtr + 0x2ac) = (float)fVar12;
    FUN_00b9a9fa();
    *(float *)(thisPtr + 0x208) = (float)dVar17;

    cVar4 = FUN_00410eb0();
    if (cVar4 == 0) {
        fVar12 = (float10)FUN_006c89d0(*(undefined4 *)(thisPtr + 0x20c), (float)dVar16,
                                       *(undefined4 *)(thisPtr + 0x2ac));
        *(float *)(thisPtr + 0x20c) = (float)fVar12;
    }
    else {
        *(float *)(thisPtr + 0x20c) = (float)dVar16;
    }
    *(undefined4 *)(thisPtr + 0x210) = 0;

    // AI staggering/hit reaction handling
    if ((((*(char *)(thisPtr + 700) == 0) || (iVar6 = *(int *)(thisPtr + 0x2c8), iVar6 == 0)) ||
        (piVehicle = (int *)FUN_007ff880(), piVehicle == (int *)0x0)) || (piVehicle[0x2a7] == 0))
        goto LAB_006c7948;

    uVar5 = FUN_0085e050(0xe); // read random or flag
    local_98 = (float)CONCAT31(local_98._1_3_, uVar5);

    (**(code **)(*piVehicle + 0x4c))(&local_50);
    iVar9 = FUN_00471610();
    uVar2 = *(ulonglong *)(iVar9 + 0x20);
    local_78 = *(float *)(iVar9 + 0x28);
    local_80._0_4_ = (float)uVar2;
    local_80._4_4_ = (float)(uVar2 >> 0x20);
    fVar14 = local_50._4_4_ * local_80._4_4_ + (float)local_50 * (float)local_80 + local_48 * local_78;
    local_80 = uVar2;

    pcVar10 = (char *)FUN_00549a40(&local_b1);
    if (*pcVar10 == 0) {
        if (*(char *)(thisPtr + 0x308) == 0) goto LAB_006c761d;
        bVar11 = false;
        if ((g_clampLimit - g_hitThreshold < fVar14) && (local_98._0_1_ != 0)) {
            bVar11 = true;
        }
        if (((0.0 < fVar14) &&
            (fVar14 = fVar14 * dt + *(float *)(thisPtr + 0x30c),
             bVar3 = g_hitRecover <= fVar14,
             *(float *)(thisPtr + 0x30c) = fVar14,
             bVar3)) || (bVar11)) {
            *(byte *)(thisPtr + 0x308) = 0; // recover from hit
            *(undefined4 *)(thisPtr + 0x30c) = 0;
        }
    }
    else if (*(char *)(thisPtr + 0x308) == 0) { // not in hit reaction
        if (fVar14 < 0.0) {
            fVar14 = *(float *)(thisPtr + 0x30c) - fVar14 * dt;
            bVar11 = g_hitStunThreshold <= fVar14;
            *(float *)(thisPtr + 0x30c) = fVar14;
            if ((bVar11) || (local_98._0_1_ != 0)) {
                *(byte *)(thisPtr + 0x308) = 1;
                *(undefined4 *)(thisPtr + 0x30c) = 0;
            }
        }
    }
    else {
LAB_006c761d:
        *(undefined4 *)(thisPtr + 0x30c) = 0;
    }

    cVar4 = FUN_0085e050(0xe);
    if ((cVar4 == 0) && (*(char *)(thisPtr + 0x308) == 0)) {
        cVar4 = FUN_00690210(0x16); // some AI check
        if (cVar4 != 0) {
            cVar4 = FUN_006c1b80(local_98, 0, local_9c, local_64, iVar6);
            if (cVar4 != 0) {
                fVar12 = (float10)FUN_004a1580(*(undefined4 *)(thisPtr + 0x2a0));
                *(float *)(thisPtr + 0x20c) = (float)fVar12;
                if (g_drivingFlagGlobal != 0) {
                    local_80 = CONCAT44(g_globalVectorHigh, g_globalVectorLow);
                    local_78 = g_globalVectorZ;
                    uStack_74 = g_globalVectorW;
                    fVar12 = (float10)FUN_004a1580(g_globalVectorLow + g_additiveOffset);
                    *(float *)(thisPtr + 0x20c) = (float)fVar12;
                }
                fVar14 = g_clampLimit - SQRT(local_8c * local_8c + local_84 * local_84);
                local_b0 = fVar14;
                iVar6 = FUN_00471610();
                bVar11 = g_drivingFlagGlobal != 0;
                *(float *)(thisPtr + 0x214) = local_b0 * *(float *)(iVar6 + 0x20) + *pfVar1;
                *(float *)(thisPtr + 0x218) =
                     *(float *)(iVar6 + 0x24) * local_b0 + *(float *)(thisPtr + 0x224);
                *(float *)(thisPtr + 0x21c) =
                     *(float *)(iVar6 + 0x28) * local_b0 + *(float *)(thisPtr + 0x228);
                if (bVar11) {
                    local_ac = 0;
                    local_a4 = g_minClamp;
                    local_80 = CONCAT44(g_globalVectorHigh, g_globalVectorLow);
                    local_78 = g_globalVectorZ;
                    uStack_74 = g_globalVectorW;
                    fVar12 = (float10)FUN_004a1580(g_globalVectorLow);
                    FUN_004a0370(&local_ac, &local_ac, &g_verticalUp, (float)fVar12);
                    *(float *)(thisPtr + 0x214) = (float)local_ac * fVar14 + *pfVar1;
                    *(float *)(thisPtr + 0x218) = local_ac._4_4_ * fVar14 + *(float *)(thisPtr + 0x224);
                    *(float *)(thisPtr + 0x21c) = local_a4 * fVar14 + *(float *)(thisPtr + 0x228);
                }
                *(float *)(thisPtr + 0x218) = *(float *)(thisPtr + 0x218) + local_88;
            }
            *(byte *)(thisPtr + 0x270) = 0;
            FUN_006901e0(0x16); // reset AI
        }
    }
    else {
        cVar4 = FUN_006c1b80(local_98, *(byte *)(thisPtr + 0x308), local_9c, local_64, iVar6);
        if (cVar4 != 0) {
            fVar12 = (float10)FUN_004a1580(*(float *)(thisPtr + 0x2a0) + g_additiveOffset);
            *(float *)(thisPtr + 0x20c) = (float)fVar12;
            local_b0 = SQRT(local_8c * local_8c + local_84 * local_84);
            iVar9 = FUN_00471610();
            local_a4 = *(float *)(iVar9 + 0x28);
            local_ac = *(ulonglong *)(iVar9 + 0x20) & 0xffffffff;
            FUN_0043a210(&local_ac, &local_ac);
            *(float *)(thisPtr + 0x214) = (float)local_ac * local_b0 + *pfVar1;
            fVar14 = local_ac._4_4_ * local_b0 + *(float *)(thisPtr + 0x224);
            *(float *)(thisPtr + 0x218) = fVar14;
            *(float *)(thisPtr + 0x21c) = local_b0 * local_a4 + *(float *)(thisPtr + 0x228);
            *(float *)(thisPtr + 0x218) = fVar14 + local_88;
        }
        *(uint *)(iVar6 + 0x249c) = *(uint *)(iVar6 + 0x249c) | 0x400000;
    }

LAB_006c7948:
    fVar14 = local_78;
    if ((local_b9 != 0) && (g_drivingFlagGlobal == 0)) {
        local_80 = *(ulonglong *)(thisPtr + 0x214);
        local_48 = *(float *)(thisPtr + 0x210);
        local_50 = *(ulonglong *)(thisPtr + 0x208);
        fVar14 = *(float *)(thisPtr + 0x21c);
        local_8c = *(float *)(thisPtr + 0x214) - *pfVar1;
        local_88 = *(float *)(thisPtr + 0x218) - *(float *)(thisPtr + 0x224);
        local_84 = *(float *)(thisPtr + 0x21c) - *(float *)(thisPtr + 0x228);
        fVar13 = g_clampLimit - g_pushbackFactor * local_9c;
        FUN_004a0370(&local_8c, &local_8c, &g_verticalUp, fVar13);
        *(float *)(thisPtr + 0x214) = *pfVar1 + local_8c;
        *(float *)(thisPtr + 0x218) = *(float *)(thisPtr + 0x224) + local_88;
        *(float *)(thisPtr + 0x21c) = *(float *)(thisPtr + 0x228) + local_84;
        fVar12 = (float10)FUN_004a1580(*(float *)(thisPtr + 0x20c) + fVar13);
        *(float *)(thisPtr + 0x20c) = (float)fVar12;
    }

    FUN_006c4f60(*(undefined4 *)(thisPtr + 0x2cc));
    FUN_006c4f00();

    if (g_someDistance < *(float *)(thisPtr + 0x2b8)) {
        FUN_006ca5e0(pfVar1, thisPtr + 0x238, thisPtr + 0x238);
    }

    if (((local_b9 != 0) && (local_92 == 0)) && (g_drivingFlagGlobal == 0)) {
        *(ulonglong *)(thisPtr + 0x214) = local_80;
        *(ulonglong *)(thisPtr + 0x208) = local_50;
        *(float *)(thisPtr + 0x21c) = fVar14;
        *(float *)(thisPtr + 0x210) = local_48;
    }

    // Update transform output (position, rotation, etc.)
    fVar14 = g_oneClamp;
    *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(thisPtr + 0x238);
    *(undefined4 *)(thisPtr + 0x24) = *(undefined4 *)(thisPtr + 0x23c);
    *(float *)(thisPtr + 0x2c) = fVar14;
    *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(thisPtr + 0x240);
    *(undefined4 *)(thisPtr + 0x40) = *(undefined4 *)(thisPtr + 0x22c);
    *(undefined4 *)(thisPtr + 0x44) = *(undefined4 *)(thisPtr + 0x230);
    *(float *)(thisPtr + 0x4c) = fVar14;
    *(undefined4 *)(thisPtr + 0x48) = *(undefined4 *)(thisPtr + 0x234);
    *(float *)(thisPtr + 0x50) = *(float *)(thisPtr + 0x244) * g_scaleFactor;

    // Speed-based clamp for certain mode
    if ((*(char *)(thisPtr + 700) == 0) ||
        (FUN_006c0f60(local_60, local_54, local_58), *(char *)(thisPtr + 700) == 0)) {
        fVar14 = *(float *)(thisPtr + 0x50);
        fVar13 = 0.0;
        if ((fVar14 <= 0.0) || (fVar13 = g_speedClampMax, g_speedClampMax <= fVar14)) {
            fVar14 = fVar13;
        }
        *(float *)(thisPtr + 0x50) = fVar14;
    }

    // Position interpolation for rendering
    local_78 = *(float *)(thisPtr + 0x240) - *(float *)(thisPtr + 0x228);
    local_80._4_4_ = *(float *)(thisPtr + 0x23c) - *(float *)(thisPtr + 0x224);
    local_80._0_4_ = *(float *)(thisPtr + 0x238) - *pfVar1;

    fVar13 = SQRT(local_78 * local_78 + local_80._4_4_ * local_80._4_4_ +
                  (float)local_80 * (float)local_80);
    fVar12 = (float10)FUN_00473b70(); // get time step
    fVar14 = g_oneClamp;
    if ((float10)fVar13 - fVar12 <= (float10)g_lerpDist) {
        *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(thisPtr + 0x238);
        *(undefined4 *)(thisPtr + 0x24) = *(undefined4 *)(thisPtr + 0x23c);
        *(float *)(thisPtr + 0x2c) = fVar14;
        *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(thisPtr + 0x240);
        *(float *)(thisPtr + 0x2b4) = fVar13;
        FUN_00473b10(fVar13);
    }
    else {
        fVar14 = fVar13 * *(float *)(thisPtr + 0x2cc) * g_lerpFactor + *(float *)(thisPtr + 0x2b4);
        *(float *)(thisPtr + 0x2b4) = fVar14;
        if (fVar13 < fVar14) {
            *(float *)(thisPtr + 0x2b4) = fVar13;
        }
        fVar14 = g_oneClamp;
        fVar13 = *(float *)(thisPtr + 0x2b4) / fVar13;
        *(float *)(thisPtr + 0x20) = (float)local_80 * fVar13 + *pfVar1;
        *(float *)(thisPtr + 0x24) = local_80._4_4_ * fVar13 + *(float *)(thisPtr + 0x224);
        *(float *)(thisPtr + 0x28) = local_78 * fVar13 + *(float *)(thisPtr + 0x228);
        *(float *)(thisPtr + 0x2c) = fVar14;
        *(float *)(thisPtr + 0x30) = *pfVar1;
        *(undefined4 *)(thisPtr + 0x34) = *(undefined4 *)(thisPtr + 0x224);
        *(float *)(thisPtr + 0x3c) = fVar14;
        *(undefined4 *)(thisPtr + 0x38) = *(undefined4 *)(thisPtr + 0x228);
    }

    // Store offsets for later use
    *(float *)(thisPtr + 0x2fc) = *(float *)(thisPtr + 0x214) - *pfVar1;
    *(float *)(thisPtr + 0x300) = *(float *)(thisPtr + 0x218) - *(float *)(thisPtr + 0x224);
    *(float *)(thisPtr + 0x304) = *(float *)(thisPtr + 0x21c) - *(float *)(thisPtr + 0x228);

    g_globalOutput = *(undefined4 *)(thisPtr + 0x2d8);
    return;
}
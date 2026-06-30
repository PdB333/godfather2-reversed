// FUNC_NAME: EntityPhysics::simulateStep

// Class representing a physics-controlled entity (vehicle or character)
// Offset field definitions:
// +0x00: vtable
// +0x08: position x
// +0x0C: position y
// +0x10: position z
// +0x14: velocity? (set from +0x1D8?)
// +0x88 (0x22*4): stored value
// +0x90 (0x24*4): throttle/input value
// +0x91 (0x24*4+4): previous throttle
// +0x92 (0x24*4+8): char flag (is reversing?)
// +0x93 (0x24*4+12): steering angle?
// +0x94 etc.
// Full offsets reconstructed from decompiled indices

void __thiscall EntityPhysics::simulateStep(int* thisPtr, float deltaTime) {
    float* pfVar1;
    float* pfVar2;
    uint uVar3;
    char cVar4;
    int iVar5;
    bool bVar6;
    float10 fVar7;
    float10 fVar8;
    float fVar9;
    float fVar10;
    double dVar11;
    float fVar12;
    int iStack_120; // uninitialized local? Actually seems to be a pointer used later via iStack_120 + 0x8e0
    float* pSomeFloat;
    float local_118; // frequently reused temp
    undefined8 uStack_114; // 8 bytes vector
    float fStack_10c;
    undefined4 uStack_108; // uninitialized local (maybe audio?)
    float local_104; // orientation angle (yaw?)
    float local_100; // orientation angle (pitch?)
    float fStack_fc;
    float fStack_f8;
    float fStack_f4;
    float fStack_f0;
    float fStack_ec;
    float fStack_e8;
    float fStack_e0;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float fStack_d0;
    float fStack_cc;
    float fStack_c8;
    float fStack_c0;
    float fStack_bc;
    float fStack_b8;
    float local_b0; // velocity vector? (set later)
    float local_ac;
    float local_a8;
    float local_a4;
    int iStack_8c; // uninitialized
    int local_88; // uninitialized
    int iStack_84; // uninitialized
    int local_80; // uninitialized
    float fStack_7c;
    float local_78; // pitch acceleration?
    float local_74; // roll acceleration?
    float fStack_70;
    float local_6c; // yaw acceleration?
    float local_64;
    float local_5c;
    undefined4 uStack_58; // uninitialized (used in condition)
    float fStack_40;
    float fStack_3c;
    float local_34;
    float fStack_30;
    float local_2c;
    undefined4 uStack_24;
    undefined4 uStack_20;
    float fStack_1c;
    float fStack_18;

    // Check if menu is active or debug pause
    cVar4 = FUN_00424980(); // probably isMenuActive() or isPaused()
    if ((cVar4 == '\0') || (DAT_0112a863 = 1, 1 < DAT_0112a8e4)) {
        DAT_0112a863 = 0; // reset some flag
    }

    FUN_006c85e0(DAT_00d5f374); // update some timer with delta time? (DAT_00d5f374 is probably frameTime)
    FUN_006d74c0(thisPtr + 0x30); // likely update acceleration from input (offset 0xC0)

    // Handle some pointer arithmetic (maybe linked list)
    if (local_88 == 0) {
        local_88 = 0;
    }
    else {
        local_88 = local_88 + -0x48;
    }
    thisPtr[0x76] = local_88; // offset 0x1D8

    if (local_88 == 0) {
        if (local_80 == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = local_80 + -0x48;
        }
        thisPtr[0x76] = iVar5;
    }

    fVar9 = _DAT_00d5780c; // usually 1.0f
    fVar8 = (float10)1.0f;
    thisPtr[0x22] = thisPtr[0x76]; // offset 0x88

    // Throttle control logic
    if ((char)thisPtr[0x92] == '\0') { // +0x248 flag
        if (0.0f < (float)thisPtr[0x90]) { // +0x240 throttle
            local_118 = (float)(DAT_01205224 - thisPtr[0x8f]); // timer delta?
            fVar7 = (float10)(int)local_118;
            if ((int)local_118 < 0) {
                fVar7 = fVar7 + (float10)DAT_00e44578;
            }
            fVar7 = fVar8 - fVar7 * (float10)_DAT_00d5f564;
            goto LAB_006d8a5c;
        }
    }
    else if ((float)thisPtr[0x90] <= fVar9 && fVar9 != (float)thisPtr[0x90]) {
        local_118 = (float)(DAT_01205224 - thisPtr[0x8f]);
        fVar7 = (float10)(int)local_118;
        if ((int)local_118 < 0) {
            fVar7 = fVar7 + (float10)DAT_00e44578;
        }
        fVar7 = fVar7 * (float10)_DAT_00d5f564;
LAB_006d8a5c:
        thisPtr[0x90] = (int)(float)fVar7;
    }

    fVar10 = (float)thisPtr[0x90];
    if (0.0f < fVar10) {
        if (fVar9 <= fVar10) {
            fVar10 = fVar9;
        }
    }
    else {
        fVar10 = 0.0f;
    }
    thisPtr[0x90] = (int)fVar10; // clamp throttle

    // Compute sine-based scaling for acceleration
    fVar7 = (float10)fsin(((float10)fVar10 + (float10)fVar10) - fVar8);
    fVar8 = (fVar7 + fVar8) * (float10)_DAT_00d5c458; // _DAT_00d5c458 is maxAccel
    pSomeFloat = (float*)(float)fVar8;

    // Compute angular accelerations from input (likely pitch/yaw/roll)
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x41], thisPtr[100], (float)fVar8); // lerp
    local_6c = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x3e], thisPtr[0x61], pSomeFloat);
    local_78 = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x3f], thisPtr[0x62], pSomeFloat);
    local_74 = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x34], thisPtr[0x57], pSomeFloat);
    local_a0 = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x30], thisPtr[0x53], pSomeFloat);
    local_b0 = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x31], thisPtr[0x54], pSomeFloat);
    local_ac = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x32], thisPtr[0x55], pSomeFloat);
    local_a8 = (float)fVar8;
    fVar8 = (float10)FUN_006c89b0(thisPtr[0x33], thisPtr[0x56], pSomeFloat);
    local_a4 = (float)fVar8;

    cVar4 = FUN_00410eb0(); // maybe isFirstPerson?
    iVar5 = DAT_01129944; // global camera transform?
    if (cVar4 == '\0') {
        fVar9 = deltaTime * _DAT_00d5f560; // speed scaling?
        if (_DAT_00d5780c < deltaTime * _DAT_00d5f560) {
            fVar9 = _DAT_00d5780c;
        }
        local_b0 = local_b0 * fVar9;
        local_ac = local_ac * fVar9;
        local_a8 = local_a8 * fVar9;
        local_a4 = local_a4 * fVar9;
    }

    // Interpolate orientation based on throttle change
    if ((float)thisPtr[0x90] != (float)thisPtr[0x91]) {
        fVar9 = _DAT_00d5780c - (float)pSomeFloat;
        local_34 = (float)thisPtr[0x72] * (float)pSomeFloat + (float)thisPtr[0x4f] * fVar9;
        fStack_30 = (float)thisPtr[0x73] * (float)pSomeFloat + (float)thisPtr[0x50] * fVar9;
        local_2c = (float)thisPtr[0x74] * (float)pSomeFloat + (float)thisPtr[0x51] * fVar9;
        *(ulonglong*)(iVar5 + 0x108) = CONCAT44(fStack_30, local_34);
        *(float*)(iVar5 + 0x110) = local_2c;
    }

    fVar9 = _DAT_00d5c458; // maxAccel used for threshold
    thisPtr[0x91] = thisPtr[0x90]; // store previous throttle

    // Get pointer to some entity (maybe this entity's parent or config)
    iVar5 = **(int**)(DAT_012233a0 + 4);
    if (iVar5 == 0) {
        pSomeFloat = (float*)0x0;
    }
    else {
        pSomeFloat = (float*)(iVar5 + -0x1f30);
        if (((pSomeFloat != (float*)0x0) && ((*(byte*)(iVar5 + 0x56f) & 1) != 0)) && (local_6c < fVar9)) {
            local_6c = fVar9; // enforce minimum yaw
        }
    }

    pfVar1 = (float*)(thisPtr + 0x7d); // offset 0x1F4 (position?)
    FUN_006d65a0(pfVar1, thisPtr[0x76], &local_b0); // apply forces/acceleration

    if (local_80 == 0) {
        local_80 = 0;
    }
    else {
        local_80 = local_80 + -0x48;
    }
    FUN_006ca8e0(local_80); // update linked list or similar

    cVar4 = FUN_006c9fe0(); // check if something is active?
    if (cVar4 == '\0') {
        if (thisPtr[0x3c] == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = thisPtr[0x3c] + -0x48;
        }
        if ((*(uint*)(iVar5 + 0x24a4) >> 10 & 1) != 0) goto LAB_006d8de5;
    }
    else {
LAB_006d8de5:
        if (thisPtr[0x3c] == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = thisPtr[0x3c] + -0x48;
        }
        *(uint*)(iVar5 + 0x24a4) = *(uint*)(iVar5 + 0x24a4) & 0xfffffbff; // clear bit
        FUN_006d72a0(0); // reset some state
    }

    // Extract orientation angles from current rotation
    FUN_006ca770(&local_104, &local_100, &local_b0); // pitch, yaw from vector?
    fVar8 = (float10)FUN_006d7380(local_104); // normalize?
    local_104 = (float)fVar8;

    if (0.0f < DAT_0112a8e0) {
        DAT_0112a8e0 = DAT_0112a8e0 - DAT_00d5f374; // decrement cooldown timer
        local_100 = 0.0f;
        if (DAT_0112a8e0 < 0.0f) {
            DAT_0112a8e0 = 0.0f;
        }
    }

    iVar5 = thisPtr[0x89]; // something flag
    // Handle turning/steering interpolation with acceleration
    if ((iVar5 != 0) || (thisPtr[0x8a] != 0)) {
        if (thisPtr[0x8a] != 0) {
            fVar9 = (float)(thisPtr[0x8b] & DAT_00e44680);
            // Calculate signed difference
            if ((float)thisPtr[0x8b] * local_64 <= 0.0f) {
                fVar9 = (float)((uint)local_64 & DAT_00e44680) + fVar9;
            }
            else {
                fVar9 = (float)((uint)local_64 & DAT_00e44680) - fVar9;
            }
            fVar9 = (float)((uint)fVar9 & DAT_00e44680) / (float)(DAT_00e511e4 & DAT_00e44680);
            if (0.0f < fVar9) {
                if (_DAT_00d5780c <= fVar9) {
                    fVar9 = _DAT_00d5780c;
                }
            }
            else {
                fVar9 = 0.0f;
            }
            fVar9 = DAT_00e511e0 * fVar9; // speed factor
            if (local_64 < (float)thisPtr[0x8b]) {
                fVar9 = fVar9 * DAT_00d5ccf8; // deceleration factor?
            }
            fVar10 = (float)thisPtr[0x8b];
            thisPtr[0x8b] = (int)(fVar10 + fVar9);
            fVar8 = (float10)FUN_006d6350((fVar10 + fVar9) - local_64); // check distance
            if (ABS(fVar8) < (float10)_DAT_00e511dc) {
                thisPtr[0x8a] = 0; // done turning?
            }
        }
        uVar3 = DAT_00e44680;
        if (iVar5 != 0) {
            // Steering wheel animation?
            local_118 = (float)thisPtr[0x8d];
            if (local_118 < 0.0f) {
                local_118 = local_118 + DAT_00d5f4b4;
            }
            local_118 = local_118 * DAT_00e445c8;
            fVar9 = (float)thisPtr[0x93] - local_118;
            fVar10 = (float)((uint)fVar9 & DAT_00e44680);
            if (DAT_00d5eeec < fVar10) {
                if (fVar9 <= 0.0f) {
                    fVar9 = fVar9 + DAT_00d5d70c;
                }
                else {
                    fVar9 = fVar9 - DAT_00d5d70c;
                }
                thisPtr[0x93] = (int)(fVar9 + local_118);
                fVar10 = (float)((uint)fVar9 & uVar3);
            }
            fVar12 = DAT_00d5f55c;
            if ((DAT_00d5f55c <= fVar10) && (fVar12 = DAT_00d5f558, fVar10 <= DAT_00d5f558)) {
                fVar12 = fVar10;
            }
            fVar12 = (fVar12 - DAT_00d5f55c) * _DAT_00d5f554 * _DAT_00d5f550 + _DAT_00d5f54c;
            if (fVar12 <= fVar10) {
                if (0.0f <= fVar9) {
                    local_118 = fVar12 + local_118;
                }
                else {
                    local_118 = local_118 - fVar12;
                }
            }
            else {
                local_118 = (float)thisPtr[0x93];
                thisPtr[0x89] = 0; // stop steering
            }
            fVar8 = (float10)FUN_004a1580(local_118);
            thisPtr[0x8d] = (int)(float)(fVar8 * (float10)DAT_00e44748);
        }
    }

    pfVar2 = (float*)(thisPtr + 0x2b); // offset 0xAC (forward vector?)
    // Interpolate velocity/acceleration
    FUN_006c9880(&local_b0, pfVar2, local_100, deltaTime, 0x3f800000); // slerp orientation?
    FUN_006c99c0(&local_b0, thisPtr + 0x2a, local_104, deltaTime, 0x3f800000);

    // If angular velocity too high, reset turning
    if ((_DAT_00d5c458 < (float)((uint)local_100 & DAT_00e44680)) ||
        (_DAT_00d5c458 < (float)((uint)local_104 & DAT_00e44680))) {
        thisPtr[0x8a] = 0;
        thisPtr[0x89] = 0;
    }

    // Integrate speed and steering
    fVar8 = (float10)FUN_006c8900(*pfVar2, DAT_00d5f374); // multiply by dt
    fVar8 = (float10)FUN_006d6350((float)((float10)(float)thisPtr[0x8b] - fVar8 * (float10)DAT_00e44748));
    thisPtr[0x8b] = (int)(float)fVar8;

    fVar8 = (float10)FUN_006c8900(thisPtr[0x2a], DAT_00d5f374);
    fVar8 = (float10)FUN_006d6350((float)(fVar8 * (float10)DAT_00e44748 + (float10)(float)thisPtr[0x8d]));
    thisPtr[0x8d] = (int)(float)fVar8;

    FUN_006ca4b0(pSomeFloat, 1, 1, DAT_00d5f374); // some update with entity pointer

    local_118 = local_5c; // uninitialized
    // Call virtual function on entity (likely getPosition)
    (**(code**)((int)*pSomeFloat + 0x4c))((int)&uStack_114 + 4); // returns a 3D vector at uStack_114

    if (DAT_00d5f548 <=
        uStack_114._4_4_ * uStack_114._4_4_ + fStack_10c * fStack_10c +
        (float)uStack_114 * (float)uStack_114) {
        fVar8 = (float10)FUN_006c89b0(thisPtr[0x8c], uStack_58, _DAT_00d5cf70);
        thisPtr[0x8c] = (int)(float)fVar8;
    }
    else {
        thisPtr[0x8c] = (int)local_5c;
    }

    // Clamp speed and reset forward if beyond limits
    if ((float)thisPtr[0x8b] <= (float)pSomeFloat) {
        if (DAT_00e44564 - (float)thisPtr[0x8c] <= (float)thisPtr[0x8b]) goto LAB_006d9269;
        thisPtr[0x8b] = (int)(DAT_00e44564 - (float)thisPtr[0x8c]);
        fVar9 = *pfVar2;
        bVar6 = fVar9 < 0.0f;
    }
    else {
        thisPtr[0x8b] = (int)pSomeFloat;
        fVar9 = *pfVar2;
        bVar6 = 0.0f < fVar9;
    }
    if (bVar6 || fVar9 == 0.0f) {
        fVar9 = 0.0f;
    }
    *pfVar2 = fVar9;
LAB_006d9269:

    // Check if debug/audio flag is set
    if (((*(uint*)(iStack_120 + 0x8e0) >> 9 & 1) != 0) && (cVar4 = FUN_00481660(), cVar4 == '\0')) {
        FUN_006d7fd0(uStack_108, local_104); // play audio?
    }

    iVar5 = FUN_00471610(); // get camera transform
    FUN_004a0370(&local_100, thisPtr + 0x80, iVar5 + 0x10, (float)thisPtr[0x8d] * DAT_00e445c8);

    fStack_70 = DAT_00e44564 - fStack_70;
    // Update predicted position (interpolation with offset)
    thisPtr[0x7a] = (int)(fStack_70 * local_100 + *pfVar1); // +0x1E8 x
    pfVar2 = (float*)(thisPtr + 0x7a);
    thisPtr[0x7b] = (int)(fStack_70 * fStack_fc + (float)thisPtr[0x7e]); // +0x1EC y
    thisPtr[0x7c] = (int)(fStack_70 * fStack_f8 + (float)thisPtr[0x7f]); // +0x1F0 z

    // Compute cross product for up vector adjustment
    iVar5 = FUN_00471610();
    pSomeFloat = (float*)(iVar5 + 0x10);
    iVar5 = FUN_00471610();
    fStack_c0 = pSomeFloat[2] * fStack_fc - *(float*)(iVar5 + 0x14) * fStack_f8;
    iVar5 = FUN_00471610();
    pSomeFloat = (float*)(iVar5 + 0x10);
    iVar5 = FUN_00471610();
    fStack_bc = *pSomeFloat * fStack_f8 - *(float*)(iVar5 + 0x18) * local_100;
    iVar5 = FUN_00471610();
    pSomeFloat = (float*)(iVar5 + 0x10);
    iVar5 = FUN_00471610();
    fStack_b8 = pSomeFloat[1] * local_100 - *(float*)(iVar5 + 0x10) * fStack_fc;

    fStack_e0 = *pfVar2 - *pfVar1;
    fStack_dc = (float)thisPtr[0x7b] - (float)thisPtr[0x7e];
    fStack_d8 = (float)thisPtr[0x7c] - (float)thisPtr[0x7f];

    FUN_004a0370(&fStack_e0, &fStack_e0, &fStack_c0, (float)thisPtr[0x8b] * DAT_00e445c8);
    *pfVar2 = fStack_e0 + *pfVar1;
    thisPtr[0x7b] = (int)((float)thisPtr[0x7e] + fStack_dc);
    thisPtr[0x7c] = (int)((float)thisPtr[0x7f] + fStack_d8);

    // Call virtual function (likely updateTransform)
    (**(code**)(*thisPtr + 0x18))();

    FUN_006c9120(thisPtr + 0x77, pfVar2, pfVar1); // compare positions?

    // Get camera transform and compute goal position
    iVar5 = FUN_00471610();
    fStack_10c = *(float*)(iVar5 + 0x38);
    uStack_114 = *(undefined8*)(iVar5 + 0x30);
    iVar5 = FUN_00471610();
    fStack_f4 = *pfVar2;
    fStack_f0 = (float)thisPtr[0x7b];
    fStack_d4 = *(float*)(iVar5 + 0x10) * fStack_7c + (float)uStack_114;
    fStack_d0 = *(float*)(iVar5 + 0x14) * fStack_7c + uStack_114._4_4_;
    fStack_10c = *(float*)(iVar5 + 0x18) * fStack_7c + fStack_10c;
    fStack_ec = (float)thisPtr[0x7c];
    uStack_114 = CONCAT44(fStack_d0, fStack_d4);
    local_118 = _DAT_00d5780c;
    fStack_e8 = _DAT_00d5780c;
    fStack_c8 = _DAT_00d5780c;
    fStack_cc = fStack_10c;
    thunk_FUN_006d2db0(&fStack_d4, &fStack_f4, &local_118); // collision check?

    // Smoothly interpolate position towards goal
    pSomeFloat = (float*)thisPtr[0x95];
    if ((float)pSomeFloat < local_118) {
        fVar8 = (float10)FUN_006c89b0(pSomeFloat, local_118, DAT_00d58cbc);
        local_118 = (float)fVar8;
        if ((float10)1.0f - fVar8 < (float10)_DAT_00d5f4a8) {
            local_118 = _DAT_00d5780c;
        }
    }
    fVar9 = _DAT_00d5780c;
    thisPtr[0x95] = (int)local_118;

    // If not fully interpolated, apply spring correction
    if (local_118 < fVar9) {
        fStack_f4 = *pfVar1 - *pfVar2;
        fStack_f0 = (float)thisPtr[0x7e] - (float)thisPtr[0x7b];
        fStack_ec = (float)thisPtr[0x7f] - (float)thisPtr[0x7c];
        fStack_e8 = 0.0f;
        FUN_0056afa0(&fStack_f4, &fStack_f4); // normalize?

        *pfVar2 = (*pfVar2 - (float)uStack_114) * local_118 + (float)uStack_114;
        thisPtr[0x7b] = (int)(((float)thisPtr[0x7b] - uStack_114._4_4_) * local_118 + uStack_114._4_4_);
        thisPtr[0x7c] = (int)(((float)thisPtr[0x7c] - fStack_10c) * local_118 + fStack_10c);

        fVar9 = _DAT_00d5780c;
        fVar10 = DAT_00d5ccf8;
        if (0.0f <= local_78) {
            fVar10 = _DAT_00d5780c;
        }
        fVar10 = (_DAT_00d5780c - local_118) * fVar10 * _DAT_00d5c458;
        *pfVar2 = fVar10 * fStack_c0 + *pfVar2;
        thisPtr[0x7b] = (int)(fVar10 * fStack_bc + (float)thisPtr[0x7b]);
        thisPtr[0x7c] = (int)(fVar10 * fStack_b8 + (float)thisPtr[0x7c]);

        if (fStack_3c < local_118) {
            fVar10 = (local_118 - fStack_3c) / (fVar9 - fStack_3c);
        }
        else {
            fVar10 = 0.0f;
        }
        dVar11 = (double)((fVar9 - fVar10) * DAT_00d5f00c - DAT_00d5f00c);
        FUN_00b99e20(); // some system call
        thisPtr[0x7b] = (int)((float)dVar11 * fStack_40 + (float)thisPtr[0x7b]);

        // Re-check collision after correction
        fStack_d4 = *pfVar2;
        fStack_d0 = (float)thisPtr[0x7b];
        fStack_cc = (float)thisPtr[0x7c];
        uStack_24 = (float)uStack_114;
        uStack_20 = uStack_114._4_4_;
        fStack_c8 = _DAT_00d5780c;
        fStack_1c = fStack_10c;
        fStack_18 = _DAT_00d5780c;
        cVar4 = thunk_FUN_006d2db0(&uStack_24, &fStack_d4, &local_118);
        if (cVar4 == '\0') {
            // If still colliding, snap back
            *pfVar2 = (*pfVar2 - (float)uStack_114) * local_118 + (float)uStack_114;
            thisPtr[0x7b] =
                (int)(((float)thisPtr[0x7b] - uStack_114._4_4_) * local_118 + uStack_114._4_4_);
            thisPtr[0x7c] = (int)(((float)thisPtr[0x7c] - fStack_10c) * local_118 + fStack_10c);
        }
    }

    fVar9 = _DAT_00d5780c;
    // Store final position/rotation for rendering
    _DAT_0112a8d0 = *(undefined8*)(thisPtr + 0x77); // rotation quaternion?
    _DAT_0112a8d8 = thisPtr[0x79]; // w component?
    thisPtr[8] = (int)*pfVar2;   // +0x20 x position
    thisPtr[9] = thisPtr[0x7b]; // +0x24 y position
    thisPtr[0xb] = (int)fVar9;  // +0x2C? (maybe z scale?)
    thisPtr[10] = thisPtr[0x7c]; // +0x28 z position
    thisPtr[0xc] = (int)*pfVar1; // +0x30 previous x?
    thisPtr[0xd] = thisPtr[0x7e]; // +0x34 previous y?
    thisPtr[0xf] = (int)fVar9;   // +0x3C?
    thisPtr[0xe] = thisPtr[0x7f]; // +0x38 previous z?
    thisPtr[0x10] = thisPtr[0x77]; // +0x40 rotation x?
    thisPtr[0x11] = thisPtr[0x78]; // +0x44 rotation y?
    thisPtr[0x13] = (int)fVar9;   // +0x4C?
    thisPtr[0x12] = thisPtr[0x79]; // +0x48 rotation z?

    pSomeFloat = (float*)(local_6c * DAT_00e445c8);
    // If debug/audio flag, play sound with velocity magnitude
    if (((*(uint*)(iStack_120 + 0x8e0) >> 9 & 1) != 0) && (cVar4 = FUN_00481660(), cVar4 == '\0')) {
        FUN_006d7ea0(&pSomeFloat);
    }

    fVar8 = (float10)FUN_006c89b0(thisPtr[0x14], pSomeFloat, _DAT_00e511d8);
    thisPtr[0x14] = (int)(float)fVar8;
    FUN_00473bb0((float)fVar8); // update some audio parameter

    if (iStack_84 != 0) {
        FUN_004daf90(&iStack_84); // release memory?
    }
    if (iStack_8c != 0) {
        FUN_004daf90(&iStack_8c);
    }
    return;
}
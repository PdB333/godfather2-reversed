// FUNC_NAME: CharacterController::updateMovement
// Function at 0x006d3340 - Main update loop for character movement physics
// Handles linear and angular velocity damping, steering, arrival, and collision response
// thisPtr offsets (all ints stored as float when needed):
// +0x04: position (x,y,z,w) - 4 ints
// +0x14: rotation axis (x?) 
// +0x15: rotation axis (y?) 
// +0x16: rotation axis (z?) 
// +0x17: rotation axis (w?) 
// +0x18: velocity (x,y,z,w) - 4 ints
// +0x1c: angular velocity? (x?) stored as int
// +0x1d: angular velocity damping target? 
// +0x1e: timer (e.g., time since last land)
// +0x1f: flag byte (e.g., inAir, etc.)
// +0x20: current speed or throttle scalar
// +0x21: timer for something
// +0x22: speed magnitude (float stored as int)
// +0x23: pitch/roll interpolation target
// +0x24: pitch/roll interpolation target
// +0x25: cooldown timer (e.g., dash recharge)
void __thiscall FUN_006d3340(int* thisPtr, int inputState, int unknown3, float deltaTime, float param5, uint flags, int targetTransform, int unknown8)
{
    bool bVar1;
    uint uVar2;
    char cVar3;
    char cVar4;
    float* pfVar5;
    float* pfVar6;
    float10 fVar7;
    float fVar8;
    double dVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    uint uVar13;
    char cStack_82;
    char cStack_81;
    undefined4 uStack_80;
    char cStack_7c;
    undefined4 uStack_78;
    float local_74;
    uint local_70;
    float* local_6c;
    float local_68;
    float local_64;
    float* local_60;
    float fStack_4c;
    float fStack_48;
    float* local_44;
    float local_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    undefined1 auStack_20[28];

    // Decrement cooldown timer (offset 0x94)
    if ((0.0 < (float)thisPtr[0x25]) && 
        (fVar8 = (float)thisPtr[0x25] - deltaTime, thisPtr[0x25] = (int)fVar8, fVar8 < 0.0)) {
        thisPtr[0x25] = 0;
    }

    // Target position from targetTransform + 0x30
    local_44 = (float*)(targetTransform + 0x30);
    // Current orientation vector (offset 0x30)
    local_60 = (float*)(thisPtr + 0xc);

    // Delta between target and current orientation
    local_30 = *(float*)(targetTransform + 0x30) - (float)thisPtr[0xc];
    fStack_2c = *(float*)(targetTransform + 0x34) - (float)thisPtr[0xd];
    fStack_28 = *(float*)(targetTransform + 0x38) - (float)thisPtr[0xe];
    fStack_24 = *(float*)(targetTransform + 0x3c) - (float)thisPtr[0xf];

    // Check if inputState has flag 0x200 (bit9 at offset 0x8e8)
    if ((*(uint*)(inputState + 0x8e8) >> 9 & 1) == 0) {
        local_70 = CONCAT31(local_70._1_3_, 1); // set flag byte
        if (SQRT(local_30 * local_30 + fStack_2c * fStack_2c + fStack_28 * fStack_28) / deltaTime <= DAT_00e51180) 
            goto LAB_006d33f3;
    }
    else {
LAB_006d33f3:
        local_70 = local_70 & 0xffffff00; // clear flag byte
    }

    // Check inputState flags at offset 0x8e4 (bit31 and bit30)
    if (((int)*(uint*)(inputState + 0x8e4) < 0) || ((*(uint*)(inputState + 0x8e4) >> 0x1e & 1) != 0)) {
        cVar4 = '\x01';
    }
    else {
        cVar4 = '\0';
    }
    uStack_78._0_3_ = CONCAT12(cVar4, (undefined2)uStack_78);

    cVar3 = FUN_00410eb0(); // likely "isAnalogInputActive" or similar
    uVar2 = local_70;
    fVar10 = local_74;
    fVar8 = DAT_00d5c454;
    if (cVar3 == '\0') {
        fVar12 = (float)thisPtr[0x23];
        if ((float)thisPtr[0x20] <= 0.0) {
            if (cVar4 == '\0') {
                thisPtr[0x23] = (int)((DAT_00e51134 - fVar12) * DAT_00d5c454 + fVar12);
                fVar12 = DAT_00e51188;
            }
            else {
                thisPtr[0x23] = (int)((DAT_00e51154 - fVar12) * DAT_00d5c454 + fVar12);
                fVar12 = DAT_00e51190;
            }
        }
        else {
            thisPtr[0x23] = (int)((DAT_00e51140 - fVar12) * DAT_00d5c454 + fVar12);
            fVar12 = DAT_00e5118c;
        }
        thisPtr[0x24] = (int)((fVar12 - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
    }
    else {
        thisPtr[0x23] = (int)((DAT_00e51198 - (float)thisPtr[0x23]) * DAT_00d5c454 + (float)thisPtr[0x23]);
        thisPtr[0x24] = (int)((DAT_00e5119c - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
    }

    uVar13 = DAT_00e44680; // flag mask?
    local_74 = (float)((uint)local_74 & 0xffffff00);

    // Handle angular velocity (offset 0x1d) damping
    if ((float)(flags & DAT_00e44680) <= 0.0) {
        thisPtr[0x1d] = 0;
    }
    else {
        local_40 = (float)thisPtr[0x1a];
        fStack_38 = DAT_00e44564 - (float)thisPtr[0x18];
        pfVar5 = (float*)(thisPtr + 0x18);
        local_6c = (float*)SQRT(local_40 * local_40 + fStack_38 * fStack_38);
        fStack_3c = 0.0;
        fStack_34 = 0.0;
        if (0.0 < (float)local_6c) {
            local_74._1_3_ = SUB43(fVar10, 1);
            local_74 = (float)CONCAT31(local_74._1_3_, 1);
            fVar7 = (float10)FUN_006d0e40(flags, thisPtr[0x1d]); // likely angular velocity spring
            thisPtr[0x1d] = (int)(float)fVar7;
            fVar7 = (float10)FUN_006d1420(uVar2, (float)fVar7);
            local_64 = (float)(fVar7 * (float10)DAT_00e510f8);
            local_68 = (float)(fVar7 * (float10)DAT_00e510f8 * (float10)(float)thisPtr[0x1d] * (float10)deltaTime);
            cVar4 = FUN_00410eb0();
            fVar8 = local_68;
            if (cVar4 != '\0') {
                fVar8 = local_64 * deltaTime;
            }
            local_64 = fVar8 * DAT_00d5c458;
            dVar9 = (double)local_64;
            FUN_00b99fcb(); // likely cos() or sin()
            fVar8 = (float)dVar9 / (float)local_6c;
            local_40 = fVar8 * local_40;
            fStack_3c = fVar8 * fStack_3c;
            fStack_38 = fVar8 * fStack_38;
            fStack_34 = fVar8 * fStack_34;
            dVar9 = (double)local_64;
            FUN_00b99e20(); // likely sin() or cos()
            fStack_34 = (float)dVar9;
            local_30 = *pfVar5;
            fStack_2c = (float)thisPtr[0x19];
            fStack_28 = (float)thisPtr[0x1a];
            fStack_24 = (float)thisPtr[0x1b];
            FUN_0056ce80(&local_40, pfVar5, pfVar5); // likely quaternion rotation
            thisPtr[0x1b] = 0;
            uVar13 = DAT_00e44680;
            fStack_34 = DAT_00d5780c / SQRT(*pfVar5 * *pfVar5 + (float)thisPtr[0x19] * (float)thisPtr[0x19] + (float)thisPtr[0x1a] * (float)thisPtr[0x1a]);
            local_40 = fStack_34 * *pfVar5;
            fStack_3c = fStack_34 * (float)thisPtr[0x19];
            fStack_38 = fStack_34 * (float)thisPtr[0x1a];
            fStack_34 = fStack_34 * (float)thisPtr[0x1b];
            fVar8 = DAT_00e510fc;
            if ((fStack_3c <= DAT_00e510fc) || (fVar8 = DAT_00e51100, DAT_00e51100 <= fStack_3c)) {
                fStack_3c = fVar8;
            }
            fVar8 = fStack_38 * fStack_38 + local_40 * local_40;
            if (0.0 < (float)((uint)fVar8 & DAT_00e44680)) {
                fVar8 = (DAT_00d5780c - fStack_3c * fStack_3c) / fVar8;
                fVar10 = DAT_00d5780c;
                if (local_40 < 0.0) {
                    fVar10 = DAT_00d5ccf8;
                }
                fVar12 = DAT_00d5ccf8;
                if (0.0 <= fStack_38) {
                    fVar12 = DAT_00d5780c;
                }
                fStack_38 = SQRT(fVar8 * fStack_38 * fStack_38) * fVar12;
                fVar12 = (float)thisPtr[0x22];
                local_40 = SQRT(fVar8 * local_40 * local_40) * fVar10;
                *pfVar5 = fVar12 * local_40;
                thisPtr[0x19] = (int)(fVar12 * fStack_3c);
                thisPtr[0x1a] = (int)(fVar12 * fStack_38);
                thisPtr[0x1b] = (int)(fVar12 * fStack_34);
            }
        }
    }

    // Handle linear velocity (offset 0x1c) damping (similar to angular but different)
    if ((float)((uint)param5 & uVar13) <= 0.0) {
        thisPtr[0x1c] = 0;
    }
    else {
        pfVar5 = (float*)(**(code**)(*thisPtr + 0x14))(); // get something via vtable
        pfVar6 = (float*)(**(code**)(*thisPtr + 0x10))(); // get another vector
        local_30 = *pfVar6 - *pfVar5;
        fStack_2c = pfVar6[1] - pfVar5[1];
        fStack_28 = pfVar6[2] - pfVar5[2];
        fStack_24 = pfVar6[3] - pfVar5[3];
        fStack_38 = DAT_00e44564 - local_30;
        local_40 = fStack_28;
        if (0.0 < param5) {
            local_40 = 0.0 - fStack_28;
            fStack_38 = 0.0 - fStack_38;
        }
        fStack_34 = 0.0;
        fStack_3c = 0.0;
        if (0.0 < SQRT(fStack_38 * fStack_38 + 0.0 + local_40 * local_40)) {
            local_74 = (float)CONCAT31(local_74._1_3_, 1);
            fVar7 = (float10)FUN_006d0e40(param5, thisPtr[0x1c]);
            thisPtr[0x1c] = (int)(float)fVar7;
            fVar7 = (float10)FUN_006d1420(uVar2, (float)fVar7);
            local_64 = (float)fVar7;
            local_6c = (float*)(float)(fVar7 * (float10)(float)thisPtr[0x1c] * (float10)deltaTime);
            cVar4 = FUN_00410eb0();
            if (cVar4 != '\0') {
                local_6c = (float*)(local_64 * deltaTime);
            }
            dVar9 = (double)(float)local_6c;
            FUN_00b99e20();
            local_64 = (float)dVar9;
            dVar9 = (double)(float)local_6c;
            FUN_00b99fcb();
            fVar8 = (float)thisPtr[0x18];
            thisPtr[0x18] = (int)(fVar8 * local_64 - (float)thisPtr[0x1a] * (float)dVar9);
            fVar8 = fVar8 * (float)dVar9 + (float)thisPtr[0x1a] * local_64;
            thisPtr[0x1a] = (int)fVar8;
            fVar8 = SQRT((float)thisPtr[0x18] * (float)thisPtr[0x18] + (float)thisPtr[0x19] * (float)thisPtr[0x19] + fVar8 * fVar8);
            if (0.0 < fVar8) {
                fVar8 = (float)thisPtr[0x22] / fVar8;
                thisPtr[0x18] = (int)(fVar8 * (float)thisPtr[0x18]);
                thisPtr[0x19] = (int)(fVar8 * (float)thisPtr[0x19]);
                thisPtr[0x1a] = (int)(fVar8 * (float)thisPtr[0x1a]);
                thisPtr[0x1b] = (int)(fVar8 * (float)thisPtr[0x1b]);
            }
        }
    }

    // Compute desired direction (offset 0x14-0x17) towards target (from local_44)
    pfVar5 = local_44;
    fVar8 = *local_60;
    fVar10 = local_60[2];
    thisPtr[0x15] = 0;
    thisPtr[0x17] = 0;
    fVar8 = *local_44 - fVar8;
    fVar10 = local_44[2] - fVar10;
    fVar12 = SQRT(fVar10 * fVar10 + fVar8 * fVar8);
    if (0.0 < fVar12) {
        fVar12 = DAT_00d5780c / fVar12;
        thisPtr[0x14] = (int)(fVar12 * fVar8);
        thisPtr[0x16] = (int)(fVar12 * fVar10);
    }

    // Position delta to target (from targetTransform+0x30)
    local_30 = *local_44 - (float)thisPtr[4];
    fStack_2c = local_44[1] - (float)thisPtr[5];
    fStack_28 = local_44[2] - (float)thisPtr[6];
    fStack_24 = local_44[3] - (float)thisPtr[7];

    // Check flag at inputState+0x490 bit 8 (0x100)
    local_64 = (float)(*(uint*)(inputState + 0x490) & 0x100);
    // bVar1 = dot product of current rotation axis (thisPtr[0x14], thisPtr[0x16]) with position delta
    bVar1 = 0.0 < (float)thisPtr[0x16] * fStack_28 + (float)thisPtr[0x14] * local_30;
    local_44 = (float*)SQRT(fStack_2c * fStack_2c + fStack_28 * fStack_28 + local_30 * local_30);

    // Check for early arrival if close enough and not facing away and no flag
    if (((local_64 == 0.0) && ((float)local_44 <= DAT_00e51148)) && (!bVar1)) {
        FUN_006d2b90(pfVar5, local_44, unknown8); // likely stop and align
        return;
    }

    // Choose movement state based on flags
    if ((char)local_70 == '\0') {
        if (local_74._0_1_ == '\0') {
            if ((float)thisPtr[0x21] <= DAT_00e510d4) {
                return; // no movement needed
            }
            goto LAB_006d3b28;
        }
        cVar4 = FUN_00410eb0();
        fVar8 = DAT_00d5c454;
        if (cVar4 == '\0') {
            thisPtr[0x23] = (int)((DAT_00e51164 - (float)thisPtr[0x23]) * DAT_00d5c454 + (float)thisPtr[0x23]);
            thisPtr[0x24] = (int)((DAT_00e51194 - (float)thisPtr[0x24]) * fVar8 + (float)thisPtr[0x24]);
        }
    }
    else if (local_74._0_1_ == '\0') {
        goto LAB_006d3b28;
    }
    thisPtr[0x25] = DAT_00e5113c; // set cooldown

LAB_006d3b28:
    if (uStack_78._2_1_ != '\0') {
        thisPtr[0x25] = 0; // cancel cooldown if special input
    }

    // Reduce speed if moving and conditions met (e.g., uphill)
    if ((((bVar1) || (DAT_00e510d4 < (float)thisPtr[0x21])) &&
        (((char)local_70 != '\0' || ((float)thisPtr[9] <= (float)thisPtr[5] + DAT_00d58cbc)))) &&
        (local_68 = (float)thisPtr[0x22], DAT_00e51174 <= local_68)) {
        fVar7 = (float10)FUN_006d02d0(local_68, DAT_00e51178, deltaTime * DAT_00d5f2b0);
        thisPtr[0x22] = (int)(float)fVar7;
    }

    // Update rotation to face target using vtable call
    pfVar5 = (float*)(targetTransform + 0x30);
    (**(code**)(*thisPtr + 0x18))(auStack_20, pfVar5, unknown8);
    cStack_82 = '\0';
    if (((cStack_7c == '\0') || ((char)uStack_80 != '\0')) || 
        (uStack_78 = (float)((uint)uStack_78 & 0xffffff00), DAT_00e510c8 != '\0')) {
        uStack_78 = (float)CONCAT31(uStack_78._1_3_, 1);
    }

    FUN_006d14b0(CONCAT31((int3)((uint)uStack_78 >> 8), (char)unknown8 == '\0'), deltaTime, targetTransform, &fStack_2c, uStack_78, &cStack_82);

    // Compute velocity error (difference between desired velocity and current)
    fStack_4c = *pfVar5 - (float)thisPtr[0x18];
    fStack_48 = *(float*)(targetTransform + 0x34) - (float)thisPtr[0x19];
    local_44 = (float*)(*(float*)(targetTransform + 0x38) - (float)thisPtr[0x1a]);
    local_40 = *(float*)(targetTransform + 0x3c) - (float)thisPtr[0x1b];

    uStack_78 = DAT_00d5780c;
    fStack_3c = (float)thisPtr[4];
    fStack_34 = (float)thisPtr[6];
    local_30 = (float)thisPtr[7];
    fStack_38 = (float)thisPtr[5] - DAT_00e51168;
    cStack_81 = '\0';
    cVar4 = FUN_006d0ee0(thisPtr + 4, &fStack_3c, &uStack_78); // check if grounded or on slope
    fVar8 = fStack_48;
    if (cVar4 == '\0') {
        cStack_81 = '\x01';
        if (((char)uStack_80 == '\0') && (cVar4 = FUN_00410eb0(), fVar8 = fStack_48, cVar4 == '\0')) {
            fVar10 = (float)thisPtr[5];
            fVar12 = fStack_48 - fVar10;
            if ((fVar12 < 0.0) && (fVar8 = fVar10, fVar12 <= DAT_00e44564 - DAT_00e51168)) {
                fVar8 = fVar12 + DAT_00e51168 + fVar10;
            }
            if (DAT_00d5842c <= uStack_78) {
                fVar10 = (DAT_00d5780c - uStack_78) * DAT_00d5ddec;
                fVar8 = (DAT_00d5780c - fVar10) * fStack_48 + fVar10 * fVar8;
            }
        }
    }
    fStack_48 = fVar8;

    cVar4 = cStack_82;
    if ((((cStack_82 == '\0') && (cStack_7c != '\0')) && (local_70 != 0)) && 
        ((cVar3 = FUN_00410eb0(), cVar3 == '\0' && (cVar3 = FUN_006d0ee0(&fStack_4c, &fStack_3c, &uStack_78), cVar3 == '\0')))) {
        fVar8 = (DAT_00d5780c - uStack_78) * DAT_00e51168;
        fStack_48 = fVar8 + fStack_48;
        thisPtr[0x19] = (int)((float)thisPtr[0x19] - fVar8);
    }

    FUN_006d16b0(pfVar5, &fStack_4c, &fStack_2c, deltaTime, uStack_80); // apply velocity change

    // Increase speed if conditions met
    if ((((cStack_7c != '\0') && (cVar4 == '\0')) && 
        ((local_70 != 0 || (((float)thisPtr[5] <= (float)thisPtr[9] && (float)thisPtr[9] != (float)thisPtr[5] || (DAT_00e510d4 < (float)thisPtr[0x21])))))) && 
        (local_74 = (float)thisPtr[0x22], local_74 < DAT_00e51174)) {
        fVar7 = (float10)FUN_006d02d0(local_74, DAT_00e51178, deltaTime * DAT_00d5f2b0);
        thisPtr[0x22] = (int)(float)fVar7;
        FUN_006d0960(pfVar5); // play sound or visual effect?
    }

    // Clamp position to a max distance from target
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    pfVar6 = (float*)(thisPtr + 4);
    fStack_3c = (float)thisPtr[4] - *pfVar5;
    fStack_38 = (float)thisPtr[5] - fVar8;
    fStack_34 = (float)thisPtr[6] - fVar10;
    local_30 = (float)thisPtr[7] - fVar12;
    fVar11 = SQRT(fStack_38 * fStack_38 + fStack_34 * fStack_34 + fStack_3c * fStack_3c);
    if (DAT_00e5117c * DAT_00e51178 < fVar11) {
        fVar11 = (DAT_00e5117c * DAT_00e51178) / fVar11;
        *pfVar6 = fVar11 * fStack_3c + *pfVar5;
        thisPtr[5] = (int)(fVar11 * fStack_38 + fVar8);
        thisPtr[6] = (int)(fVar11 * fStack_34 + fVar10);
        thisPtr[7] = (int)(fVar11 * local_30 + fVar12);
    }

    // Check collision with environment
    cVar4 = FUN_006d2db0(pfVar5, pfVar6, 0);
    if (cVar4 != '\0') {
        // Collision detected: stop movement, increment timer, set previous position to target
        thisPtr[0x1e] = 0;
        *(undefined1*)(thisPtr + 0x1f) = 0;
        thisPtr[0x21] = (int)((float)thisPtr[0x21] + deltaTime);
        fVar8 = *(float*)(targetTransform + 0x34);
        fVar10 = *(float*)(targetTransform + 0x38);
        fVar12 = *(float*)(targetTransform + 0x3c);
        *local_6c = *pfVar5;
        local_6c[1] = fVar8;
        local_6c[2] = fVar10;
        local_6c[3] = fVar12;
        return;
    }

    // Update velocity if not colliding
    if ((((cStack_81 != '\0') || ((char)uStack_80 != '\0')) || (cStack_82 == '\0')) || 
        (DAT_00e51130 < (float)thisPtr[0x1e])) {
        cVar4 = FUN_006d1890(pfVar6, pfVar5);
        if (cVar4 != '\0') {
            fVar8 = *(float*)(targetTransform + 0x34);
            fVar10 = *(float*)(targetTransform + 0x38);
            fVar12 = *(float*)(targetTransform + 0x3c);
            thisPtr[0x18] = (int)(*pfVar5 - *pfVar6);
            thisPtr[0x19] = (int)(fVar8 - (float)thisPtr[5]);
            thisPtr[0x1a] = (int)(fVar10 - (float)thisPtr[6]);
            thisPtr[0x1b] = (int)(fVar12 - (float)thisPtr[7]);
        }
    }
    else {
        // Reset speed scalar if not in air and not just landed
        thisPtr[0x20] = (int)DAT_00d5780c;
    }

    // Update timers and set velocity to move towards target
    thisPtr[0x1e] = (int)((float)thisPtr[0x1e] + deltaTime);
    *(undefined1*)(thisPtr + 0x1f) = 1;
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    thisPtr[0x18] = (int)(*pfVar5 - *pfVar6);
    thisPtr[0x19] = (int)(fVar8 - (float)thisPtr[5]);
    thisPtr[0x1a] = (int)(fVar10 - (float)thisPtr[6]);
    thisPtr[0x1b] = (int)(fVar12 - (float)thisPtr[7]);
    thisPtr[0x1b] = 0;
    thisPtr[0x21] = 0;
    fVar8 = *pfVar6 - *pfVar5;
    fVar10 = (float)thisPtr[5] - *(float*)(targetTransform + 0x34);
    fVar12 = (float)thisPtr[6] - *(float*)(targetTransform + 0x38);
    thisPtr[0x22] = (int)SQRT(fVar10 * fVar10 + fVar12 * fVar12 + fVar8 * fVar8);
    fVar8 = *(float*)(targetTransform + 0x34);
    fVar10 = *(float*)(targetTransform + 0x38);
    fVar12 = *(float*)(targetTransform + 0x3c);
    *local_6c = *pfVar5;
    local_6c[1] = fVar8;
    local_6c[2] = fVar10;
    local_6c[3] = fVar12;
    return;
}
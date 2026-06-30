// FUNC_NAME: VehiclePhysics::integrate
float __thiscall VehiclePhysics::integrate(int thisPtr, float dt)
{
    float *pfVar1;
    float *pfVar2;
    undefined4 uVar3;
    char cVar4;
    int iVar5;
    float10 fVar6;
    double dVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float local_c8;
    float local_c4;
    float local_c0;
    float local_bc;
    float local_b8;
    float fStack_b4;
    float local_b0;
    float local_ac;
    float local_a8;
    float local_a4;
    float local_a0;
    float fStack_9c;
    float fStack_98;
    float fStack_94;
    undefined8 local_8c;
    float local_84;
    undefined1 local_80 [4];
    undefined1 local_7c [4];
    undefined1 local_78 [4];
    float local_74;
    undefined1 local_6c [4];
    float local_68;
    float local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float local_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    undefined4 local_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    float fStack_24;
    undefined1 local_1c [24];
    
    fStack_54 = 0.0;
    fStack_44 = 0.0;
    fStack_34 = 0.0;
    fStack_24 = _DAT_00d5780c; // identity quaternion w component
    iVar5 = FUN_004262f0(0); // getGameManager
    local_a4 = *(float *)(thisPtr + 0x50); // vehicle mass
    local_bc = *(float *)(iVar5 + 0x150) * local_a4; // gravity * mass
    // Initialize identity quaternion
    local_60 = _DAT_00d5780c; // 1.0
    fStack_5c = 0.0;
    fStack_58 = 0.0;
    fStack_54 = 0.0;
    local_50 = 0.0;
    fStack_4c = _DAT_00d5780c;
    fStack_48 = 0.0;
    fStack_44 = 0.0;
    local_40 = 0.0;
    fStack_3c = 0.0;
    fStack_38 = _DAT_00d5780c;
    fStack_34 = 0.0;
    local_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    fStack_24 = _DAT_00d5780c;
    local_b8 = *(float *)(thisPtr + 0x110); // vehicle orientation quaternion x
    fStack_b4 = *(float *)(thisPtr + 0x114); // orientation quaternion y
    local_b0 = *(float *)(thisPtr + 0x118); // orientation quaternion z
    fVar8 = DAT_00e44594; // default damping
    if ((*(byte *)(thisPtr + 0xdc) & 1) == 0) { // check bit 0 of flags
        if ((*(uint *)(thisPtr + 0xdc) >> 1 & 1) == 0) { // check bit 1
            if (((*(uint *)(thisPtr + 0xdc) >> 2 & 1) != 0) && // check bit 2
               (local_c8 = DAT_00e44600 - (DAT_00d5f19c - *(float *)(thisPtr + 0xd0)), // speed - targetSpeed
               fVar8 = DAT_00d5f194, local_c8 <= DAT_00d5f194)) goto LAB_006cdc7b;
        }
        else {
            local_c8 = DAT_00d5f19c - *(float *)(thisPtr + 0xd0); // targetSpeed - currentSpeed
            fVar8 = DAT_00d5f198;
            if (DAT_00d5f198 <= local_c8) goto LAB_006cdc7b;
        }
    }
    local_c8 = fVar8; // damping value
LAB_006cdc7b:
    fVar13 = *(float *)(thisPtr + 0xf4) - *(float *)(thisPtr + 0xe8); // velocity delta z
    fVar11 = *(float *)(thisPtr + 0xf0) - *(float *)(thisPtr + 0xe4); // velocity delta y
    fVar8 = *(float *)(thisPtr + 0xec) - *(float *)(thisPtr + 0xe0); // velocity delta x
    local_c0 = SQRT(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8); // speed magnitude
    if (local_c0 < DAT_00e4475c) { // min speed threshold
        local_c8 = (_DAT_00d5780c - local_c0 * _DAT_00d5f190) * DAT_00e44594 +
                   local_c0 * _DAT_00d5f190 * local_c8; // blend damping
    }
    FUN_0046cf70(&local_60, thisPtr + 0x11c, local_c8, 0); // quaternionSlerp
    *(undefined8 *)(thisPtr + 0x140) = *(undefined8 *)(thisPtr + 0xf8); // copy velocity to newVelocity
    local_a0 = fStack_b4 * local_50 + local_b8 * local_60 + local_b0 * local_40; // transform velocity
    fStack_9c = fStack_b4 * fStack_4c + local_b8 * fStack_5c + local_b0 * fStack_3c;
    fStack_98 = fStack_b4 * fStack_48 + local_b8 * fStack_58 + local_b0 * fStack_38;
    fStack_94 = fStack_b4 * fStack_44 + local_b8 * fStack_54 + local_b0 * fStack_34;
    *(undefined4 *)(thisPtr + 0x148) = *(undefined4 *)(thisPtr + 0x100); // copy angular velocity
    fVar13 = *(float *)(thisPtr + 0x100) - *(float *)(thisPtr + 0x10c); // angular velocity delta z
    fVar8 = *(float *)(thisPtr + 0xf8) - *(float *)(thisPtr + 0x104); // angular velocity delta x
    pfVar1 = (float *)(thisPtr + 0x140); // newVelocity pointer
    fVar11 = *(float *)(thisPtr + 0xfc) - *(float *)(thisPtr + 0x108); // angular velocity delta y
    local_c4 = SQRT(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8); // angular speed
    if (**(int **)(DAT_012233a0 + 4) == 0) { // check global physics config
        local_ac = 0.0;
    }
    else {
        local_ac = (float)(**(int **)(DAT_012233a0 + 4) + -0x1f30); // physics config offset
    }
    fVar8 = local_ac;
    fVar6 = (float10)FUN_006cc570(local_c0, local_c8, local_bc * DAT_00e44748, _DAT_00d5f0e4); // computeForce
    local_c0 = (float)fVar6;
    cVar4 = FUN_007f7c50(); // isPlayerControlled?
    uVar3 = _DAT_00d5f0dc; // default friction
    if (cVar4 != '\0') {
        uVar3 = _DAT_00d5f0e0; // player friction
    }
    fVar6 = (float10)FUN_006cc570(local_c4, DAT_00e44594, local_a4 * DAT_00e44748, uVar3); // computeTorque
    fVar11 = DAT_00d5833c; // spring constant
    fVar13 = DAT_00d5f18c; // damper constant
    if (local_c0 < (float)fVar6) {
        fVar11 = DAT_00d5f18c;
        fVar13 = DAT_00d5833c;
    }
    local_c4 = *(float *)((int)fVar8 + 0x2c64) * ((float)fVar6 * fVar13 + local_c0 * fVar11); // suspension force
    fVar11 = 0.0;
    fVar8 = fVar11;
    if (*(float *)(thisPtr + 0x164) <= 0.0 && *(float *)(thisPtr + 0x164) != 0.0) { // check brake
        fVar8 = (*(float *)(thisPtr + 300) * fStack_9c + *(float *)(thisPtr + 0x128) * local_a0 +
                *(float *)(thisPtr + 0x130) * fStack_98) * DAT_00e44750; // brake force
    }
    pfVar2 = (float *)(thisPtr + 0x134); // position pointer
    *pfVar2 = *pfVar1 + (fVar8 * *(float *)(thisPtr + 0x128) + local_a0) * local_c4; // update position x
    fVar13 = _DAT_00d5c458; // dt
    *(float *)(thisPtr + 0x138) =
         *(float *)(thisPtr + 0x144) + (*(float *)(thisPtr + 300) * fVar8 + fStack_9c) * local_c4; // update position y
    *(float *)(thisPtr + 0x13c) =
         *(float *)(thisPtr + 0x148) + (*(float *)(thisPtr + 0x130) * fVar8 + fStack_98) * local_c4; // update position z
    local_c8 = 0.0;
    local_c0 = 0.0;
    local_b8 = 0.0;
    local_8c = (ulonglong)(uint)local_8c._4_4_ << 0x20;
    local_74 = 0.0;
    local_68 = 0.0;
    if ((*(uint *)(thisPtr + 0xdc) >> 0xb & 1) == 0) { // check collision flag
        FUN_006cd540(&local_b8, &local_c8, &local_a8, thisPtr + 0xe0); // getCollisionNormal
        FUN_006cd540(&local_8c, &local_c0, &local_a8, thisPtr + 0xec); // getCollisionNormal
        local_a8 = ((float)local_8c + local_b8) * _DAT_00d5c458; // combined normal
        FUN_006cd540(local_78, local_7c, local_80, thisPtr + 0xf8); // getCollisionNormal
        FUN_006cd540(local_6c, local_80, local_7c, thisPtr + 0x104); // getCollisionNormal
        fVar11 = (local_68 + local_74) * _DAT_00d5c458;
        fVar13 = _DAT_00d5c458;
    }
    else {
        local_a8 = 0.0;
        local_c8 = fVar11;
    }
    fVar9 = 0.0;
    fVar8 = (float)((uint)local_a8 & DAT_00e44680); // bitwise AND with mask
    if ((float)((uint)local_a8 & DAT_00e44680) <= (float)((uint)fVar11 & DAT_00e44680)) {
        fVar8 = (float)((uint)fVar11 & DAT_00e44680);
    }
    if (0.0 < *(float *)(thisPtr + 0x164) || *(float *)(thisPtr + 0x164) == 0.0) { // check brake
        if (local_c0 < DAT_00d5ef88) {
            fVar9 = DAT_00d5ef88 - local_c0;
        }
        if ((DAT_00d5ef6c < local_c8) && (fVar9 <= local_c8 - DAT_00d5ef6c)) {
            fVar9 = local_c8 - DAT_00d5ef6c;
        }
    }
    else {
        if (local_c8 < DAT_00d5ef88) {
            fVar9 = DAT_00d5ef88 - local_c8;
        }
        if ((DAT_00d5ef6c < local_c0) && (fVar9 <= local_c0 - DAT_00d5ef6c)) {
            fVar9 = local_c0 - DAT_00d5ef6c;
        }
    }
    if (fVar8 <= fVar9) {
        fVar8 = fVar9;
    }
    local_c8 = fVar8 * _DAT_00d5f0d8; // friction force
    if (fVar13 < fVar8 * _DAT_00d5f0d8) {
        local_c8 = fVar13;
    }
    dVar7 = (double)(local_bc * fVar13); // gravity * dt
    FUN_00b9c041(); // getTimeStep
    local_c0 = (float)dVar7 * local_c4 * DAT_00d5eee4 * local_a8; // gravity impulse
    dVar7 = (double)(local_a4 * _DAT_00d5c458); // mass * dt
    local_bc = local_c0;
    FUN_00b9c041(); // getTimeStep
    if ((_DAT_0112a830 & 1) == 0) {
        DAT_0112a82c = *(float *)((int)local_ac + 0x2c6c); // get wheel radius
        _DAT_0112a830 = _DAT_0112a830 | 1;
    }
    local_ac = (float)dVar7 * local_c4 * DAT_00d5eee4 *
               (*(float *)((int)local_ac + 0x2c68) + *(float *)(thisPtr + 0xd4)) * DAT_00d5ccf8; // wheel force
    iVar5 = FUN_004262f0(0); // getGameManager
    fVar8 = *(float *)(iVar5 + 0x44); // gravity x
    fVar11 = *(float *)(iVar5 + 0x48); // gravity y
    fVar13 = *(float *)(iVar5 + 0x40); // gravity z
    fStack_b4 = fVar8 * local_c0; // gravity impulse x
    local_b0 = fVar11 * local_c0; // gravity impulse y
    fVar10 = *(float *)(iVar5 + 0x54) * DAT_0112a82c; // wheel torque x
    fVar12 = *(float *)(iVar5 + 0x58) * DAT_0112a82c; // wheel torque y
    fVar9 = *(float *)(iVar5 + 0x50); // wheel force z
    fVar14 = *(float *)(iVar5 + 0x54); // wheel torque x
    fVar15 = *(float *)(iVar5 + 0x58); // wheel torque y
    *pfVar2 = *(float *)(iVar5 + 0x50) * DAT_0112a82c + fVar13 * local_bc + *pfVar2; // update position
    *(float *)(thisPtr + 0x138) = *(float *)(thisPtr + 0x138) + fVar10 + fVar8 * local_bc;
    *(float *)(thisPtr + 0x13c) = *(float *)(thisPtr + 0x13c) + fVar12 + fVar11 * local_bc;
    *pfVar1 = *pfVar1 + fVar9 * local_ac + fVar13 * local_c0; // update velocity
    *(float *)(thisPtr + 0x144) = *(float *)(thisPtr + 0x144) + fVar14 * local_ac + fStack_b4;
    *(float *)(thisPtr + 0x148) = *(float *)(thisPtr + 0x148) + fVar15 * local_ac + local_b0;
    fVar6 = (float10)FUN_006ca5e0(pfVar2, pfVar1, local_1c); // checkCollision
    local_bc = (float)fVar6;
    if (fVar6 < (float10)1) { // collision detected
        local_8c = *(longlong *)pfVar2; // save position
        local_84 = *(float *)(thisPtr + 0x13c); // save z
        fVar11 = 0.0;
        fVar8 = DAT_00e44564 - *(float *)(thisPtr + 0x164); // brake force
        *(float *)(thisPtr + 0x164) = fVar8;
        if (fVar8 < 0.0) {
            fVar11 = (*(float *)(thisPtr + 300) * fStack_9c + local_a0 * *(float *)(thisPtr + 0x128) +
                     *(float *)(thisPtr + 0x130) * fStack_98) * DAT_00e44750; // brake force
        }
        local_b8 = *pfVar1 + (*(float *)(thisPtr + 0x128) * fVar11 + local_a0) * local_c4; // new position x
        fStack_b4 = *(float *)(thisPtr + 0x144) +
                    (*(float *)(thisPtr + 300) * fVar11 + fStack_9c) * local_c4; // new position y
        local_b0 = *(float *)(thisPtr + 0x148) +
                   (*(float *)(thisPtr + 0x130) * fVar11 + fStack_98) * local_c4; // new position z
        *(ulonglong *)pfVar2 = CONCAT44(fStack_b4, local_b8); // update position
        *(float *)(thisPtr + 0x13c) = local_b0;
        fVar6 = (float10)FUN_006ca5e0(&local_b8, pfVar1, local_1c); // checkCollision again
        local_c0 = (float)fVar6;
        if (fVar6 < (float10)1) { // still colliding
            fVar11 = local_8c._4_4_ - *(float *)(thisPtr + 0x144); // delta y
            fVar13 = local_84 - *(float *)(thisPtr + 0x148); // delta z
            fVar8 = (float)local_8c - *pfVar1; // delta x
            fVar14 = fStack_b4 - *(float *)(thisPtr + 0x144); // delta y2
            fVar15 = local_b0 - *(float *)(thisPtr + 0x148); // delta z2
            fVar9 = local_b8 - *pfVar1; // delta x2
            local_c4 = SQRT(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8) * local_bc; // distance1
            fVar10 = SQRT(fVar15 * fVar15 + fVar14 * fVar14 + fVar9 * fVar9) * local_c0; // distance2
            if (local_c4 <= fVar10) {
                fVar8 = fVar9 * local_c0;
                fVar11 = fVar14 * local_c0;
                fVar13 = fVar15 * local_c0;
            }
            else {
                fVar8 = fVar8 * local_bc;
                fVar11 = fVar11 * local_bc;
                fVar13 = fVar13 * local_bc;
            }
            *pfVar2 = fVar8 + *pfVar1; // final position x
            *(float *)(thisPtr + 0x138) = *(float *)(thisPtr + 0x144) + fVar11; // final position y
            *(float *)(thisPtr + 0x13c) = *(float *)(thisPtr + 0x148) + fVar13; // final position z
            if (((fVar10 < _DAT_00d5c968) && (local_c4 < _DAT_00d5c968)) ||
               ((fVar10 < DAT_00e445ac &&
                ((local_c4 < DAT_00e445ac && ((*(uint *)(thisPtr + 0xdc) >> 5 & 1) != 0)))))) {
                *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) & 0xfffffc9f; // clear bits
                *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) | 0x80080; // set collision bits
                if ((*(uint *)(thisPtr + 0xdc) >> 1 & 1) == 0) {
                    if ((*(uint *)(thisPtr + 0xdc) >> 2 & 1) != 0) {
                        *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) & 0xfffffffb;
                        *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) | 2;
                    }
                }
                else {
                    *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) & 0xfffffffd;
                    *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) | 4;
                }
                if (DAT_0112a828 == 0) {
                    DAT_0112a828 = 1;
                    FUN_006cd8a0(thisPtr + 0xe0, thisPtr + 0xec, thisPtr + 0xf8, thisPtr + 0x104, thisPtr + 0x110,
                                 thisPtr + 0x11c, thisPtr + 0x128, thisPtr + 0x164); // resolveCollision
                    FUN_006cc3f0(); // playCollisionSound
                    FUN_00473bb0(*(float *)(thisPtr + 0xd8) * DAT_00e445c8); // applyDamage
                    *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) & 0xfff7ffff;
                    *(uint *)(thisPtr + 0xdc) = *(uint *)(thisPtr + 0xdc) | 0x800;
                    FUN_006cdb20(dt); // recursive call with dt
                    DAT_0112a828 = 0;
                }
            }
        }
    }
    return (float10)local_c8; // return friction force
}
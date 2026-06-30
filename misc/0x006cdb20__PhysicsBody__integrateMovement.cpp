// FUNC_NAME: PhysicsBody::integrateMovement
float __thiscall PhysicsBody::integrateMovement(void* thisPtr, float deltaTime)
{
    float* pfVar1;
    float* pfVar2;
    uint uVar3;
    char cVar4;
    int iVar5;
    float fVar6;
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
    undefined1 local_80[4];
    undefined1 local_7c[4];
    undefined1 local_78[4];
    float local_74;
    undefined1 local_6c[4];
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
    undefined1 local_1c[24];
    
    // init locals
    fStack_54 = 0.0f;
    fStack_44 = 0.0f;
    fStack_34 = 0.0f;
    fStack_24 = DAT_00d5780c; // identity quaternion? or 1.0
    
    // Get global physics manager (singleton)
    iVar5 = FUN_004262f0(0); // likely PhysicsManager::getInstance()
    
    // +0x50: some speed factor (probably vehicle speed limit)
    local_a4 = *(float*)(thisPtr + 0x50);
    // +0x150 from manager: global speed multiplier?
    local_bc = *(float*)(iVar5 + 0x150) * local_a4;
    
    // Setup a 3x3 rotation matrix (probably local->world rotation)
    // local_60..fStack_34 form a matrix
    local_60 = DAT_00d5780c;
    fStack_5c = 0.0f;
    fStack_58 = 0.0f;
    fStack_54 = 0.0f;
    local_50 = 0.0f;
    fStack_4c = DAT_00d5780c;
    fStack_48 = 0.0f;
    fStack_44 = 0.0f;
    local_40 = 0.0f;
    fStack_3c = 0.0f;
    fStack_38 = DAT_00d5780c;
    fStack_34 = 0.0f;
    local_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    fStack_24 = DAT_00d5780c;
    
    // +0x110, +0x114, +0x118: orientation (forward/up/right?)
    local_b8 = *(float*)(thisPtr + 0x110);
    fStack_b4 = *(float*)(thisPtr + 0x114);
    local_b0 = *(float*)(thisPtr + 0x118);
    
    fVar8 = DAT_00e44594; // default acceleration?
    
    // Check state flags at +0xdc for movement state
    if ((*(byte*)(thisPtr + 0xdc) & 1) == 0) {
        if ((*(uint*)(thisPtr + 0xdc) >> 1 & 1) == 0) {
            if (((*(uint*)(thisPtr + 0xdc) >> 2 & 1) != 0) &&
                // +0xd0: some timer/accumulator
                (local_c8 = DAT_00e44600 - (DAT_00d5f19c - *(float*)(thisPtr + 0xd0)),
                fVar8 = DAT_00d5f194,
                local_c8 <= DAT_00d5f194)) goto LAB_006cdc7b;
        }
        else {
            local_c8 = DAT_00d5f19c - *(float*)(thisPtr + 0xd0);
            fVar8 = DAT_00d5f198;
            if (DAT_00d5f198 <= local_c8) goto LAB_006cdc7b;
        }
    }
    local_c8 = fVar8;
    
LAB_006cdc7b:
    // Compute velocity difference from physical positions
    fVar13 = *(float*)(thisPtr + 0xf4) - *(float*)(thisPtr + 0xe8); // dz
    fVar11 = *(float*)(thisPtr + 0xf0) - *(float*)(thisPtr + 0xe4); // dy
    fVar8 = *(float*)(thisPtr + 0xec) - *(float*)(thisPtr + 0xe0);  // dx
    local_c0 = sqrtf(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8); // speed magnitude
    
    // if speed is very small, blend acceleration
    if (local_c0 < DAT_00e4475c) {
        local_c8 = (DAT_00d5780c - local_c0 * DAT_00d5f190) * DAT_00e44594 +
                   local_c0 * DAT_00d5f190 * local_c8;
    }
    
    // Build orientation matrix from +0x11c (another orientation) and local_c8 (desired speed)
    FUN_0046cf70(&local_60, thisPtr + 0x11c, local_c8, 0);
    
    // Copy target orientation from +0xf8 to +0x140
    *(undefined8*)(thisPtr + 0x140) = *(undefined8*)(thisPtr + 0xf8);
    
    // Transform local direction to world space using matrix
    local_a0 = fStack_b4 * local_50 + local_b8 * local_60 + local_b0 * local_40;
    fStack_9c = fStack_b4 * fStack_4c + local_b8 * fStack_5c + local_b0 * fStack_3c;
    fStack_98 = fStack_b4 * fStack_48 + local_b8 * fStack_58 + local_b0 * fStack_38;
    fStack_94 = fStack_b4 * fStack_44 + local_b8 * fStack_54 + local_b0 * fStack_34;
    
    // Copy another orientation
    *(undefined4*)(thisPtr + 0x148) = *(undefined4*)(thisPtr + 0x100);
    
    // Compute angular difference?
    fVar13 = *(float*)(thisPtr + 0x100) - *(float*)(thisPtr + 0x10c);
    fVar8 = *(float*)(thisPtr + 0xf8) - *(float*)(thisPtr + 0x104);
    pfVar1 = (float*)(thisPtr + 0x140);
    fVar11 = *(float*)(thisPtr + 0xfc) - *(float*)(thisPtr + 0x108);
    local_c4 = sqrtf(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8);
    
    // Access global pointer for physics settings (e.g., DAT_012233a0)
    if (**(int**)(DAT_012233a0 + 4) == 0) {
        local_ac = 0.0f;
    }
    else {
        local_ac = (float)(**(int**)(DAT_012233a0 + 4) + -0x1f30); // offset 0x1f30
    }
    
    fVar8 = local_ac; // cast to float
    // Compute smoothed acceleration for linear movement
    fVar6 = (float10)FUN_006cc570(local_c0, local_c8, local_bc * DAT_00e44748, DAT_00d5f0e4);
    local_c0 = (float)fVar6;
    
    // Check some condition (maybe button pressed?)
    cVar4 = FUN_007f7c50();
    uVar3 = DAT_00d5f0dc;
    if (cVar4 != '\0') {
        uVar3 = DAT_00d5f0e0;
    }
    // Compute smoothed acceleration for angular movement
    fVar6 = (float10)FUN_006cc570(local_c4, DAT_00e44594, local_a4 * DAT_00e44748, uVar3);
    
    fVar11 = DAT_00d5833c;
    fVar13 = DAT_00d5f18c;
    if (local_c0 < (float)fVar6) {
        fVar11 = DAT_00d5f18c;
        fVar13 = DAT_00d5833c;
    }
    
    // get friction/multiplier from physics settings +0x2c64
    local_c4 = *(float*)((int)fVar8 + 0x2c64) * ((float)fVar6 * fVar13 + local_c0 * fVar11);
    
    // compute braking force if speed > 0
    fVar11 = 0.0f;
    fVar8 = fVar11;
    if (*(float*)(thisPtr + 0x164) <= 0.0f && *(float*)(thisPtr + 0x164) != 0.0f) {
        // +0x300? offset 0x12c from 0x300? actually 300 decimal = 0x12c, likely +0x128 +4
        fVar8 = (*(float*)(thisPtr + 300) * fStack_9c + *(float*)(thisPtr + 0x128) * local_a0 +
                *(float*)(thisPtr + 0x130) * fStack_98) * DAT_00e44750;
    }
    
    pfVar2 = (float*)(thisPtr + 0x134); // position pointer
    // Update position with velocity and acceleration
    *pfVar2 = *pfVar1 + (fVar8 * *(float*)(thisPtr + 0x128) + local_a0) * local_c4;
    fVar13 = DAT_00d5c458; // timestep maybe?
    *(float*)(thisPtr + 0x138) = *(float*)(thisPtr + 0x144) + (*(float*)(thisPtr + 300) * fVar8 + fStack_9c) * local_c4;
    *(float*)(thisPtr + 0x13c) = *(float*)(thisPtr + 0x148) + (*(float*)(thisPtr + 0x130) * fVar8 + fStack_98) * local_c4;
    
    // Compute damping and collision response
    local_c8 = 0.0f;
    local_c0 = 0.0f;
    local_b8 = 0.0f;
    local_8c = (ulonglong)(uint)local_8c._4_4_ << 0x20;
    local_74 = 0.0f;
    local_68 = 0.0f;
    
    if ((*(uint*)(thisPtr + 0xdc) >> 0xb & 1) == 0) {
        // Compute velocity components from position differences (euler)
        FUN_006cd540(&local_b8, &local_c8, &local_a8, thisPtr + 0xe0);
        FUN_006cd540(&local_8c, &local_c0, &local_a8, thisPtr + 0xec);
        local_a8 = ((float)local_8c + local_b8) * DAT_00d5c458;
        FUN_006cd540(local_78, local_7c, local_80, thisPtr + 0xf8);
        FUN_006cd540(local_6c, local_80, local_7c, thisPtr + 0x104);
        fVar11 = (local_68 + local_74) * DAT_00d5c458;
        fVar13 = DAT_00d5c458;
    }
    else {
        local_a8 = 0.0f;
        local_c8 = fVar11;
    }
    
    // Compute maximum velocity magnitude
    fVar9 = 0.0f;
    fVar8 = (float)((uint)local_a8 & DAT_00e44680);
    if ((float)((uint)local_a8 & DAT_00e44680) <= (float)((uint)fVar11 & DAT_00e44680)) {
        fVar8 = (float)((uint)fVar11 & DAT_00e44680);
    }
    
    // Limit speed based on current speed sign
    if (0.0f < *(float*)(thisPtr + 0x164) || *(float*)(thisPtr + 0x164) == 0.0f) {
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
    local_c8 = fVar8 * DAT_00d5f0d8;
    if (fVar13 < fVar8 * DAT_00d5f0d8) {
        local_c8 = fVar13;
    }
    
    // Apply forces and compute final velocity
    dVar7 = (double)(local_bc * fVar13);
    FUN_00b9c041();
    local_c0 = (float)dVar7 * local_c4 * DAT_00d5eee4 * local_a8;
    dVar7 = (double)(local_a4 * DAT_00d5c458);
    local_bc = local_c0;
    FUN_00b9c041();
    
    // Get some global friction value
    if ((DAT_0112a830 & 1) == 0) {
        DAT_0112a82c = *(float*)((int)local_ac + 0x2c6c);
        DAT_0112a830 |= 1;
    }
    local_ac = (float)dVar7 * local_c4 * DAT_00d5eee4 * (*(float*)((int)local_ac + 0x2c68) + *(float*)(thisPtr + 0xd4)) * DAT_00d5ccf8;
    
    // Apply external forces (e.g., from gravity or steering)
    iVar5 = FUN_004262f0(0);
    fVar8 = *(float*)(iVar5 + 0x44); // gravity component?
    fVar11 = *(float*)(iVar5 + 0x48);
    fVar13 = *(float*)(iVar5 + 0x40);
    fStack_b4 = fVar8 * local_c0;
    local_b0 = fVar11 * local_c0;
    fVar10 = *(float*)(iVar5 + 0x54) * DAT_0112a82c;
    fVar12 = *(float*)(iVar5 + 0x58) * DAT_0112a82c;
    fVar9 = *(float*)(iVar5 + 0x50);
    fVar14 = *(float*)(iVar5 + 0x54);
    fVar15 = *(float*)(iVar5 + 0x58);
    
    // Update position with external forces
    *pfVar2 += fVar9 * DAT_0112a82c + fVar13 * local_bc;
    *(float*)(thisPtr + 0x138) += fVar10 + fVar8 * local_bc;
    *(float*)(thisPtr + 0x13c) += fVar12 + fVar11 * local_bc;
    *pfVar1 += fVar9 * local_ac + fVar13 * local_c0;
    *(float*)(thisPtr + 0x144) += fVar14 * local_ac + fStack_b4;
    *(float*)(thisPtr + 0x148) += fVar15 * local_ac + local_b0;
    
    // Call constraint solver
    fVar6 = (float10)FUN_006ca5e0(pfVar2, pfVar1, local_1c);
    local_bc = (float)fVar6;
    
    if (fVar6 < (float10)1.0f) {
        // Constraint not satisfied, apply correction
        local_8c = *(longlong*)pfVar2;
        local_84 = *(float*)(thisPtr + 0x13c);
        fVar11 = 0.0f;
        fVar8 = DAT_00e44564 - *(float*)(thisPtr + 0x164);
        *(float*)(thisPtr + 0x164) = fVar8;
        if (fVar8 < 0.0f) {
            fVar11 = (*(float*)(thisPtr + 300) * fStack_9c + local_a0 * *(float*)(thisPtr + 0x128) +
                     *(float*)(thisPtr + 0x130) * fStack_98) * DAT_00e44750;
        }
        // Secondary push
        local_b8 = *pfVar1 + (*(float*)(thisPtr + 0x128) * fVar11 + local_a0) * local_c4;
        fStack_b4 = *(float*)(thisPtr + 0x144) + (*(float*)(thisPtr + 300) * fVar11 + fStack_9c) * local_c4;
        local_b0 = *(float*)(thisPtr + 0x148) + (*(float*)(thisPtr + 0x130) * fVar11 + fStack_98) * local_c4;
        *(ulonglong*)pfVar2 = CONCAT44(fStack_b4, local_b8);
        *(float*)(thisPtr + 0x13c) = local_b0;
        
        fVar6 = (float10)FUN_006ca5e0(&local_b8, pfVar1, local_1c);
        local_c0 = (float)fVar6;
        if (fVar6 < (float10)1.0f) {
            // Blend between two collision responses
            fVar11 = local_8c._4_4_ - *(float*)(thisPtr + 0x144);
            fVar13 = local_84 - *(float*)(thisPtr + 0x148);
            fVar8 = (float)local_8c - *pfVar1;
            fVar14 = fStack_b4 - *(float*)(thisPtr + 0x144);
            fVar15 = local_b0 - *(float*)(thisPtr + 0x148);
            fVar9 = local_b8 - *pfVar1;
            local_c4 = sqrtf(fVar13 * fVar13 + fVar11 * fVar11 + fVar8 * fVar8) * local_bc;
            fVar10 = sqrtf(fVar15 * fVar15 + fVar14 * fVar14 + fVar9 * fVar9) * local_c0;
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
            // Apply blended position
            *pfVar2 = fVar8 + *pfVar1;
            *(float*)(thisPtr + 0x138) = *(float*)(thisPtr + 0x144) + fVar11;
            *(float*)(thisPtr + 0x13c) = *(float*)(thisPtr + 0x148) + fVar13;
            
            // Check if constrained sufficiently to stop iterative refinement
            if (((fVar10 < DAT_00d5c968) && (local_c4 < DAT_00d5c968)) ||
               ((fVar10 < DAT_00e445ac &&
                ((local_c4 < DAT_00e445ac && ((*(uint*)(thisPtr + 0xdc) >> 5 & 1) != 0)))))) {
                // Clear and set bits, then recurse once more
                *(uint*)(thisPtr + 0xdc) = *(uint*)(thisPtr + 0xdc) & 0xfffffc9f;
                *(uint*)(thisPtr + 0xdc) |= 0x80080;
                if ((*(uint*)(thisPtr + 0xdc) >> 1 & 1) == 0) {
                    if ((*(uint*)(thisPtr + 0xdc) >> 2 & 1) != 0) {
                        *(uint*)(thisPtr + 0xdc) &= 0xfffffffb;
                        *(uint*)(thisPtr + 0xdc) |= 2;
                    }
                }
                else {
                    *(uint*)(thisPtr + 0xdc) &= 0xfffffffd;
                    *(uint*)(thisPtr + 0xdc) |= 4;
                }
                if (DAT_0112a828 == 0) {
                    DAT_0112a828 = 1;
                    // Initialize collision response points
                    FUN_006cd8a0(thisPtr + 0xe0, thisPtr + 0xec, thisPtr + 0xf8, thisPtr + 0x104, thisPtr + 0x110,
                                 thisPtr + 0x11c, thisPtr + 0x128, thisPtr + 0x164);
                    FUN_006cc3f0();
                    FUN_00473bb0(*(float*)(thisPtr + 0xd8) * DAT_00e445c8);
                    // Update flags
                    *(uint*)(thisPtr + 0xdc) &= 0xfff7ffff;
                    *(uint*)(thisPtr + 0xdc) |= 0x800;
                    // Recursive call
                    integrateMovement((void*)param_2, deltaTime);
                    DAT_0112a828 = 0;
                }
            }
        }
    }
    return (float10)local_c8;
}
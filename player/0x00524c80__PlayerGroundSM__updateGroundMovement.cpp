// FUNC_NAME: PlayerGroundSM::updateGroundMovement
void PlayerGroundSM::updateGroundMovement()
{
    float deltaTime;
    int state;
    int i;
    void *g_pGlobalArray;
    double doubleVal;
    float f0, f1, f2, f3, f4, f5, f6, f7, f8, f9;
    float minVal, maxVal, midVal;
    undefined4 uVar8;
    float local_160, local_15c, local_14c;
    undefined **local_148;
    float local_144;
    int local_140;
    undefined4 local_13c, local_138;
    float local_134, local_130;
    float *local_12c, *local_128;
    undefined1 *local_124, *local_120;
    undefined2 local_11c;
    int local_118;
    undefined4 local_114;
    float local_110, fStack_10c, fStack_108;
    undefined4 uStack_104;
    float local_100, fStack_fc, fStack_f8, fStack_f4;
    float local_f0, fStack_ec, fStack_e8;
    undefined4 uStack_e4;
    undefined1 local_e0[12];
    undefined4 local_d4;
    float local_d0, fStack_cc;
    undefined4 uStack_c8, uStack_c4;
    float local_c0, fStack_bc;
    undefined4 uStack_b8, uStack_b4;
    undefined4 local_b0, uStack_ac, uStack_a8, uStack_a4;
    float local_a0, fStack_9c;
    undefined4 uStack_98, uStack_94;
    undefined1 local_90[64];
    undefined1 local_50[76];

    // Check if CCT variables pointer and state are valid
    if (((*(int*)(this + 0x120) != 0) && 
         (*(int*)(this + 0x124) != 0)) && 
        (*(int*)(this + 0x124) != 4)) // Exclude state 4
    {
        float fVar1 = *(float*)(*(int*)(this + 0x120) + 0xa4); // Some constant from CCT variables
        float speedFactor = *(float*)(this + 0x1c) * DAT_00e2cd54; // Time delta * global speed factor?

        // Two calls to something (maybe clearing or stacking)
        FUN_00414aa0();
        uVar8 = 0;
        fStack_f4 = 0.0f;
        FUN_00414aa0();

        fStack_cc = *(float*)(this + 0x3c); // Y-component of velocity?
        local_15c = *(float*)(this + 0x38) * speedFactor; // X-component of velocity scaled
        speedFactor = fStack_cc * speedFactor;
        
        // Compute four candidate values using global constants DAT_00e44564 (maybe 1.0?)
        float v1 = (DAT_00e44564 - local_15c) + speedFactor;
        float v2 = (DAT_00e44564 - local_15c) + (DAT_00e44564 - speedFactor);
        float v3 = local_15c + speedFactor;
        float v4 = local_15c + (DAT_00e44564 - speedFactor); // Note: this is local_15c after reassignment? Actually it's computed then assigned to local_15c?
        
        local_15c = v4;
        local_14c = local_15c;
        if (local_15c < v3) {
            local_14c = v3;
        }
        if (local_14c < v1) {
            local_14c = v1;
        }
        if (local_14c < v2) {
            local_14c = v2;
        }
        
        float f5 = local_15c;
        if (v2 < local_15c) {
            f5 = v2;
        }
        if (v3 <= f5) {
            f5 = v3;
        }
        local_160 = v1;
        if (f5 < v1) {
            local_160 = f5;
        }
        if (local_15c <= v2) {
            local_15c = v2;
        }
        if (local_15c < v3) {
            local_15c = v3;
        }
        if (local_15c < v1) {
            local_15c = v1;
        }
        
        // Initialize some structures with zero and global constant DAT_00e2b1a4
        uStack_c8 = 0;
        uStack_c4 = 0;
        uStack_b8 = 0;
        uStack_b4 = 0;
        local_b0 = 0;
        uStack_ac = 0;
        uStack_a8 = DAT_00e2b1a4;
        uStack_a4 = 0;
        uStack_98 = 0;
        uStack_94 = DAT_00e2b1a4;
        
        local_d0 = *(float*)(this + 0x38) * DAT_00e2cd54;
        local_a0 = DAT_00e2cd54;
        fStack_9c = DAT_00e2cd54;
        local_c0 = fStack_cc * DAT_00e44718;
        fStack_cc = fStack_cc * DAT_00e2cd54;
        
        float f = DAT_00e44564 - fVar1;
        // First set: interpolated position from current position + velocity * (1-fVar1)
        local_110 = f * local_100 + *(float*)(this + 0x80);
        fStack_10c = f * fStack_fc + *(float*)(this + 0x84);
        fStack_108 = f * fStack_f8 + *(float*)(this + 0x88);
        
        // Second set: extrapolated position using fVar1 * DAT_00e445ac
        f = fVar1 * DAT_00e445ac;
        local_f0 = local_100;
        fStack_ec = fStack_fc;
        fStack_e8 = fStack_f8;
        local_100 = f * local_100 + *(float*)(this + 0x80);
        fStack_fc = f * fStack_fc + *(float*)(this + 0x84);
        fStack_f8 = f * fStack_f8 + *(float*)(this + 0x88);
        fStack_f4 = f * fStack_f4 + *(float*)(this + 0x8c); // Also update the fourth component (maybe w or height?)
        uStack_e4 = 0;
        uStack_104 = 0;
        local_d4 = uVar8;
        fStack_bc = local_d0;
        
        // Call transform/pose computation
        FUN_006138b0(&local_110, &local_100, local_e0, local_90);
        
        // Call a clamping function
        FUN_006145f0(local_14c, local_160, local_15c, DAT_00e2e780);
        
        // Get global pointer
        i = DAT_012234d0;
        float fVar5 = fVar1 * DAT_00e2d99c;
        int iVar3 = DAT_012234d0 + 0x43080; // Some array offset
        
        // Set transform for physics?
        FUN_0066e3f0(iVar3, &local_110, &local_f0, fVar5);
        
        doubleVal = (double)*(float*)(*(int*)(this + 0x120) + 0xa0);
        FUN_00b99e20();
        
        // Setup stack structure for callback
        local_12c = &local_110;
        local_128 = &local_f0;
        local_124 = local_90;
        local_120 = local_50;
        local_11c = *(undefined2*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x10); // TLS or exception handling?
        local_134 = (float)doubleVal;
        local_148 = &PTR_LAB_00e3839c;
        local_140 = -1;
        local_13c = 0xFFFFFFFF;
        local_138 = 0;
        local_114 = 0;
        local_144 = fVar5;
        local_130 = fVar1;
        local_118 = iVar3;
        
        // Call some registration function
        FUN_0049f960(FUN_0049ead0, &local_148);
        
        if (local_140 != -1) {
            *(undefined4*)(i + 0x43098) = 0; // Clear something in global array
            uVar8 = FUN_0066ea80(iVar3, local_144, local_134, &local_d0);
            *(undefined4*)(this + 0xd0) = uVar8; // Store handle
        }
        
        if (*(int*)(this + 0xd0) != 0) {
            int stateIndex;
            if (*(int*)(this + 0x124) == 0) {
                stateIndex = 0;
            } else {
                stateIndex = *(int*)(this + 0x124) - 4;
            }
            *(undefined1**)(stateIndex + 0xa8) = &LAB_0051f860; // Set function pointer in state data
            FUN_0049f960(&LAB_00524c50, *(undefined4*)(this + 0xd0));
        }
    }
    return;
}
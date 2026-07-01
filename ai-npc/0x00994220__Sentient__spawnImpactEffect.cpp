// FUNC_NAME: Sentient::spawnImpactEffect
void __thiscall Sentient::spawnImpactEffect(int thisPtr, char *effectName, undefined4 param_3, undefined4 param_4, undefined4 param_5,
                                           undefined4 param_6, undefined4 param_7, undefined4 param_8)
{
    float *pfVar1;
    undefined4 uVar2;
    long lVar3;
    int iVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    float local_114;
    float local_110;
    float local_10c;
    float local_108;
    int local_104;
    float local_100;
    float local_fc;
    float local_f8;
    float local_f4;
    undefined4 local_f0;
    undefined4 uStack_ec;
    undefined4 uStack_e8;
    undefined4 uStack_e4;
    undefined4 local_e0;
    undefined4 uStack_dc;
    undefined4 uStack_d8;
    undefined4 uStack_d4;
    undefined4 local_d0;
    undefined4 uStack_cc;
    undefined4 uStack_c8;
    undefined4 uStack_c4;
    float local_c0;
    float fStack_bc;
    float fStack_b8;
    undefined4 uStack_b4;
    float local_b0;
    float fStack_ac;
    float fStack_a8;
    float local_a0;
    undefined4 uStack_9c;
    undefined4 uStack_98;
    undefined4 uStack_94;
    undefined4 local_90;
    float fStack_8c;
    undefined4 uStack_88;
    undefined4 uStack_84;
    undefined4 local_80;
    undefined4 uStack_7c;
    float fStack_78;
    undefined4 uStack_74;
    undefined4 local_70;
    undefined4 uStack_6c;
    undefined4 uStack_68;
    undefined4 uStack_64;
    undefined4 local_60;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined4 uStack_54;
    undefined4 local_50;
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 local_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 local_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 local_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;
    
    local_104 = thisPtr;
    lVar3 = _atol(effectName); // Attempt to parse effectName as a long integer
    if (lVar3 < 0) {
        // Negative ID - use fallback from global data (+0x138)
        if (*(int *)(DAT_011304f8 + 0x138) == 0) {
            return;
        }
        iVar4 = *(int *)(DAT_011304f8 + 0x138) + -0x48;
    }
    else {
        // Non-negative - resolve via lookup at address
        iVar4 = FUN_00705ab0(lVar3); // Likely finds effect data by ID
    }
    
    if (iVar4 != 0) {
        // Set up matrix/transform state
        FUN_005c4bf0(); // Push transform
        FUN_005c5320(param_7, param_8); // Set some transformation parameters
        FUN_005c50c0(param_4, &local_114, &local_108, &local_10c, &local_110); // Decompose/transform
        
        // Compute scaling based on Sentient parameters (thisPtr+8, thisPtr+0xC)
        local_110 = local_110 - local_108;
        local_100 = ((local_114 + local_10c) - local_110) * *(float *)(thisPtr + 8) * _DAT_00d5c458;
        local_f8 = *(float *)(thisPtr + 8) * local_110;
        local_f4 = *(float *)(thisPtr + 0xc) * local_110;
        
        // Initialize many vectors with default W=0, and some with _DAT_00d5780c (likely identity/quaternion data)
        local_e0 = 0;
        uStack_dc = _DAT_00d5780c;
        uStack_d8 = 0;
        uStack_d4 = 0;
        local_d0 = 0;
        uStack_cc = 0;
        uStack_c8 = _DAT_00d5780c;
        uStack_c4 = 0;
        local_fc = *(float *)(thisPtr + 0xc) * local_108;
        local_60 = _DAT_00d5780c;
        uStack_5c = 0;
        uStack_58 = 0;
        uStack_54 = 0;
        local_f0 = _DAT_00d5780c;
        uStack_ec = 0;
        uStack_e8 = 0;
        uStack_e4 = 0;
        local_c0 = 0.0;
        fStack_bc = 0.0;
        fStack_b8 = 0.0;
        uStack_b4 = _DAT_00d5780c;
        
        // Get effect offset (position offset for spawn)
        if (lVar3 < 0) {
            // Use fallback path for negative IDs
            FUN_009937f0(iVar4, &local_b0); // Get offset from effect data
        }
        else {
            // Direct offset from thisPtr's member array: offset start = (effectID+1)*0x10
            pfVar1 = (float *)((lVar3 + 1) * 0x10 + thisPtr);
            local_b0 = *pfVar1;
            fStack_ac = pfVar1[1];
            fStack_a8 = pfVar1[2];
        }
        
        // Scale offset by factor
        local_c0 = DAT_00d5ccf8 * local_b0;
        fStack_bc = DAT_00d5ccf8 * fStack_ac;
        fStack_b8 = DAT_00d5ccf8 * fStack_a8;
        
        // Constant for something (maybe gravity?)
        local_a0 = DAT_00d5d7b8;
        fStack_8c = DAT_00d5d7b8;
        fStack_78 = DAT_00d5d7b8;
        
        // More vector copies/initializations
        uVar5 = local_60;
        uVar6 = uStack_5c;
        uVar7 = uStack_58;
        uVar8 = uStack_54;
        uStack_9c = uStack_5c;
        uStack_98 = uStack_58;
        uStack_94 = uStack_54;
        local_90 = uStack_54;
        uStack_88 = uStack_54;
        uStack_84 = uStack_54;
        local_80 = uStack_54;
        uStack_7c = uStack_54;
        uStack_74 = uStack_54;
        local_70 = uStack_54;
        uStack_6c = uStack_54;
        uStack_68 = uStack_54;
        uStack_64 = local_60;
        
        // Process effect data
        FUN_00993540(&local_f0); // Likely processes the effect
        
        uVar2 = DAT_00d5eff8;
        if ((((lVar3 != 5) && (lVar3 != 6)) && (lVar3 != 7)) && (lVar3 != 8)) {
            uVar2 = 0;
        }
        // Build parameter block for effect spawn
        local_50 = uVar5;
        uStack_4c = uVar6;
        uStack_48 = uVar7;
        uStack_44 = uVar8;
        local_40 = uVar8;
        uStack_3c = uVar5;
        uStack_38 = uVar8;
        uStack_34 = uVar8;
        local_30 = uVar8;
        uStack_2c = uVar8;
        uStack_28 = uVar5;
        uStack_24 = uVar8;
        local_20 = uVar8;
        uStack_1c = uVar8;
        uStack_18 = uVar8;
        uStack_14 = uVar5;
        
        // Spawn effect via rendering/effects system
        FUN_0056b8a0(DAT_00e446a0, uVar2, 0, &local_50); // Likely spawnEffect
        FUN_00993540(&local_f0); // Another processing step
        
        fStack_b8 = fStack_b8 + DAT_00d5d7b8; // Adjust Z offset
        
        // Finalize effect spawn on this Sentient
        FUN_00993d50(iVar4, local_104, &local_f0, &local_100);
        FUN_005c4ac0(); // Pop transform
    }
    return;
}
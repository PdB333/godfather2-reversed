// FUNC_NAME: AnimationBlend::blendPose
undefined4 AnimationBlend::blendPose(undefined4 param_1, float blendFactor, int poseA, int poseB)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float fVar4;
  float local_160;
  float fStack_15c;
  float fStack_158;
  float fStack_154;
  undefined4 local_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined **local_140 [19];
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int local_90;
  undefined4 local_8c;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
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
  float local_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  // Check if both poses have valid skeleton data (at +0xb0)
  if ((*(int *)(poseA + 0xb0) == 0) || (*(int *)(poseB + 0xb0) == 0)) {
    FUN_008208c0(); // likely clearBlend or reset
  }
  else {
    FUN_008208c0(); // reset blend state
    
    // Lerp translation channels (poseA +0x80 to +0x9c)
    local_c0 = (*(float *)(poseB + 0x80) - *(float *)(poseA + 0x80)) * blendFactor +
               *(float *)(poseA + 0x80);
    fStack_bc = (*(float *)(poseB + 0x84) - *(float *)(poseA + 0x84)) * blendFactor +
                *(float *)(poseA + 0x84);
    fStack_b8 = (*(float *)(poseB + 0x88) - *(float *)(poseA + 0x88)) * blendFactor +
                *(float *)(poseA + 0x88);
    fStack_b4 = (*(float *)(poseB + 0x8c) - *(float *)(poseA + 0x8c)) * blendFactor +
                *(float *)(poseA + 0x8c);
    local_b0 = (*(float *)(poseB + 0x90) - *(float *)(poseA + 0x90)) * blendFactor +
               *(float *)(poseA + 0x90);
    fStack_ac = (*(float *)(poseB + 0x94) - *(float *)(poseA + 0x94)) * blendFactor +
                *(float *)(poseA + 0x94);
    fStack_a8 = (*(float *)(poseB + 0x98) - *(float *)(poseA + 0x98)) * blendFactor +
                *(float *)(poseA + 0x98);
    fStack_a4 = (*(float *)(poseB + 0x9c) - *(float *)(poseA + 0x9c)) * blendFactor +
                *(float *)(poseA + 0x9c);
    
    // Lerp rotation quaternion channels (poseA +0x4c to +0x70)
    local_f4 = (*(float *)(poseB + 0x4c) - *(float *)(poseA + 0x4c)) * blendFactor +
               *(float *)(poseA + 0x4c);
    local_f0 = (*(float *)(poseB + 0x50) - *(float *)(poseA + 0x50)) * blendFactor +
               *(float *)(poseA + 0x50);
    local_ec = (*(float *)(poseB + 0x54) - *(float *)(poseA + 0x54)) * blendFactor +
               *(float *)(poseA + 0x54);
    local_e8 = (*(float *)(poseB + 0x58) - *(float *)(poseA + 0x58)) * blendFactor +
               *(float *)(poseA + 0x58);
    local_e4 = (*(float *)(poseB + 0x5c) - *(float *)(poseA + 0x5c)) * blendFactor +
               *(float *)(poseA + 0x5c);
    local_e0 = (*(float *)(poseB + 0x60) - *(float *)(poseA + 0x60)) * blendFactor +
               *(float *)(poseA + 0x60);
    local_dc = (*(float *)(poseB + 100) - *(float *)(poseA + 100)) * blendFactor +
               *(float *)(poseA + 100);
    local_d8 = (*(float *)(poseB + 0x68) - *(float *)(poseA + 0x68)) * blendFactor +
               *(float *)(poseA + 0x68);
    local_d4 = (*(float *)(poseB + 0x6c) - *(float *)(poseA + 0x6c)) * blendFactor +
               *(float *)(poseA + 0x6c);
    local_d0 = (*(float *)(poseB + 0x70) - *(float *)(poseA + 0x70)) * blendFactor +
               *(float *)(poseA + 0x70);
    
    // Handle skeleton reference counting (at +0xb0)
    if ((&local_90 != (int *)(poseA + 0xb0)) &&
       (iVar1 = *(int *)(poseA + 0xb0), local_90 != iVar1)) {
      if (local_90 != 0) {
        FUN_004daf90(&local_90); // release skeleton reference
      }
      local_90 = iVar1;
      if (iVar1 != 0) {
        local_8c = *(undefined4 *)(iVar1 + 4);
        *(int **)(iVar1 + 4) = &local_90;
      }
    }
    
    // Get quaternion from lerped rotation
    uVar2 = FUN_004aaa50(&local_160); // quaternionFromEuler or similar
    FUN_0056dbe0(uVar2); // normalizeQuaternion
    
    // Blend scale/shear components (at +0x100)
    FUN_0056db60(blendFactor, poseA + 0x100, poseB + 0x100, &local_40);
    
    // Normalize quaternion if needed
    fVar4 = fStack_3c * fStack_3c + fStack_38 * fStack_38 + fStack_34 * fStack_34 +
            local_40 * local_40;
    if (DAT_00e44768 < (double)(float)((uint)(fVar4 - _DAT_00d5780c) & DAT_00e44680)) {
      fVar4 = _DAT_00d5780c / SQRT(fVar4);
      local_40 = fVar4 * local_40;
      fStack_3c = fVar4 * fStack_3c;
      fStack_38 = fVar4 * fStack_38;
      fStack_34 = fVar4 * fStack_34;
    }
    
    // Check if blended rotation needs spherical interpolation
    fVar4 = fStack_15c * fStack_3c + fStack_158 * fStack_38 + fStack_154 * fStack_34 +
            local_40 * local_160;
    if (fVar4 < 0.0) {
      fVar4 = DAT_00e44564 - fVar4;
    }
    
    if (_DAT_00d5780c - fVar4 <= local_d0) {
      // Use lerp (close enough)
      puVar3 = (undefined4 *)FUN_004aaa50(); // getIdentityQuaternion
      local_80 = *puVar3;
      uStack_7c = puVar3[1];
      uStack_78 = puVar3[2];
      uStack_74 = puVar3[3];
      local_70 = puVar3[4];
      uStack_6c = puVar3[5];
      uStack_68 = puVar3[6];
      uStack_64 = puVar3[7];
      local_60 = puVar3[8];
      uStack_5c = puVar3[9];
      uStack_58 = puVar3[10];
      uStack_54 = puVar3[0xb];
      local_50 = puVar3[0xc];
      uStack_4c = puVar3[0xd];
      uStack_48 = puVar3[0xe];
      uStack_44 = puVar3[0xf];
      local_30 = local_150;
      uStack_2c = uStack_14c;
      uStack_28 = uStack_148;
      uStack_24 = uStack_144;
      
      // Normalize the lerped quaternion
      fVar4 = fStack_15c * fStack_15c + fStack_158 * fStack_158 + fStack_154 * fStack_154 +
              local_160 * local_160;
      local_40 = local_160;
      fStack_3c = fStack_15c;
      fStack_38 = fStack_158;
      fStack_34 = fStack_154;
      if (DAT_00e44768 < (double)(float)((uint)(fVar4 - _DAT_00d5780c) & DAT_00e44680)) {
        fStack_34 = _DAT_00d5780c / SQRT(fVar4);
        local_40 = fStack_34 * local_160;
        fStack_3c = fStack_34 * fStack_15c;
        fStack_38 = fStack_34 * fStack_158;
        fStack_34 = fStack_34 * fStack_154;
      }
    }
    else {
      // Use spherical interpolation (slerp)
      FUN_0056dc20(&local_40, &local_80);
    }
    
    // Set up vtable for result
    FUN_00820d40(local_140);
    local_140[0] = &PTR_FUN_00d73398;
    
    if (local_90 != 0) {
      FUN_004daf90(&local_90); // release skeleton reference
      return param_1;
    }
  }
  return param_1;
}
// FUNC_NAME: AnimationBlendTree::blendTwoAnimations
undefined4 * __thiscall AnimationBlendTree::blendTwoAnimations(int this, undefined4 *outResult, undefined4 *timeData, uint *outBlendInfo)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  float fVar11;
  undefined **local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uVar7 = findAnimationIndex(timeData); // FUN_0082c2c0
  if (uVar7 == 0xffffffff) {
    if (outBlendInfo != (uint *)0x0) {
      *outBlendInfo = 0xffffffff;
      outBlendInfo[1] = 0xffffffff;
      outBlendInfo[2] = 0;
    }
    getDefaultBlend(); // FUN_008334a0
    local_34 = _DAT_00d5780c; // some global float constant
    local_30 = _DAT_00d5780c;
    local_2c = 0;
    local_80 = &PTR_LAB_00d736c0; // default blend data
    local_20 = _DAT_00d735f0;
    uStack_1c = _UNK_00d735f4;
    uStack_18 = _UNK_00d735f8;
    uStack_14 = _UNK_00d735fc;
    copyBlendData(&local_80); // FUN_0081f9f0
    outResult[0x13] = local_34;
    outResult[0x14] = local_30;
    outResult[0x15] = local_2c;
    *outResult = &PTR_LAB_00d736c0;
    outResult[0x18] = local_20;
    outResult[0x19] = uStack_1c;
    outResult[0x1a] = uStack_18;
    outResult[0x1b] = uStack_14;
    return outResult;
  }
  *(uint *)(this + 4) = uVar7; // store current animation index
  fVar5 = _DAT_00d5780c;
  if (uVar7 < *(int *)(this + 0xc) - 1U) {
    uVar9 = uVar7 + 1;
  }
  else {
    uVar9 = 0;
  }
  iVar3 = *(int *)(*(int *)(this + 8) + uVar7 * 4); // animation data at index
  iVar4 = *(int *)(*(int *)(this + 8) + uVar9 * 4); // next animation data
  uVar1 = *(int *)(iVar3 + 0x18) + (*(int *)(iVar3 + 0x14) + *(int *)(iVar3 + 0x10) * 0x3c) * 0x3c; // total frames in current animation
  if (uVar9 == 0) {
    uVar2 = timeData[5] + (timeData[4] + timeData[3] * 0x3c) * 0x3c; // time in seconds
    iVar8 = *(int *)(iVar4 + 0x18) + (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c
            + (0x15180 - uVar1); // wrap around day boundary
    if (uVar2 < uVar1) {
      iVar10 = uVar2 + (0x15180 - uVar1);
    }
    else {
      iVar10 = uVar2 - uVar1;
    }
  }
  else {
    iVar10 = ((timeData[4] + timeData[3] * 0x3c) * 0x3c - uVar1) + timeData[5]; // time difference
    iVar8 = (*(int *)(iVar4 + 0x18) +
            (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c) - uVar1; // frame difference
  }
  if (iVar8 == 0) {
    if (outBlendInfo != (uint *)0x0) {
      *outBlendInfo = uVar7;
      outBlendInfo[1] = uVar9;
      outBlendInfo[2] = (uint)fVar5;
    }
    applyAnimation(iVar4); // FUN_0082abf0
  }
  else {
    fVar5 = (float)iVar10;
    if (iVar10 < 0) {
      fVar5 = fVar5 + DAT_00e44578; // handle negative float
    }
    fVar6 = (float)iVar8;
    if (iVar8 < 0) {
      fVar6 = fVar6 + DAT_00e44578;
    }
    if (outBlendInfo != (uint *)0x0) {
      fVar11 = _DAT_00d5780c - fVar5 / fVar6;
      *outBlendInfo = uVar7;
      outBlendInfo[1] = uVar9;
      outBlendInfo[2] = (uint)fVar11;
    }
    blendAnimations(&local_80, fVar5 / fVar6, iVar3, iVar4); // FUN_0082c370
  }
  if (&local_7c != timeData) {
    local_7c = *timeData;
    local_74 = timeData[2];
    local_78 = timeData[1];
    local_70 = timeData[3];
    local_68 = timeData[5];
    local_6c = timeData[4];
  }
  applyAnimation(&local_80); // FUN_0082abf0
  return outResult;
}
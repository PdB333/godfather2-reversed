// FUNC_NAME: DateTimeUtils::calculateLinearInterpolation
undefined4 __thiscall DateTimeUtils::calculateLinearInterpolation(int this, undefined4 returnValue, undefined4 *timeComponents, uint *outIndices)
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
  undefined **local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined1 local_30 [16];
  undefined1 local_20 [16];

  uVar7 = findTimeSlotIndex(timeComponents); // FUN_0082d390
  if (uVar7 == 0xffffffff) {
    if (outIndices != (uint *)0x0) {
      *outIndices = 0xffffffff;
      outIndices[1] = 0xffffffff;
      outIndices[2] = 0;
    }
    resetSomething(); // FUN_008334a0
    local_30 = (undefined1  [16])0x0;
    local_90 = &PTR_LAB_00d7366c;
    local_20 = (undefined1  [16])0x0;
    anotherReset(); // FUN_009cbee0
  }
  else {
    *(uint *)(this + 4) = uVar7;
    fVar5 = _DAT_00d5780c;
    if (uVar7 < *(int *)(this + 0xc) - 1U) {
      uVar9 = uVar7 + 1;
    }
    else {
      uVar9 = 0;
    }
    iVar3 = *(int *)(*(int *)(this + 8) + uVar7 * 4);
    iVar4 = *(int *)(*(int *)(this + 8) + uVar9 * 4);
    // Calculate total seconds from time components (hours * 3600 + minutes * 60 + seconds)
    uVar1 = *(int *)(iVar3 + 0x18) + (*(int *)(iVar3 + 0x14) + *(int *)(iVar3 + 0x10) * 0x3c) * 0x3c;
    if (uVar9 == 0) {
      uVar2 = timeComponents[5] + (timeComponents[4] + timeComponents[3] * 0x3c) * 0x3c;
      iVar8 = *(int *)(iVar4 + 0x18) +
              (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c + (0x15180 - uVar1);
      if (uVar2 < uVar1) {
        iVar10 = uVar2 + (0x15180 - uVar1);
      }
      else {
        iVar10 = uVar2 - uVar1;
      }
    }
    else {
      iVar10 = ((timeComponents[4] + timeComponents[3] * 0x3c) * 0x3c - uVar1) + timeComponents[5];
      iVar8 = (*(int *)(iVar4 + 0x18) +
              (*(int *)(iVar4 + 0x14) + *(int *)(iVar4 + 0x10) * 0x3c) * 0x3c) - uVar1;
    }
    if (iVar8 == 0) {
      if (outIndices != (uint *)0x0) {
        *outIndices = uVar7;
        outIndices[1] = uVar9;
        outIndices[2] = (uint)fVar5;
      }
      interpolateLinear(iVar4); // FUN_0082d190
    }
    else {
      fVar5 = (float)iVar10;
      if (iVar10 < 0) {
        fVar5 = fVar5 + DAT_00e44578;
      }
      fVar6 = (float)iVar8;
      if (iVar8 < 0) {
        fVar6 = fVar6 + DAT_00e44578;
      }
      if (outIndices != (uint *)0x0) {
        fVar11 = _DAT_00d5780c - fVar5 / fVar6;
        *outIndices = uVar7;
        outIndices[1] = uVar9;
        outIndices[2] = (uint)fVar11;
      }
      performInterpolation(&local_90, fVar5 / fVar6, iVar3, iVar4); // FUN_0082d070
    }
    if (&local_8c != timeComponents) {
      local_8c = *timeComponents;
      local_84 = timeComponents[2];
      local_88 = timeComponents[1];
      local_80 = timeComponents[3];
      local_78 = timeComponents[5];
      local_7c = timeComponents[4];
    }
  }
  interpolateLinear(&local_90); // FUN_0082d190
  return returnValue;
}
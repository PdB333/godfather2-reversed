// FUNC_NAME: AnimationBlendNode::blendPoses
undefined4 AnimationBlendNode::blendPoses(undefined4 this, float *animData, int *blendWeights, float startTime, float endTime, undefined4 output1, undefined4 output2)
{
  float fVar1;
  short sVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5, iVar6, iVar7;
  float fVar8, fVar9, fVar10, fVar12, fVar13, fVar14;
  uint uVar11;
  float local_1c, local_14, local_10, local_c;
  int local_8, local_4;

  piVar3 = blendWeights;
  iVar6 = (int)animData;  // treat animData as raw pointer

  // Check version (byte at offset +1)
  if (*(char *)((int)animData + 1) < '\x02') {
    return 0;
  }

  // Read pointers to array data at offsets 0xc and 0x10
  local_8 = *(int *)((int)animData + 0xc);
  iVar5 = *(int *)((int)animData + 0x10);

  // Get count of first array (short at +2)
  sVar2 = *(short *)(local_8 + 2);
  // Check if blendWeights[1] (size) is valid
  if ((uint)blendWeights[1] <= (uint)(int)sVar2) {
    animData = 0.0;
    FUN_00591c00(&animData);  // error handling
  }
  fVar1 = *(float *)(*piVar3 + sVar2 * 4);  // blend weight for first

  // Same for second array
  uVar11 = (uint)*(short *)(iVar5 + 2);
  if ((uint)piVar3[1] <= uVar11) {
    animData = 0.0;
    FUN_00591c00(&animData);
  }
  fVar14 = *(float *)(*piVar3 + uVar11 * 4);

  // Compute "fVar13" = fVar1 - identity? (DAT_00e2b1a4 likely 0.0)
  fVar13 = fVar1 - DAT_00e2b1a4;  // maybe weight minus offset
  if (startTime == fVar13) {
LAB_0058c9d8:
    animData = startTime;
  }
  else {
    fVar8 = startTime;
    if ((int)startTime < 0) {
      fVar8 = (float)(-0x80000000 - (int)startTime);
    }
    fVar9 = fVar13;
    if ((int)fVar13 < 0) {
      fVar9 = (float)(-0x80000000 - (int)fVar13);
    }
    iVar5 = (int)fVar8 - (int)fVar9;
    if (iVar5 < 1) {
      iVar5 = -iVar5;
    }
    animData = fVar13;
    if (2 < iVar5) goto LAB_0058c9d8;
  }

  fVar8 = fVar14 - DAT_00e2b1a4;
  if (startTime == fVar8) {
LAB_0058ca26:
    fVar9 = startTime;
  }
  else {
    fVar9 = startTime;
    if ((int)startTime < 0) {
      fVar9 = (float)(-0x80000000 - (int)startTime);
    }
    fVar10 = fVar8;
    if ((int)fVar8 < 0) {
      fVar10 = (float)(-0x80000000 - (int)fVar8);
    }
    iVar5 = (int)fVar9 - (int)fVar10;
    if (iVar5 < 1) {
      iVar5 = -iVar5;
    }
    fVar9 = fVar8;
    if (2 < iVar5) goto LAB_0058ca26;
  }

  // Normalize animData (time) based on fVar13 (weight1 offset)
  if (fVar1 == DAT_00e2b1a4) {
    animData = animData - (float)(int)animData;  // fractional part
  }
  else if (fVar13 < animData) {
    animData = animData - (float)(int)(animData / fVar13) * fVar13; // modulo
  }

  // Normalize fVar9 (time2) based on fVar8 (weight2 offset)
  if (fVar14 == DAT_00e2b1a4) {
    fVar8 = (float)(int)fVar9;
  }
  else {
    if (fVar9 <= fVar8) goto LAB_0058ca97;
    fVar8 = (float)(int)(fVar9 / fVar8) * fVar8;
  }
  fVar9 = fVar9 - fVar8;

LAB_0058ca97:
  if (*(char *)(iVar6 + 1) < '\x03') {
    // Version 2: blend two poses
    local_10 = (fVar9 - startTime) + endTime;
    fVar10 = (animData - startTime) + endTime;
    fVar13 = startTime;
    fVar8 = local_10;
    local_c = fVar10;
    if (startTime < fVar1) {
      FUN_0058ac50();  // clamp?
      local_c = fVar10;
    }
    if (fVar13 < fVar14) {
      FUN_0058ac50();
      local_10 = fVar8;
    }
    uVar4 = output1;
    iVar6 = FUN_00590360(this, piVar3, animData, local_c, output1, output2);
    iVar5 = FUN_00590360(this, piVar3, fVar9, local_10, uVar4, output2);
    if ((iVar6 == 0) || (iVar5 == 0)) {
      animData = 0.0;
    }
    else {
      animData = (float)FUN_00584240(iVar6, iVar5, uVar4);  // interpolate results
    }
  }
  else {
    // Version 3: blend three poses
    local_4 = *(int *)(iVar6 + 0x14);  // third array pointer at +0x14
    sVar2 = *(short *)(local_4 + 2);
    if ((uint)piVar3[1] <= (uint)(int)sVar2) {
      local_c = 0.0;
      FUN_00591c00(&local_c);
    }
    fVar13 = *(float *)(*piVar3 + sVar2 * 4); // third weight
    if (fVar13 == DAT_00e2b1a4) {
      local_c = startTime - (float)(int)startTime;
    }
    else {
      fVar8 = fVar13 - DAT_00e2b1a4;
      local_c = startTime;
      if (fVar8 < startTime) {
        local_c = startTime - (float)(int)(startTime / fVar8) * fVar8;
      }
    }

    local_14 = (fVar9 - startTime) + endTime;
    local_1c = (animData - startTime) + endTime;
    local_10 = (local_c - startTime) + endTime;
    fVar8 = startTime;
    fVar10 = local_10;
    fVar12 = local_14;
    if (startTime < fVar1) {
      FUN_0058ac50();
    }
    if (fVar8 < fVar14) {
      FUN_0058ac50();
      local_14 = fVar12;
    }
    if (fVar8 < fVar13) {
      FUN_0058ac50();
      local_10 = fVar10;
    }
    uVar4 = output1;
    iVar6 = FUN_00590360(this, piVar3, animData, local_1c, output1, output2);
    iVar5 = FUN_00590360(this, piVar3, fVar9, local_14, uVar4, output2);
    iVar7 = FUN_00590360(this, piVar3, local_c, local_10, uVar4, output2);

    if ((iVar5 == 0) || (iVar7 == 0)) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_00584240(iVar5, iVar7, uVar4);
    }
    if ((iVar6 == 0) || (iVar5 == 0)) {
      animData = 0.0;
      FUN_0056fb60();
      FUN_0056fb60();
    }
    else {
      animData = (float)FUN_00584240(iVar6, iVar5, uVar4);
      FUN_0056fb60();
      FUN_0056fb60();
    }
  }
  FUN_0056fb60();
  FUN_0056fb60();
  return animData;
}
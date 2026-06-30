// FUNC_NAME: SimManager::calculateSmoothBlendAlpha
undefined4 SimManager::calculateSmoothBlendAlpha(undefined4 param_1, float param_2, int *param_3, float param_4, float param_5, undefined4 param_6, undefined4 param_7)

{
  float fVar1;
  short sVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  int local_4;
  
  piVar3 = param_3;
  iVar6 = (int)param_2;
  if (*(char *)((int)param_2 + 1) < '\x02') {
    return 0;
  }
  local_8 = *(int *)((int)param_2 + 0xc);
  iVar5 = *(int *)((int)param_2 + 0x10);
  sVar2 = *(short *)(local_8 + 2);
  if ((uint)param_3[1] <= (uint)(int)sVar2) {
    param_2 = 0.0;
    FUN_00591c00(&param_2);
  }
  fVar1 = *(float *)(*piVar3 + sVar2 * 4);
  uVar11 = (uint)*(short *)(iVar5 + 2);
  if ((uint)piVar3[1] <= uVar11) {
    param_2 = 0.0;
    FUN_00591c00(&param_2);
  }
  fVar14 = *(float *)(*piVar3 + uVar11 * 4);
  fVar13 = fVar1 - DAT_00e2b1a4;
  if (param_4 == fVar13) {
LAB_0058c518:
    param_2 = param_4;
  }
  else {
    fVar8 = param_4;
    if ((int)param_4 < 0) {
      fVar8 = (float)(-0x80000000 - (int)param_4);
    }
    fVar9 = fVar13;
    if ((int)fVar13 < 0) {
      fVar9 = (float)(-0x80000000 - (int)fVar13);
    }
    iVar5 = (int)fVar8 - (int)fVar9;
    if (iVar5 < 1) {
      iVar5 = -iVar5;
    }
    param_2 = fVar13;
    if (2 < iVar5) goto LAB_0058c518;
  }
  fVar8 = fVar14 - DAT_00e2b1a4;
  if (param_4 == fVar8) {
LAB_0058c566:
    fVar9 = param_4;
  }
  else {
    fVar9 = param_4;
    if ((int)param_4 < 0) {
      fVar9 = (float)(-0x80000000 - (int)param_4);
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
    if (2 < iVar5) goto LAB_0058c566;
  }
  if (fVar1 == DAT_00e2b1a4) {
    param_2 = param_2 - (float)(int)param_2;
  }
  else if (fVar13 < param_2) {
    param_2 = param_2 - (float)(int)(param_2 / fVar13) * fVar13;
  }
  if (fVar14 == DAT_00e2b1a4) {
    fVar8 = (float)(int)fVar9;
  }
  else {
    if (fVar9 <= fVar8) goto LAB_0058c5d7;
    fVar8 = (float)(int)(fVar9 / fVar8) * fVar8;
  }
  fVar9 = fVar9 - fVar8;
LAB_0058c5d7:
  if (*(char *)(iVar6 + 1) < '\x03') {
    local_10 = (fVar9 - param_4) + param_5;
    fVar10 = (param_2 - param_4) + param_5;
    fVar13 = param_4;
    fVar8 = local_10;
    local_c = fVar10;
    if (param_4 < fVar1) {
      FUN_0058ac50();
      local_c = fVar10;
    }
    if (fVar13 < fVar14) {
      FUN_0058ac50();
      local_10 = fVar8;
    }
    uVar4 = param_6;
    iVar6 = FUN_00590360(param_1,piVar3,param_2,local_c,param_6,param_7);
    iVar5 = FUN_00590360(param_1,piVar3,fVar9,local_10,uVar4,param_7);
    if ((iVar6 == 0) || (iVar5 == 0)) {
      param_2 = 0.0;
    }
    else {
      param_2 = (float)FUN_00583b00(iVar6,iVar5,uVar4);
    }
  }
  else {
    local_4 = *(int *)(iVar6 + 0x14);
    sVar2 = *(short *)(local_4 + 2);
    if ((uint)piVar3[1] <= (uint)(int)sVar2) {
      local_c = 0.0;
      FUN_00591c00(&local_c);
    }
    fVar13 = *(float *)(*piVar3 + sVar2 * 4);
    if (fVar13 == DAT_00e2b1a4) {
      local_c = param_4 - (float)(int)param_4;
    }
    else {
      fVar8 = fVar13 - DAT_00e2b1a4;
      local_c = param_4;
      if (fVar8 < param_4) {
        local_c = param_4 - (float)(int)(param_4 / fVar8) * fVar8;
      }
    }
    local_14 = (fVar9 - param_4) + param_5;
    local_1c = (param_2 - param_4) + param_5;
    local_10 = (local_c - param_4) + param_5;
    fVar8 = param_4;
    fVar10 = local_10;
    fVar12 = local_14;
    if (param_4 < fVar1) {
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
    uVar4 = param_6;
    iVar6 = FUN_00590360(param_1,piVar3,param_2,local_1c,param_6,param_7);
    iVar5 = FUN_00590360(param_1,piVar3,fVar9,local_14,uVar4,param_7);
    iVar7 = FUN_00590360(param_1,piVar3,local_c,local_10,uVar4,param_7);
    if ((iVar5 == 0) || (iVar7 == 0)) {
      iVar5 = 0;
    }
    else {
      iVar5 = FUN_00584240(iVar5,iVar7,uVar4);
    }
    if ((iVar6 == 0) || (iVar5 == 0)) {
      param_2 = 0.0;
      FUN_0056fb60();
      FUN_0056fb60();
    }
    else {
      param_2 = (float)FUN_00583b00(iVar6,iVar5,uVar4);
      FUN_0056fb60();
      FUN_0056fb60();
    }
  }
  FUN_0056fb60();
  FUN_0056fb60();
  return param_2;
}
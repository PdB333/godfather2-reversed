// FUNC_NAME: PlayerMovement::updateMovement
void PlayerMovement::updateMovement(int param_1, undefined4 param_2, undefined4 *param_3)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int unaff_ESI;
  int iVar6;
  int unaff_FS_OFFSET;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float local_14;
  
  iVar4 = *(int *)(unaff_ESI + 0xa0);
  *param_3 = 0;
  if ((iVar4 == 0) && (*(int *)(*(int *)(unaff_ESI + 4) + 0x20) != 0)) {
    iVar4 = *(int *)(*(int *)(unaff_ESI + 4) + 0x20);
    if (iVar4 != 0) {
      *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
    }
    iVar4 = FUN_00513f70(iVar4);
    if (iVar4 != 0) {
      uVar5 = *(undefined4 *)(iVar4 + 0x28);
      *(undefined4 *)(unaff_ESI + 0xa0) = *(undefined4 *)(iVar4 + 0x24);
      *(undefined4 *)(unaff_ESI + 0xa4) = uVar5;
    }
    if ((*(int *)(unaff_ESI + 0xa0) != 0) && (*(int *)(unaff_ESI + 0xa0) != 0)) {
      piVar1 = (int *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x30 +
                      *(int *)(unaff_ESI + 0xa0));
      *piVar1 = *piVar1 + 1;
    }
  }
  local_14 = *(float *)(*(int *)(unaff_ESI + 0x24) + 0xac);
  fVar7 = 0.0;
  if (local_14 < 0.0) {
    if ((*(byte *)(unaff_ESI + 0x2c) & 0x10) != 0) {
      return;
    }
    local_14 = 0.0;
  }
  if ((*(uint *)(*(int *)(unaff_ESI + 0x24) + 0x108) & 0x40000) != 0) {
    FUN_004e41b0();
    fVar7 = (fVar7 + *(float *)(*(int *)(unaff_ESI + 0x24) + 0xbc)) * local_14;
    local_14 = fVar7;
  }
  iVar4 = *(int *)(unaff_ESI + 0x24);
  FUN_004e41b0();
  fVar9 = DAT_00e2b1a4;
  fVar10 = *(float *)(unaff_ESI + 0x40) +
           fVar7 * (float)(int)*(short *)(iVar4 + 0x126) + (float)(int)*(short *)(iVar4 + 0x124);
  iVar6 = (int)fVar10;
  fVar11 = (float)iVar6;
  fVar7 = fVar10 - fVar11;
  *(float *)(unaff_ESI + 0x40) = fVar7;
  if ((((*(uint *)(iVar4 + 0x10c) & 0x20000000) == 0) && (iVar6 != 0)) &&
     (FUN_00534350(), fVar7 < fVar9)) {
    fVar8 = fVar7 * fVar10;
    if (fVar7 * fVar10 < fVar9) {
      fVar8 = fVar9;
    }
    iVar6 = (int)fVar8;
    local_14 = ((((float)iVar6 * DAT_00e448a4) / fVar11) * (fVar9 - fVar7) + fVar9) * local_14;
  }
  if ((*(float *)(iVar4 + 0xc0) != 0.0) && (0.0 < *(float *)(unaff_ESI + 0x30))) {
    iVar2 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
    iVar3 = *(int *)(unaff_ESI + 0x10);
    fVar11 = *(float *)(iVar2 + 0x88 + iVar3) - *(float *)(unaff_ESI + 0x88);
    fVar10 = *(float *)(iVar2 + 0x84 + iVar3) - *(float *)(unaff_ESI + 0x84);
    fVar7 = *(float *)(iVar2 + 0x80 + iVar3) - *(float *)(unaff_ESI + 0x80);
    fVar7 = (SQRT(fVar11 * fVar11 + fVar10 * fVar10 + fVar7 * fVar7) / *(float *)(unaff_ESI + 0x30))
            * *(float *)(iVar4 + 0xc0);
    if (fVar9 < fVar7) {
      fVar7 = fVar9;
    }
    local_14 = (fVar9 - fVar7) * local_14;
    iVar6 = (int)((*(float *)(iVar4 + 0xc4) * fVar7 + fVar9) * (float)iVar6);
  }
  param_1 = *(short *)(iVar4 + 0x11a) - param_1;
  *(float *)(unaff_ESI + 0x3c) = local_14 + *(float *)(unaff_ESI + 0x3c);
  if (param_1 < iVar6) {
    iVar6 = param_1;
  }
  if (((DAT_01194a94 != 0) && ((*(uint *)(iVar4 + 0x10c) & 0x1000) == 0)) &&
     (*(int *)(DAT_01194a94 + 0x2c) < iVar6)) {
    iVar6 = *(int *)(DAT_01194a94 + 0x2c);
  }
  if ((iVar6 != 0) &&
     (((*(short *)(iVar4 + 0x118) < 0 ||
       (*(int *)(unaff_ESI + 0x50) < (int)*(short *)(iVar4 + 0x118))) &&
      ((*(uint *)(unaff_ESI + 0x2c) & 0x800) == 0)))) {
    uVar5 = FUN_0050cac0(iVar6,param_2);
    *param_3 = uVar5;
    return;
  }
  return;
}
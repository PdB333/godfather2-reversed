// FUNC_NAME: ChaseCamera::updateCameraPosition
void ChaseCamera::updateCameraPosition(int param_1)

{
  int *piVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  float fVar8;
  
  FUN_00533cc0();
  *unaff_ESI = &PTR_FUN_00e37560;
  unaff_ESI[9] = 0;
  if (*(char *)(unaff_EDI + 0xd) != '\0') {
    return;
  }
  iVar6 = *(int *)(unaff_ESI[1] + 0x20);
  if (iVar6 != 0) {
    *(int *)(iVar6 + 4) = *(int *)(iVar6 + 4) + 1;
  }
  iVar6 = FUN_004f2ce0(iVar6);
  if (iVar6 != 0) {
    uVar3 = *(undefined4 *)(iVar6 + 0x14);
    uVar4 = *(undefined4 *)(iVar6 + 0x18);
    uVar5 = *(undefined4 *)(iVar6 + 0x1c);
    unaff_ESI[0xc] = *(undefined4 *)(iVar6 + 0x10);
    unaff_ESI[0xd] = uVar3;
    unaff_ESI[0xe] = uVar4;
    unaff_ESI[0xf] = uVar5;
    uVar3 = *(undefined4 *)(iVar6 + 0x24);
    uVar4 = *(undefined4 *)(iVar6 + 0x28);
    uVar5 = *(undefined4 *)(iVar6 + 0x2c);
    unaff_ESI[0x10] = *(undefined4 *)(iVar6 + 0x20);
    unaff_ESI[0x11] = uVar3;
    unaff_ESI[0x12] = uVar4;
    unaff_ESI[0x13] = uVar5;
    unaff_ESI[0x14] = DAT_01205228;
    fVar8 = SQRT(((float)unaff_ESI[0xe] - (float)unaff_ESI[0x12]) *
                 ((float)unaff_ESI[0xe] - (float)unaff_ESI[0x12]) +
                 ((float)unaff_ESI[0xd] - (float)unaff_ESI[0x11]) *
                 ((float)unaff_ESI[0xd] - (float)unaff_ESI[0x11]) +
                 ((float)unaff_ESI[0xc] - (float)unaff_ESI[0x10]) *
                 ((float)unaff_ESI[0xc] - (float)unaff_ESI[0x10]));
    if (DAT_00e2b1a4 <= fVar8) {
      if (*(float *)(param_1 + 0x10) <= DAT_00e44598 && DAT_00e44598 != *(float *)(param_1 + 0x10))
      {
        *(float *)(param_1 + 0x10) = DAT_00e44598;
      }
      fVar8 = fVar8 / *(float *)(param_1 + 0x10);
      bVar2 = DAT_01217ab0 < fVar8;
      unaff_ESI[0x16] = fVar8;
      if (bVar2) {
        unaff_ESI[0x15] = unaff_ESI[0x14];
        unaff_ESI[9] = param_1;
        uVar7 = FUN_004e9270();
        if ((((uVar7 != 0) && (uVar7 != 0xffffffff)) && (uVar7 < 0x1000)) &&
           ((uVar7 * 0x38 != -0x11a0f28 &&
            (piVar1 = *(int **)(&DAT_011a0f38 + uVar7 * 0x38), piVar1 != (int *)0x0)))) {
          *piVar1 = *piVar1 + 1;
        }
        FUN_004f2100(unaff_ESI,param_1,*(undefined4 *)(unaff_ESI[1] + 0x10),uVar7,unaff_ESI[4],
                     unaff_ESI[5]);
        return;
      }
    }
  }
  *(undefined1 *)(unaff_EDI + 0xc) = 1;
  return;
}
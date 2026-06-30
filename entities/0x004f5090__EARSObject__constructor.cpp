// FUNC_NAME: EARSObject::constructor
void EARSObject::constructor(int *param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int in_EAX;
  uint uVar8;
  int *piVar9;
  undefined4 *unaff_EDI;
  int unaff_FS_OFFSET;
  uint local_24;
  
  FUN_00533cc0();
  *unaff_EDI = &PTR_FUN_00e377a0;
  uVar5 = DAT_00e2b1a4;
  if (*(char *)(in_EAX + 0xd) == '\0') {
    iVar3 = **(int **)(unaff_FS_OFFSET + 0x2c);
    unaff_EDI[10] = param_1;
    puVar1 = (undefined4 *)(unaff_EDI[4] + 0x10 + *(int *)(iVar3 + 8));
    *puVar1 = uVar5;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = uVar5;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = uVar5;
    puVar1[0xb] = 0;
    if ((param_1[9] & 2U) == 0) {
      if ((param_1[9] & 4U) != 0) {
        iVar4 = unaff_EDI[4];
        iVar3 = *(int *)(iVar3 + 8);
        *(int *)(iVar4 + 0x40 + iVar3) = param_1[0xb];
        iVar3 = iVar4 + 0x40 + iVar3;
        *(int *)(iVar3 + 4) = param_1[0xc];
        *(int *)(iVar3 + 8) = param_1[0xd];
      }
    }
    else {
      pfVar2 = (float *)(unaff_EDI[4] + 0x40 + *(int *)(iVar3 + 8));
      *pfVar2 = (float)param_1[0xb] + *(float *)(unaff_EDI[4] + 0x40 + *(int *)(iVar3 + 8));
      pfVar2[1] = (float)param_1[0xc] + pfVar2[1];
      pfVar2[2] = (float)param_1[0xd] + pfVar2[2];
    }
    unaff_EDI[0xb] = 0;
    unaff_EDI[0xc] = 0;
    unaff_EDI[0xd] = param_1[0xe];
    unaff_EDI[0xe] = uVar5;
    local_24 = 0;
    if ((*param_1 != 0 || param_1[1] != 0) || (param_1[2] != 0 || param_1[3] != 0)) {
      local_24 = FUN_004e9270();
      if ((local_24 != 0) &&
         ((((local_24 != 0xffffffff && (local_24 < 0x1000)) && (local_24 * 0x38 != -0x11a0f28)) &&
          (piVar9 = *(int **)(&DAT_011a0f38 + local_24 * 0x38), piVar9 != (int *)0x0)))) {
        *piVar9 = *piVar9 + 1;
      }
    }
    if ((param_1[4] != 0 || param_1[5] != 0) || (param_1[6] != 0 || param_1[7] != 0)) {
      uVar8 = FUN_004e9270();
      if ((((uVar8 != 0) && ((uVar8 != 0xffffffff && (uVar8 < 0x1000)))) &&
          (uVar8 * 0x38 != -0x11a0f28)) &&
         (piVar9 = *(int **)(&DAT_011a0f38 + uVar8 * 0x38), piVar9 != (int *)0x0)) {
        *piVar9 = *piVar9 + 1;
      }
    }
    uVar5 = unaff_EDI[5];
    uVar6 = *(undefined4 *)(unaff_EDI[1] + 0x10);
    uVar7 = unaff_EDI[4];
    piVar9 = (int *)(DAT_01206880 + 0x14);
    *(undefined ***)*piVar9 = &PTR_FUN_01124e68;
    *piVar9 = *piVar9 + 4;
    FUN_004f56c0(unaff_EDI,param_1,uVar6,uVar7,uVar5,local_24);
  }
  return;
}
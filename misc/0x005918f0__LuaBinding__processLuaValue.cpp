// FUNC_NAME: LuaBinding::processLuaValue
byte FUN_005918f0(undefined4 param_1, char *param_2, int *param_3, undefined4 param_4)

{
  char cVar1;
  short *psVar2;
  int *piVar3;
  byte bVar4;
  undefined4 *puVar5;
  int iVar6;
  int extraout_EDX;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  float in_XMM0_Da;
  char *pcVar10;
  byte local_5;
  
  piVar3 = param_3;
  pcVar8 = param_2;
  cVar1 = *param_2;
  local_5 = 0;
  if (cVar1 == '\t') {
    // Type: nil or boolean (0x09)
    if ((**(int **)(param_2 + 4) == 0) || ((char)param_4 == '\0')) {
      uVar7 = (*(int **)(param_2 + 4))[1];
      if ((uint)param_3[1] <= uVar7) {
        param_2 = (char *)0x0;
        FUN_00591c00(&param_2);
      }
      *(undefined4 *)(*piVar3 + uVar7 * 4) = 0;
      local_5 = 1;
      goto LAB_00591a72;
    }
    puVar5 = (undefined4 *)FUN_0058abc0(param_3);
    pcVar10 = DAT_00e2b04c;
  }
  else {
    if (cVar1 == '\x03') {
      // Type: number (0x03)
      psVar2 = *(short **)(param_2 + 4);
      uVar7 = (uint)*psVar2;
      if ((uint)param_3[1] <= uVar7) {
        param_2 = (char *)0x0;
        FUN_00591c00(&param_2);
      }
      iVar9 = *piVar3;
      iVar6 = FUN_0058b2e0(param_1,pcVar8,piVar3);
      *(float *)(iVar9 + uVar7 * 4) = (float)iVar6;
      uVar7 = (uint)psVar2[1];
      if ((uint)piVar3[1] <= uVar7) {
        param_2 = (char *)0x0;
        FUN_00591c00(&param_2);
      }
      *(char **)(*piVar3 + uVar7 * 4) = DAT_00e2eff4;
      goto LAB_00591a72;
    }
    if (cVar1 == '\x06') {
      // Type: string (0x06)
      iVar9 = FUN_0058c0b0(param_1,param_2,param_3);
      param_2 = (char *)(float)iVar9;
      puVar5 = (undefined4 *)FUN_0058abc0(piVar3);
      *puVar5 = param_2;
      puVar5 = (undefined4 *)FUN_0058abc0(piVar3);
      pcVar10 = DAT_00e2eff4;
    }
    else {
      if (cVar1 != '\x14') goto LAB_00591a72;
      // Type: function (0x14)
      FUN_00593700();
      param_2 = (char *)(in_XMM0_Da * *(float *)(extraout_EDX + 0xc) + *(float *)(extraout_EDX + 8))
      ;
      puVar5 = (undefined4 *)FUN_0058abc0(piVar3);
      pcVar10 = param_2;
    }
  }
  *puVar5 = pcVar10;
LAB_00591a72:
  iVar9 = (int)pcVar8[1];
  if (0 < iVar9) {
    pcVar8 = pcVar8 + 0xc;
    do {
      bVar4 = FUN_005918f0(param_1,*(undefined4 *)pcVar8,piVar3,param_4);
      local_5 = local_5 | bVar4;
      pcVar8 = pcVar8 + 4;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  return local_5;
}
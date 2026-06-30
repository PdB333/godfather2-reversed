// FUNC_NAME: AptManager::initialize
undefined1 AptManager::initialize(undefined4 param_1)

{
  int *piVar1;
  code *pcVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int unaff_FS_OFFSET;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (DAT_012055b0 != 0) goto LAB_005a0355;
  local_14 = "bAptIsInitialized";
  local_10 = "..\\source\\Apt\\Apt.cpp";
  local_c = 0x342;
  local_8 = 2;
  local_4 = &DAT_01128f5b;
  if (DAT_01128f5b == '\0') goto LAB_005a0355;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar4 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005a0332:
    if ((uVar4 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"bAptIsInitialized");
    if (local_4 != (undefined1 *)0x0) goto LAB_005a0332;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    uVar3 = (*pcVar2)();
    return uVar3;
  }
LAB_005a0355:
  uVar9 = 1;
  uVar8 = 1;
  uVar7 = 0;
  uVar5 = FUN_0059e2f0(0,param_1,1,1);
  iVar6 = FUN_005aea60(uVar5,uVar7,param_1,uVar8,uVar9);
  if ((iVar6 != 0) && (iVar6 != DAT_0119cbbc)) {
    iVar6 = FUN_0059c3b0();
    return iVar6 != 0;
  }
  return false;
}
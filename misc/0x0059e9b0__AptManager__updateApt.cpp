// FUNC_NAME: AptManager::updateApt
void AptManager::updateApt(int param_1, float param_2)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  int unaff_FS_OFFSET;
  char *local_44;
  char *local_40;
  undefined4 local_3c;
  int local_38;
  undefined1 *local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  if (DAT_012055b0 != 0) goto LAB_0059ea50;
  local_44 = "bAptIsInitialized";
  local_40 = "..\\source\\Apt\\Apt.cpp";
  local_3c = 0x1c4;
  local_38 = 2;
  local_34 = &DAT_01128f40;
  if (DAT_01128f40 == '\0') goto LAB_0059ea50;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_0059ea2e:
    if ((uVar3 & 2) != 0) {
      *local_34 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_44,"bAptIsInitialized");
    if (local_34 != (undefined1 *)0x0) goto LAB_0059ea2e;
  }
  if (((piVar1 != (int *)0x0) || (local_38 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_38 == 0 || (local_38 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_0059ea50:
  if ((DAT_0119a9cc != 0) && (0.0 <= param_2)) {
    if (param_2 < DAT_00e2b1a4) {
      local_2c = DAT_00e2b1a4;
      local_28 = DAT_00e2b1a4;
      local_24 = DAT_00e2b1a4;
      local_30 = param_2;
      uStack_14 = 0;
      uStack_18 = 0;
      uStack_1c = 0;
      uStack_20 = 0;
      FUN_0059cc70(&local_30);
    }
    if (param_1 == -1) {
      FUN_005b36b0(DAT_0119cbf0,0,0);
    }
    else {
      FUN_005b3570(param_1);
    }
    if (param_2 < DAT_00e2b1a4) {
      FUN_0059cb90();
    }
    if (param_1 == 0) {
      DAT_0103af70 = param_1;
    }
  }
  return;
}
// FUNC_NAME: StreamManager::updateStreaming
void StreamManager::updateStreaming(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined1 uStack_12;
  undefined1 uStack_11;
  undefined4 local_10;
  float local_c;
  
  if (DAT_012067e8 <= DAT_00e44598) {
    local_c = DAT_00e2e230;
  }
  else {
    local_c = DAT_00e2b1a4 / DAT_012067e8;
  }
  local_10 = *(undefined4 *)(DAT_01223480 + 0x24);
  iVar5 = *(int *)(param_1 + 0x1c);
  if (((iVar5 != 0) && (*(int *)(iVar5 + 8) == 0)) && (*(int *)(param_1 + 0x20) != 0)) {
    iVar5 = *(int *)(iVar5 + 0x10);
    *(int *)(iVar5 + 0x18) = *(int *)(param_1 + 0x20);
    *(undefined1 *)(iVar5 + 0x48) = 1;
    FUN_00558b70();
    FUN_009e7450(*(undefined4 *)(param_1 + 0x1c));
  }
  iVar5 = **(int **)(param_1 + 4);
  if (iVar5 != (*(int **)(param_1 + 4))[1] * 0x70 + iVar5) {
    do {
      if (*(int *)(*(int *)(iVar5 + 0x40) + 8) == 0) {
        FUN_005570a0(local_c);
        iVar1 = *(int *)(iVar5 + 0x40);
        if (iVar1 == 0) {
LAB_0055894f:
          if (*(int *)(iVar5 + 0x40) != 0) {
            FUN_009e7450(*(int *)(iVar5 + 0x40));
            goto LAB_005589a8;
          }
        }
        else {
          piVar2 = (int *)(**(code **)(*DAT_0113dfc8 + 0x14))();
          uVar3 = (**(code **)(*piVar2 + 0x10))(iVar1);
          pcVar4 = (char *)FUN_00ab06f0(&uStack_12,uVar3);
          if (*pcVar4 != '\0') goto LAB_0055894f;
        }
        iVar1 = *(int *)(iVar5 + 0x40);
        if (iVar1 != 0) {
          piVar2 = (int *)(**(code **)(*DAT_0113dfc8 + 0x14))();
          uVar3 = (**(code **)(*piVar2 + 0x10))(iVar1);
          pcVar4 = (char *)FUN_00ab06f0(&uStack_11,uVar3);
          if (*pcVar4 == '\0') goto LAB_005589a8;
        }
        if (*(int *)(iVar5 + 0x40) != 0) {
          FUN_009e6ff0(*(int *)(iVar5 + 0x40),1);
        }
      }
LAB_005589a8:
      iVar5 = iVar5 + 0x70;
    } while (iVar5 != (*(int **)(param_1 + 4))[1] * 0x70 + **(int **)(param_1 + 4));
  }
  return;
}
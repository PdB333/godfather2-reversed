// FUNC_NAME: MissionManager::startMissionFromDialog
undefined4 MissionManager::startMissionFromDialog(undefined4 param_1, undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int local_20 [8];
  
  iVar5 = 0;
  iVar2 = FUN_004a37d0(); // GetGameManager
  if ((*(int *)(iVar2 + 0x1c) == 0) || (*(int *)(iVar2 + 8) != 0x33a1672c)) {
    return 0;
  }
  piVar3 = (int *)FUN_004a3790(0x22898a7f); // GetGlobalVariable
  if (piVar3 != (int *)0x0) {
    iVar5 = *piVar3;
  }
  uVar4 = 0x16; // Default mission type: Story
  if (iVar5 != 0) {
    if (iVar5 == 1) {
      uVar4 = 0x17; // Side mission
    }
    else if (iVar5 == 2) {
      uVar4 = 0x18; // Favor mission
    }
  }
  uVar6 = 0;
  iVar5 = FUN_0054a4d0(); // GetDialogManager
  iVar2 = 0;
  if (0 < *(int *)(iVar5 + 0xc)) { // +0x0C = dialogCount
    do {
      iVar1 = *(int *)(*(int *)(*(int *)(iVar5 + 8) + iVar2 * 4) + 0x10); // +0x10 = missionId
      if (iVar1 != 0) {
        if (7 < uVar6) break;
        local_20[uVar6] = iVar1;
        uVar6 = uVar6 + 1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(iVar5 + 0xc));
    if (uVar6 != 0) {
      iVar5 = FUN_009c8e50(0x10); // Allocate memory
      if (iVar5 != 0) {
        uVar4 = FUN_008ca540(param_1,param_2,local_20,uVar6,uVar4); // StartMission
        return uVar4;
      }
    }
  }
  return 0;
}
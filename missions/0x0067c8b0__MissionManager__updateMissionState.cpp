// FUNC_NAME: MissionManager::updateMissionState
void MissionManager::updateMissionState(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_01129820 == 0) { // +0x0: missionManager singleton check
    if (DAT_01206880 == 0) { // +0x0: flowState check (e.g. isActive)
      FUN_0068baf0(0); // clearMissionState
      iVar1 = FUN_009c8e50(0x20); // allocateMissionNode (size 0x20)
      if (iVar1 != 0) {
        uVar2 = FUN_009c8f80(); // createMissionInstance
        FUN_008d0f10(uVar2); // activateCurrentMission
      }
      FUN_0068bcd0(0); // pushMissionEvent
      return;
    }
    iVar1 = FUN_009c8e50(0x20); // allocateMissionNode (size 0x20)
    if (iVar1 != 0) {
      uVar2 = FUN_009c8f80(); // createMissionInstance
      FUN_008d0f10(uVar2); // activateCurrentMission
    }
  }
  return;
}
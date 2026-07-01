// FUNC_NAME: Player::tryStartMission
void __fastcall Player::tryStartMission(int thisPtr)
{
  char isMissionActive;
  int *missionManager;
  
  // Check if mission is not already active (+0x7c = missionActive flag)
  // and there is a current mission (+0x58 = currentMission pointer)
  if ((((*(char *)(thisPtr + 0x7c) == '\0') && (*(int *)(thisPtr + 0x58) != 0)) &&
      // Get mission manager singleton from global pointer (DAT_01131018)
      (missionManager = (int *)FUN_0043b870(DAT_01131018), missionManager != (int *)0x0)) &&
     // Call mission manager's canStartMission method (vtable+0x38)
     (cVar1 = (**(code **)(*missionManager + 0x38))(), cVar1 != '\0')) {
    // Set mission active flag (+0x7c)
    *(undefined1 *)(thisPtr + 0x7c) = 1;
    // Start the mission
    FUN_009aef10();
    return;
  }
  return;
}
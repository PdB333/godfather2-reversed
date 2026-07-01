// FUNC_NAME: MultiplayerScenarioManager::getBiggestEnemyString
char* MultiplayerScenarioManager::getBiggestEnemyString(void)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_4;
  
  local_4 = 0;
  if (**(int **)(DAT_012233a0 + 4) == 0) { // +0x4: pointer to current scenario
    iVar1 = 0;
  }
  else {
    iVar1 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // -0x1f30: offset to MultiplayerScenario
  }
  if ((*(int *)(DAT_0112ebb4 + 0x16c) != 0) && (iVar1 != 0)) {
    uVar2 = FUN_004bb390(DAT_0112b6fc,*(undefined4 *)(iVar1 + 0x1ef8),&local_4); // retrieve player data
    iVar1 = FUN_004baf60(uVar2); // get biggest enemy player
    if (iVar1 != 0) {
      piVar3 = (int *)FUN_004bb600(iVar1); // get player name
      if ((char *)*piVar3 != (char *)0x0) {
        return (char *)*piVar3;
      }
      return &DAT_0120546e; // fallback to empty string?
    }
  }
  return "$mp_finalscore_no_biggest_enemy"; // localized string key
}
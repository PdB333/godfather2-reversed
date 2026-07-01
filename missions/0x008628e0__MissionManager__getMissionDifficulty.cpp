// FUNC_NAME: MissionManager::getMissionDifficulty
int __thiscall getMissionDifficulty(int param_1, int param_2, int param_3, int param_4)
{
  int iVar1;
  char cVar2;
  int missionIndex; // local_8
  int *difficultyPtr; // local_4
  
  missionIndex = 0;
  difficultyPtr = (int *)0x0;
  cVar2 = FUN_00862820(param_1, param_2, param_3, param_4, &DAT_00d756d0, &missionIndex);
  if ((((cVar2 != '\0') && (difficultyPtr != (int *)0x0)) && (missionIndex != 0)) &&
     ((*(char *)(missionIndex + 6) == '\x02' && (iVar1 = *difficultyPtr, iVar1 != 0)))) {
    if (iVar1 == 1) {
      return 2; // Medium difficulty
    }
    if (iVar1 == 2) {
      return 3; // Hard difficulty
    }
  }
  return 1; // Easy difficulty (default)
}
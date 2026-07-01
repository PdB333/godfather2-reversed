// FUNC_NAME: PlayerReputationTracker::hasReputationFlags
undefined4 PlayerReputationTracker::hasReputationFlags(undefined4 param_1, int param_2, int *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint reputationFlags;
  int reputationData;
  uint *reputationPtr;
  
  iVar4 = 0;
  iVar2 = 0;
  iVar3 = 0;
  iVar5 = 0;
  reputationFlags = 0;
  reputationData = 0;
  reputationPtr = (uint *)0x0;
  cVar1 = FUN_005fd340(*(undefined2 *)(param_2 + 0x12),0x998cab76,&reputationData);
  if ((((cVar1 != '\0') && (reputationPtr != (uint *)0x0)) && (reputationData != 0)) &&
     (*(char *)(reputationData + 6) == '\x02')) {
    reputationFlags = *reputationPtr;
  }
  if ((reputationFlags & 2) != 0) {
    reputationData = 0;
    reputationPtr = (uint *)0x0;
    cVar1 = FUN_005fd340(*(undefined2 *)(param_2 + 0x12),0x22c6cc5,&reputationData);
    if (((cVar1 != '\0') && (reputationPtr != (uint *)0x0)) &&
       ((reputationData != 0 && (*(char *)(reputationData + 6) == '\x04')))) {
      iVar4 = *reputationPtr;
      iVar5 = reputationPtr[1];
      iVar3 = reputationPtr[2];
      iVar2 = reputationPtr[3];
    }
  }
  if (param_3 != (int *)0x0) {
    *param_3 = ((iVar4 * 0x21 + iVar5) * 0x21 + iVar3) * 0x21 + iVar2;
  }
  if (((iVar4 == 0) && (iVar5 == 0)) && ((iVar3 == 0 && (iVar2 == 0)))) {
    return 0;
  }
  return 1;
}
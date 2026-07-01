// FUNC_NAME: MissionManager::completeObjective
void MissionManager::completeObjective(int param_1, int param_2, int param_3, int param_4)
{
  int iVar1;
  int uVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = FUN_004461c0(param_1,0);
  if (iVar1 != 0) {
    uVar2 = FUN_0043aaf0();
    piVar3 = (int *)FUN_0045d9e0(iVar1);
    iVar4 = FUN_008ecbc0(((*piVar3 * 0x21 + piVar3[1]) * 0x21 + piVar3[2]) * 0x21 + piVar3[3]);
    uVar2 = FUN_008ebf00(uVar2,iVar1,param_4,param_3);
    FUN_008eb6b0(uVar2,param_2);
    *(int *)(iVar4 + 8) = 2; // +0x8 = objectiveState, set to COMPLETED (2)
    return;
  }
  if (param_3 != 0) {
    FUN_00408b80(&DAT_0112fde8,param_3 + 0x3c,0); // +0x3c = some string offset, log error
  }
  return;
}
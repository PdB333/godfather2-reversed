// FUNC_NAME: NPCManager::processPendingSpawnRequests
void __thiscall NPCManager::processPendingSpawnRequests(int this, uint param_2, undefined4 param_3, int *param_4)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  
  if ((*(byte *)(this + 0x80) & 1) != 0) {
    iVar3 = FUN_006b1980(); // likely getSpawnQueue or getPendingSpawns
    piVar1 = param_4;
    if ((*(int *)(iVar3 + 4) != 0) && (*param_4 == 0)) {
      *param_4 = 1;
    }
    uVar5 = 0;
    if (*(int *)(iVar3 + 4) != 0) {
      do {
        if (*piVar1 == 0) {
          return;
        }
        piVar4 = (int *)FUN_008e33d0(1); // likely allocateNPC or createEntity
        if (piVar4 != (int *)0x0) {
          param_2 = 0;
          cVar2 = (**(code **)(*piVar4 + 0x10))(0xd7e44d6a,&param_2); // vtable call, likely validateSpawn
          param_2 = -(uint)(cVar2 != '\0') & param_2;
          if ((param_2 != 0) && (cVar2 = FUN_00791230(), cVar2 != '\0')) { // likely checkSpawnConditions
            FUN_006b44a0(&param_2); // likely spawnNPC or finalizeSpawn
            *piVar1 = *piVar1 + -1;
          }
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < *(uint *)(iVar3 + 4));
    }
  }
  return;
}
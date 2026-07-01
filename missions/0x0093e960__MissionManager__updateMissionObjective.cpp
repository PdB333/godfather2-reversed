// FUNC_NAME: MissionManager::updateMissionObjective
void __thiscall MissionManager::updateMissionObjective(int thisPtr, int objectiveId, char isPrimary)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined4 local_4;
  
  if (*(uint *)(thisPtr + 0x50) < 0x14) {
    iVar3 = 0;
    bVar5 = isPrimary == '\0';
    if (bVar5) {
      local_4 = 10000; // Secondary objective reward
      uVar2 = 10000;
      iVar4 = 12000;   // Secondary objective XP
    }
    else {
      uVar2 = 5000;    // Primary objective reward
      iVar4 = 0;       // Primary objective XP
      local_4 = 5000;
    }
    _param_3 = (uint)!bVar5;
    for (puVar1 = *(undefined4 **)(thisPtr + 0x48); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((puVar1[2] == 0) && (puVar1[8] == objectiveId)) {
        if (puVar1 == *(undefined4 **)(thisPtr + 0x78)) {
          // Current objective - update mission state
          *(undefined2 *)(thisPtr + 0x60) = 0;
          *(undefined2 *)(thisPtr + 0x62) = 0;
          *(int *)(thisPtr + 0x6c) = iVar4;
          *(uint *)(thisPtr + 100) = (uint)bVar5;
          *(undefined4 *)(thisPtr + 0x68) = 0;
          *(undefined4 *)(thisPtr + 0x70) = uVar2;
          *(uint *)(thisPtr + 0x74) = _param_3;
          *(ushort *)(thisPtr + 0x60) = *(ushort *)(thisPtr + 0x60) | 0x1f;
          *(ushort *)(thisPtr + 0x62) = *(ushort *)(thisPtr + 0x62) | 0x10;
          return;
        }
        // Non-current objective - update individual objective
        *(undefined2 *)((int)puVar1 + 0x12) = 0;
        *(ushort *)(puVar1 + 4) = (ushort)bVar5;
        if (iVar4 != 0) {
          iVar3 = DAT_01205224 + iVar4;
        }
        puVar1[3] = iVar3;
        *(short *)(puVar1 + 5) = (short)uVar2;
        return;
      }
    }
    // Objective not found - create new one
    iVar3 = FUN_0093dbe0(); // AllocateObjective
    if ((iVar3 != 0) &&
       (iVar3 = FUN_0093e000(objectiveId, (uint)bVar5, iVar4, local_4, _param_3), iVar3 != 0)) {
      FUN_0093e4c0(iVar3); // AddObjectiveToList
    }
  }
  return;
}
// FUNC_NAME: MissionManager::processMissionObjective

undefined4 __thiscall MissionManager::processMissionObjective(int thisPtr, int objectiveIndex, undefined4 param3, int param4, int param5)
{
  undefined4 *puVar1;
  byte *pbVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 uVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined4 local_1c;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Check if mission data exists at +0x2c88
  if (*(int *)(thisPtr + 0x2c88) == 0) {
    return 0;
  }
  
  // Get objective data at offset +0x140 + objectiveIndex * 0x24
  pbVar2 = (byte *)(*(int *)(thisPtr + 0x2c88) + 0x140 + objectiveIndex * 0x24);
  
  // Check various conditions that would cause early exit
  if ((((*(uint *)(thisPtr + 0x2c6c) >> 4 & 1) != 0) || (*(float *)(pbVar2 + 0x14) <= 0.0)) ||
     ((cVar6 = FUN_0072a240(), cVar6 != '\0' &&
      (((param4 != 0 && (iVar8 = FUN_006b1c70(param4,0x55859efa), iVar8 != 0)) &&
       (*(int *)(iVar8 + 0x1ed4) == 0x637b907)))))) {
    return 0;
  }
  
  uVar5 = DAT_01205228;
  puVar9 = (undefined4 *)(thisPtr + 0x193c);
  puVar1 = puVar9 + *(int *)(thisPtr + 0x1a3c);
  local_1c = 0;
  
  // Check if objective already exists in list
  if (puVar9 != puVar1) {
    do {
      uVar3 = *puVar9;
      iVar8 = FUN_00788430(objectiveIndex, param3, uVar5, param4);
      if (iVar8 != 0) break;
      puVar9 = puVar9 + 1;
      uVar3 = local_1c;
    } while (puVar9 != puVar1);
    local_1c = uVar3;
    if (iVar8 != 0) goto LAB_007878f1;
  }
  
  // Initialize objective system if needed
  if (*(int *)(thisPtr + 0x2c58) == 0) {
    FUN_00786500();
  }
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  
  // Allocate and initialize new objective
  iVar8 = (*(code *)**(undefined4 **)(thisPtr + 0x2c40))(0x24, &local_c);
  if (iVar8 == 0) {
    iVar8 = 0;
  }
  else {
    iVar8 = FUN_00785a60(objectiveIndex, uVar5, param3, param4);
  }
  
  local_1c = FUN_00787550(iVar8);
  FUN_00788920(iVar8, 1);
  
  // Notify objective listeners
  if (*(int *)(thisPtr + 0x2c70) != 0) {
    (**(code **)**(undefined4 **)(thisPtr + 0x2c70))(iVar8);
  }
  
  // Set flags and register message handlers
  if ((*(byte *)(thisPtr + 0x2c6c) & 1) == 0) {
    *(uint *)(thisPtr + 0x2c6c) = *(uint *)(thisPtr + 0x2c6c) | 1;
    FUN_00407e40(&DAT_012069c4);
    FUN_00407e40(&DAT_012069d4);
  }
  
  if ((*(uint *)(thisPtr + 0x2c6c) >> 5 & 1) == 0) {
    FUN_00408240(&DAT_011302b8, "iMsgEnteredPauseMap");
    FUN_00408240(&DAT_01130248, "iMsgExitedPauseMap");
    FUN_00407e40(&DAT_011302b8);
    FUN_00407e40(&DAT_01130248);
    *(uint *)(thisPtr + 0x2c6c) = *(uint *)(thisPtr + 0x2c6c) | 0x20;
  }
  
LAB_007878f1:
  // Process objective completion/update
  if ((*pbVar2 & 1) != 0) {
    if (param5 == 0) {
      // No specific target - iterate through all entities
      param3._0_1_ = FUN_00785b70(iVar8, local_1c);
      puVar9 = (undefined4 *)FUN_0043c2c0(2);
      for (piVar4 = (int *)*puVar9; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[1]) {
        if ((((*piVar4 != 0) && (iVar10 = FUN_0043b870(DAT_0112af58), iVar10 != 0)) &&
            ((cVar6 = FUN_007829d0(), cVar6 != '\0' && (cVar6 = FUN_00782ce0(), cVar6 == '\0')))) &&
           ((((char)param3 != '\0' || ((*(uint *)(iVar10 + 0x74) >> 1 & 1) != 0)) &&
            (cVar6 = FUN_00786da0(iVar10, objectiveIndex, iVar8), cVar6 != '\0')))) {
          cVar6 = FUN_00782ce0();
          cVar7 = (**(code **)(*(int *)(iVar10 + 0x1c) + 4))(param4, *(undefined4 *)(iVar8 + 0x20));
          if (cVar7 != '\0') {
            if (cVar6 != '\0') {
              FUN_00785bd0(iVar10);
            }
            FUN_007882f0(iVar10 + 0x1c);
            param3._0_1_ = FUN_00785b70(iVar8, local_1c);
          }
        }
      }
    }
    else {
      // Specific target provided
      cVar6 = FUN_00785b70(iVar8, local_1c);
      if ((((cVar6 != '\0') || ((*(uint *)(param5 + 0x74) >> 1 & 1) != 0)) &&
          (cVar6 = FUN_00782ce0(), cVar6 == '\0')) &&
         ((param4 != 0 && (cVar6 = FUN_00786da0(param5, objectiveIndex, iVar8), cVar6 != '\0')))) {
        cVar6 = (**(code **)(*(int *)(param5 + 0x1c) + 4))(param4, *(undefined4 *)(iVar8 + 0x20));
        if (cVar6 != '\0') {
          *(int *)(iVar8 + 0x20) = *(int *)(iVar8 + 0x20) + 1;
          FUN_007882f0(param5 + 0x1c);
          return 1;
        }
      }
    }
  }
  return 1;
}
// FUNC_NAME: GodfatherGameManager::updateMissionObjectiveDisplay
undefined4 GodfatherGameManager::updateMissionObjectiveDisplay(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_14 = 0;
  local_10 = 0;
  uVar3 = 0;
  uVar4 = 0;
  local_18 = 0;
  local_c = DAT_00d648f4; // Default distance threshold
  iVar1 = FUN_006257d0(param_1,1); // Get mission objective count
  uVar5 = 0;
  if (iVar1 != 0) {
    fVar6 = (float10)FUN_006259b0(param_1,1); // Get current objective index
    local_8 = (uint)(longlong)ROUND(fVar6);
    if (local_8 < 4) {
      uVar5 = local_8;
    }
  }
  iVar1 = (&DAT_0112e170)[uVar5 * 3]; // Objective data array (3 entries per objective)
  if (iVar1 != 0) {
    uVar4 = (&DAT_0112e168)[uVar5 * 3]; // Objective type/state
    local_18 = *(int *)(iVar1 + 0x1bc); // Objective completion flag
    local_14 = *(undefined4 *)(iVar1 + 0x34); // Objective position X
    local_10 = *(undefined4 *)(iVar1 + 0x140); // Objective position Y
    uVar3 = 1;
    if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
      iVar2 = FUN_00471610(); // Get player position
      fVar7 = *(float *)(iVar2 + 0x30) - *(float *)(iVar1 + 0x1c); // Delta X
      fVar8 = *(float *)(iVar2 + 0x34) - *(float *)(iVar1 + 0x20); // Delta Y
      fVar9 = *(float *)(iVar2 + 0x38) - *(float *)(iVar1 + 0x24); // Delta Z
      local_c = fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7; // Distance squared
    }
  }
  FUN_00625df0(param_1,uVar3); // Set objective active state
  FUN_00625e10(param_1,uVar4); // Set objective type
  fVar7 = (float)local_18;
  if (local_18 < 0) {
    fVar7 = fVar7 + DAT_00e44578; // Handle negative completion flag
  }
  FUN_00625c40(param_1,fVar7); // Set completion percentage
  FUN_00625c40(param_1,local_14); // Set position X
  FUN_00625c40(param_1,local_10); // Set position Y
  FUN_00625c40(param_1,local_c); // Set distance to objective
  return 6; // Return number of display elements updated
}
// FUNC_NAME: MissionManager::handleMissionEvent
void __thiscall MissionManager::handleMissionEvent(undefined4 param_1, int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *param_2;
  if (iVar3 == DAT_01206940) {
    FUN_008f0d60(); // MissionManager::handleMissionComplete
    return;
  }
  if (*(int *)(param_2[1] + 0xc) == 0) { // +0xC: mission data pointer
    uVar4 = 0;
  }
  else {
    uVar4 = *(undefined4 *)(*(int *)(param_2[1] + 0xc) + 0x1c); // +0x1C: mission objective ID
  }
  iVar2 = FUN_004025a0(uVar4); // EntityManager::findEntityByID
  if (iVar2 == 0) {
    param_2 = (int *)0xfe16702f; // invalid entity sentinel
  }
  else {
    param_2 = *(int **)(iVar2 + 0x2c); // +0x2C: entity data pointer
  }
  uVar1 = param_2;
  if (iVar3 == DAT_01206760) { // mission objective start event
    FUN_008ee940(&param_2, uVar4); // MissionManager::startObjective
    return;
  }
  if (iVar3 == DAT_01206780) { // mission objective complete event
    FUN_008ef6b0(param_2); // MissionManager::completeObjective
    FUN_004035f0(uVar4, 0x46, param_1); // EventManager::fireEvent(0x46 = mission objective complete)
    return;
  }
  if (iVar3 == DAT_01206768) { // mission objective update event
    iVar3 = FUN_008ecbc0(param_2); // MissionManager::getObjectiveState
    FUN_004035f0(uVar4, 0x46, param_1); // EventManager::fireEvent
    if ((iVar3 != 0) && (*(int *)(iVar3 + 8) == 4)) { // +0x8: state enum, 4 = completed
      FUN_008ee810(uVar1); // MissionManager::finalizeObjective
      FUN_008ef580(); // MissionManager::checkMissionCompletion
    }
  }
  return;
}
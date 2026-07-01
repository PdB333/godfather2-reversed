// FUNC_NAME: GodfatherGameManager::saveGame
bool __fastcall GodfatherGameManager::saveGame(int *this)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 auStack_424 [1060];
  
  iVar4 = -1;
  piVar1 = (int *)FUN_00ad8d40(); // GetSaveManager or similar
  if (piVar1 != (int *)0x0) {
    iVar2 = (**(code **)(*piVar1 + 0x34))(); // SaveManager::isSaveAllowed?
    if (iVar2 != 0) {
      piVar1 = (int *)(**(code **)(*piVar1 + 0x34))(); // Get save slot manager
      piVar1 = (int *)(**(code **)(*piVar1 + 0x24))(); // Get current save slot
      if (piVar1 != (int *)0x0) {
        uVar3 = (**(code **)(*this + 0x10))(); // Get save data buffer
        FUN_00b21d90(uVar3); // Prepare save data
        FUN_00b21ed0(this); // Serialize game state
        iVar4 = (**(code **)(*piVar1 + 0x38))(auStack_424,1,0); // Write save to file
        FUN_00b19550(); // Cleanup/notify
      }
    }
  }
  return -1 < iVar4;
}
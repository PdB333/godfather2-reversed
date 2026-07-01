// FUNC_NAME: GodfatherGameManager::isPlayerInFreeRoam
bool GodfatherGameManager::isPlayerInFreeRoam(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = FUN_00798f50(0x35); // Get current game state (0x35 = kGameState_Gameplay)
  cVar1 = FUN_0079e920(uVar2); // Check if state is active
  if (cVar1 != '\0') {
    cVar1 = FUN_007ab420(0x80000); // Check if free roam flag is set (0x80000)
    if (cVar1 != '\0') {
      iVar3 = FUN_007ab360(); // Get player's current mode/state
      return iVar3 != 0; // Return true if player is in free roam mode
    }
  }
  return false;
}
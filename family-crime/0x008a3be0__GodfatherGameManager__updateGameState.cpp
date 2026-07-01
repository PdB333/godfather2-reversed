// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(void)
{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = (int *)FUN_00ad8d40(); // likely getGameManager() or getSingleton()
  if (piVar1 != (int *)0x0) {
    iVar2 = (**(code **)(*piVar1 + 0x34))(); // vtable[0x34] -> getCurrentState()
    if (iVar2 != 0) {
      piVar1 = (int *)(**(code **)(*piVar1 + 0x34))(); // getCurrentState() again
      piVar1 = (int *)(**(code **)(*piVar1 + 0x3c))(); // vtable[0x3c] -> getActiveSubState()
      if (piVar1 != (int *)0x0) {
        uVar3 = (**(code **)(*piVar1 + 0x78))(); // vtable[0x78] -> getSomeData()
        FUN_008a3530(uVar3); // processStateData()
        (**(code **)(*piVar1 + 100))(); // vtable[100] -> updateSubState()
      }
    }
  }
  return;
}
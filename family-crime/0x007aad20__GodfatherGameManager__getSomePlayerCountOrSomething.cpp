// FUNC_NAME: GodfatherGameManager::getSomePlayerCountOrSomething
int GodfatherGameManager::getSomePlayerCountOrSomething(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_012233a0; // global game manager pointer
  iVar3 = 0;
  if (DAT_012233a0 != 0) {
    iVar2 = FUN_0043ff50(); // likely some check (e.g., isGameActive)
    if (iVar2 != 0) {
      if (**(int **)(iVar1 + 4) == 0) { // +0x4: some pointer member
        iVar3 = 0;
      }
      else {
        iVar3 = **(int **)(iVar1 + 4) + -0x1f30; // subtract offset 0x1f30
      }
    }
  }
  if (iVar3 != 0) {
    iVar3 = FUN_0043b870(DAT_01131010); // likely getPlayerManager or similar
    if (iVar3 != 0) {
      return *(int *)(iVar3 + 0x1c) * 4 + 0x10; // +0x1c: some count field, *4 for array stride, +0x10 for base offset
    }
  }
  return 0;
}
// FUNC_NAME: GameStateManager::setState
void __thiscall GameStateManager::setState(int this, undefined4 newState)
{
  int iVar1;
  int *piVar2;
  
  iVar1 = DAT_012234d8;
  if (*(int *)(DAT_012234d8 + 0xc) == 5) {
    *(undefined4 *)(DAT_012234d8 + 0xc) = newState;
    if (*(int *)(iVar1 + 0xc) == 5) {
      *(undefined4 *)(iVar1 + 4) = 5;
    }
    else {
      *(int *)(iVar1 + 4) = *(int *)(iVar1 + 0xc);
    }
  }
  if (DAT_01223484[3] != 0) {
    (**(code **)(*DAT_01223484 + 0x80))();
    piVar2 = DAT_01223484 + 3;
    if ((undefined4 *)DAT_01223484[3] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)DAT_01223484[3])();
      *piVar2 = 0;
    }
  }
  if (*(int *)(this + 0xc) != 0) {
    iVar1 = (**(code **)(**(int **)(this + 0xc) + 8))();
    if (iVar1 == 5) {
      FUN_00568410();
      return;
    }
    if ((*(int *)(this + 0xc) != 0) &&
       (iVar1 = (**(code **)(**(int **)(this + 0xc) + 8))(), iVar1 != 0)) {
      return;
    }
  }
  *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) | 0x400;
  return;
}
// FUNC_NAME: SomeManager::updateActiveEntries
void SomeManager::updateActiveEntries(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x360) != 0) {
    piVar1 = (int *)(param_1 + 8);
    do {
      if (((piVar1[0x17] != 0) && (*piVar1 != 0)) && (piVar1[4] != 0)) {
        FUN_006aac00(piVar1 + -2);
      }
      uVar2 = uVar2 + 1;
      piVar1 = piVar1 + 0x1b;
    } while (uVar2 < *(uint *)(param_1 + 0x360));
  }
  return;
}
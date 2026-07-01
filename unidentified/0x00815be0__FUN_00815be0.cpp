// FUNC_NAME: SomeManager::removeEntry
void __thiscall SomeManager::removeEntry(int this, int param_2)
{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  // Get count from array at offset +8, indexed by (param_2+0x50)*0xc
  uVar1 = *(uint *)(this + 8 + *(int *)(param_2 + 0x50) * 0xc);
  uVar2 = 0;
  if (uVar1 != 0) {
    // Get pointer to array at offset +4, same index
    piVar3 = *(int **)(this + 4 + *(int *)(param_2 + 0x50) * 0xc);
    do {
      if (*piVar3 == param_2) {
        if ((int)uVar2 < 0) {
          return;
        }
        // Found match, call removal function
        FUN_00815a80();
        return;
      }
      uVar2 = uVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (uVar2 < uVar1);
  }
  return;
}
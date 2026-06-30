// FUNC_NAME: SomeClass::removeElementAtIndex
void SomeClass::removeElementAtIndex(int param_1)
{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x22c); // +0x22c: element count
  while (uVar1 = uVar1 - 1, -1 < (int)uVar1) {
    FUN_00565130(); // likely a callback or cleanup function
    uVar2 = *(uint *)(param_1 + 0x22c); // re-read count (may have changed)
    if (uVar1 < uVar2) {
      if (uVar1 < uVar2 - 1) {
        // shift elements down: copy from index uVar2 to index uVar1
        *(undefined4 *)(param_1 + 300 + uVar1 * 4) = *(undefined4 *)(param_1 + 0x128 + uVar2 * 4);
      }
      // decrement element count
      *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + -1;
    }
  }
  return;
}
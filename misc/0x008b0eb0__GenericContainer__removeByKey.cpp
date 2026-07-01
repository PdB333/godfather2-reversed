// FUNC_NAME: GenericContainer::removeByKey
void __thiscall GenericContainer::removeByKey(int this, int key)
{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(uint *)(this + 8) != 0) {
    puVar2 = *(undefined4 **)(this + 4);
    while (key != *(int *)*puVar2) {
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 1;
      if (*(uint *)(this + 8) <= uVar3) {
        return;
      }
    }
    iVar1 = (*(undefined4 **)(this + 4))[uVar3];
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 4) != 0) {
        // Release the value object if it has a reference count
        FUN_009c8f10(*(int *)(iVar1 + 4));
      }
      // Free the key-value pair node
      FUN_009c8eb0(iVar1);
    }
    if (uVar3 != *(int *)(this + 8) - 1U) {
      // Shift the last element into the removed slot
      *(undefined4 *)(*(int *)(this + 4) + uVar3 * 4) =
           *(undefined4 *)(*(int *)(this + 4) + -4 + *(int *)(this + 8) * 4);
    }
    // Decrement the count
    *(int *)(this + 8) = *(int *)(this + 8) + -1;
  }
  return;
}
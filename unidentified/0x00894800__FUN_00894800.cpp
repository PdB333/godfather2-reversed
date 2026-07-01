// FUNC_NAME: SomeContainer::removeByKey
void __thiscall SomeContainer::removeByKey(int param_1, int param_2)
{
  uint count;
  int index;
  uint uVar3;
  int *piVar4;
  
  count = *(uint *)(param_1 + 0x4c); // +0x4c: count of elements
  uVar3 = 0;
  if (count != 0) {
    piVar4 = (int *)(*(int *)(param_1 + 0x48) + 4); // +0x48: pointer to array of pairs (key, value)
    while (*piVar4 != param_2) {
      uVar3 = uVar3 + 1;
      piVar4 = piVar4 + 2; // each pair is 8 bytes (key + value)
      if (count <= uVar3) {
        return;
      }
    }
    if (uVar3 != 0xffffffff) {
      if (uVar3 != count - 1) {
        // Move last element to the removed position
        index = *(int *)(param_1 + 0x48);
        *(undefined4 *)(index + uVar3 * 8) = *(undefined4 *)(index + -8 + count * 8);
        *(undefined4 *)(index + 4 + uVar3 * 8) = *(undefined4 *)(index + -4 + count * 8);
      }
      *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + -1; // decrement count
    }
  }
  return;
}
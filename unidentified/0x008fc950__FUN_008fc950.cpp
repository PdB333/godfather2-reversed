// FUNC_NAME: SomeContainer::removeElement
void __thiscall SomeContainer::removeElement(int param_1, int param_2)
{
  uint count;
  uint index;
  int *elements;
  
  count = *(uint *)(param_1 + 0x24); // +0x24: element count
  index = 0;
  if (count != 0) {
    elements = *(int **)(param_1 + 0x20); // +0x20: pointer to element array
    while (*elements != param_2) {
      index = index + 1;
      elements = elements + 1;
      if (count <= index) {
        return;
      }
    }
    if (-1 < (int)index) {
      if (index != count - 1) {
        // Replace removed element with last element (swap-and-pop)
        *(undefined4 *)(*(int *)(param_1 + 0x20) + index * 4) =
             *(undefined4 *)(*(int *)(param_1 + 0x20) + -4 + count * 4);
      }
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1; // Decrement count
      if (*(int *)(param_1 + 0x1c) == param_2) { // +0x1c: some current/active element pointer
        FUN_008fbcf0(); // Called when removing the active element
        *(undefined4 *)(param_1 + 0x1c) = 0; // Clear active element
      }
    }
  }
  return;
}
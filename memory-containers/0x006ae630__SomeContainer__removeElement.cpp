// FUNC_NAME: SomeContainer::removeElement
void __thiscall SomeContainer::removeElement(int this, int element)
{
  uint count;
  uint index;
  int *elements;
  
  count = *(uint *)(this + 0x19c); // +0x19c: element count
  index = 0;
  if (count != 0) {
    elements = *(int **)(this + 0x198); // +0x198: pointer to element array
    while (*elements != element) {
      index = index + 1;
      elements = elements + 1;
      if (count <= index) {
        return;
      }
    }
    if (-1 < (int)index) {
      if (index != count - 1) {
        // Shift last element into the removed slot
        *(undefined4 *)(*(int *)(this + 0x198) + index * 4) =
             *(undefined4 *)(*(int *)(this + 0x198) + -4 + count * 4);
      }
      // Decrement count
      *(int *)(this + 0x19c) = *(int *)(this + 0x19c) + -1;
    }
  }
  return;
}
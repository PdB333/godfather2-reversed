// FUNC_NAME: SomeContainer::removeElement
void __thiscall SomeContainer::removeElement(int this, int element)
{
  uint count;
  uint index;
  uint foundIndex;
  
  count = *(uint *)(this + 0x7c); // +0x7c: element count
  foundIndex = 0;
  index = 0xffffffff;
  if (count != 0) {
    do {
      index = foundIndex;
      if (*(int *)(this + 0x18 + foundIndex * 4) == element) break; // +0x18: element array start
      foundIndex = foundIndex + 1;
      index = 0xffffffff;
    } while (foundIndex < count);
  }
  if (index < count) {
    if (index < count - 1) {
      do {
        *(undefined4 *)(this + 0x18 + index * 4) = *(undefined4 *)(this + 0x1c + index * 4); // shift elements left
        index = index + 1;
      } while (index < *(int *)(this + 0x7c) - 1U);
    }
    *(int *)(this + 0x7c) = *(int *)(this + 0x7c) + -1; // decrement count
  }
  return;
}
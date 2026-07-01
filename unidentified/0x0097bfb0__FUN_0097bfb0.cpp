// FUNC_NAME: SomeContainer::removeElement
void __thiscall SomeContainer::removeElement(int this, int element)
{
  uint count;
  uint index;
  int *array;
  uint foundIndex;
  
  count = *(uint *)(this + 0xdc); // +0xdc: element count
  index = 0;
  foundIndex = 0xffffffff;
  if (count != 0) {
    array = *(int **)(this + 0xd8); // +0xd8: pointer to element array
    do {
      foundIndex = index;
      if (*array == element) break;
      index = index + 1;
      array = array + 1;
      foundIndex = 0xffffffff;
    } while (index < count);
  }
  // If found and not the last element, move last element to fill the gap
  if (foundIndex != count - 1) {
    *(undefined4 *)(*(int *)(this + 0xd8) + foundIndex * 4) =
         *(undefined4 *)(*(int *)(this + 0xd8) + -4 + count * 4);
  }
  // Decrement count
  *(int *)(this + 0xdc) = *(int *)(this + 0xdc) + -1;
  return;
}
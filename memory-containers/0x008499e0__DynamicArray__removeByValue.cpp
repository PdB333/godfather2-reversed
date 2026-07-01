// FUNC_NAME: DynamicArray::removeByValue
void __thiscall DynamicArray::removeByValue(int this, int value)
{
  uint count = *(uint *)(this + 0x14); // +0x14: element count
  uint index = 0;
  uint foundIndex = 0xffffffff;
  
  if (count != 0) {
    int *elements = *(int **)(this + 0x10); // +0x10: pointer to element array
    do {
      foundIndex = index;
      if (*elements == value) break;
      index = index + 1;
      elements = elements + 1;
      foundIndex = 0xffffffff;
    } while (index < count);
  }
  
  // If found and not the last element, move last element to fill the gap
  if (foundIndex != count - 1) {
    *(int *)(*(int *)(this + 0x10) + foundIndex * 4) =
         *(int *)(*(int *)(this + 0x10) + (count - 1) * 4);
  }
  
  // Decrement count
  *(int *)(this + 0x14) = count - 1;
}
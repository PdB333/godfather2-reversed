// FUNC_NAME: DynamicArray::removeByValue
void __thiscall DynamicArray::removeByValue(int this, int value)
{
  uint count = *(uint *)(this + 0xc); // +0x0C: element count
  uint index = 0;
  uint foundIndex = 0xffffffff;
  
  if (count != 0) {
    int *array = *(int **)(this + 8); // +0x08: pointer to element array
    do {
      foundIndex = index;
      if (array[index] == value) break;
      index = index + 1;
      array = array + 1;
      foundIndex = 0xffffffff;
    } while (index < count);
  }
  
  // If found and not the last element, swap with last element
  if (foundIndex != count - 1) {
    *(int *)(*(int *)(this + 8) + foundIndex * 4) =
         *(int *)(*(int *)(this + 8) + (count - 1) * 4);
  }
  
  // Decrement count
  *(int *)(this + 0xc) = count - 1;
}
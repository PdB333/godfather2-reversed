// FUNC_NAME: SomeManager::removeItem
void __thiscall SomeManager::removeItem(int this, int itemToRemove)
{
  uint index;
  int *arrayPtr;
  uint foundIndex;
  
  index = 0;
  foundIndex = 0xffffffff;
  if (*(uint *)(this + 0x2c80) != 0) {
    arrayPtr = *(int **)(this + 0x2c7c);
    do {
      foundIndex = index;
      if (*arrayPtr == itemToRemove) break;
      index = index + 1;
      arrayPtr = arrayPtr + 1;
      foundIndex = 0xffffffff;
    } while (index < *(uint *)(this + 0x2c80));
  }
  // Clear the "current" or "active" item if it matches the one being removed
  if (*(int *)(this + 0x2c88) == itemToRemove) {
    *(undefined4 *)(this + 0x2c88) = 0;
  }
  // If found and not the last element, replace with the last element (swap-remove)
  if (foundIndex != *(int *)(this + 0x2c80) - 1U) {
    *(undefined4 *)(*(int *)(this + 0x2c7c) + foundIndex * 4) =
         *(undefined4 *)(*(int *)(this + 0x2c7c) + -4 + *(int *)(this + 0x2c80) * 4);
  }
  // Decrement count
  *(int *)(this + 0x2c80) = *(int *)(this + 0x2c80) + -1;
  return;
}
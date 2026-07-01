// FUNC_NAME: SomeContainer::removeByKey
void __thiscall SomeContainer::removeByKey(int this, int key, undefined4 param_3)
{
  uint index;
  int *ptrArray;
  
  index = 0;
  if (*(uint *)(this + 0x1c) != 0) {
    ptrArray = *(int **)(this + 0x18);
    while (*(int *)(*ptrArray + 0xc) != key) {
      index = index + 1;
      ptrArray = ptrArray + 1;
      if (*(uint *)(this + 0x1c) <= index) {
        return;
      }
    }
    if (-1 < (int)index) {
      // Call to remove at index (likely a vector/array erase or element removal)
      FUN_0090d9e0(param_3);
    }
  }
  return;
}
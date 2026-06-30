// FUNC_NAME: DynamicArray::pushBack
int DynamicArray::pushBack(int element)
{
  int *countPtr = (int *)(this + 0xc4);
  int newCount = *(int *)(this + 0xc4) + 1;
  if (*(int *)(this + 200) < newCount) {
    // Reallocate array to accommodate new element (grow by 4 bytes per element)
    *(int *)(this + 0xc0) = FUN_005c27a0(*(int *)(this + 0xc0), newCount, 4, countPtr, this + 200);
  }
  int index = *countPtr;
  *countPtr = index + 1;
  *(int *)(*(int *)(this + 0xc0) + index * 4) = element;
  return *(int *)(this + 0xc4); // Return new count
}
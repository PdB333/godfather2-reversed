// FUNC_NAME: SomeClass::addElementToArray
void __thiscall addElementToArray(int thisPtr, int element)
{
  uint count;
  uint index;
  int newSize;
  int *arrayPtr;

  count = *(uint *)(thisPtr + 0xdc);
  index = 0;
  if (count != 0) {
    arrayPtr = *(int **)(thisPtr + 0xd8);
    do {
      if (*arrayPtr == element) {
        if (-1 < (int)index) {
          return;
        }
        break;
      }
      index = index + 1;
      arrayPtr = arrayPtr + 1;
    } while (index < count);
  }
  index = *(uint *)(thisPtr + 0xe0);
  if (count == index) {
    if (index == 0) {
      newSize = 1;
    }
    else {
      newSize = index * 2;
    }
    reallocateArray(newSize);
  }
  arrayPtr = (int *)(*(int *)(thisPtr + 0xd8) + *(int *)(thisPtr + 0xdc) * 4);
  *(int *)(thisPtr + 0xdc) = *(int *)(thisPtr + 0xdc) + 1;
  if (arrayPtr != (int *)0x0) {
    *arrayPtr = element;
  }
  return;
}
// FUNC_NAME: SomeContainer::addElement
void __thiscall SomeContainer::addElement(int thisPtr, int elementPtr)
{
  int *piVar1;
  int currentSize;
  
  currentSize = *(int *)(thisPtr + 0xc);
  if (*(int *)(thisPtr + 8) == currentSize) {
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    FUN_00849170(currentSize); // likely reallocate/grow internal buffer
  }
  piVar1 = (int *)(*(int *)(thisPtr + 4) + *(int *)(thisPtr + 8) * 4);
  *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 1;
  if (piVar1 != (int *)0x0) {
    *piVar1 = elementPtr;
  }
  FUN_0084a910(*(undefined4 *)(elementPtr + 0x40)); // likely retain/reference count increment
  return;
}
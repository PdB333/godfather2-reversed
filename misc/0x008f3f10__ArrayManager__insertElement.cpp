// FUNC_NAME: ArrayManager::insertElement
undefined4 __thiscall ArrayManager::insertElement(int this, undefined4 element, uint index)
{
  uint currentCount;
  int iVar2;
  int iVar3;
  
  currentCount = *(uint *)(this + 0x2010);
  if (5 < currentCount) {
    return 0;
  }
  if (index != currentCount) {
    // Shift elements down to make room at the specified index
    FUN_008f3530(currentCount * 0x558 + this + -0x558); // Destructor call for element at currentCount-1
    currentCount = *(int *)(this + 0x2010) - 1;
    if (index < currentCount) {
      iVar3 = currentCount * 0x558 + this;
      iVar2 = currentCount - index;
      do {
        FUN_008f3530(iVar3 + -0x558); // Destructor call for element at iVar3-0x558
        iVar3 = iVar3 + -0x558;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    *(int *)(this + 0x2010) = *(int *)(this + 0x2010) + 1;
    FUN_008f3530(element); // Copy constructor call for new element
    return 1;
  }
  // Append at end
  FUN_008f3530(element); // Copy constructor call for new element
  *(int *)(this + 0x2010) = *(int *)(this + 0x2010) + 1;
  return 1;
}
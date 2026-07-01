// FUNC_NAME: SortedArray::insertSorted
void __thiscall SortedArray::insertSorted(int this, int value)
{
  int *elementList;
  int listSize;
  
  listSize = *(int *)(this + 0xc); // +0x0C: number of elements currently stored
  elementList = *(int *)(this + 0x10); // +0x10: capacity
  if (listSize == elementList) {
    if (elementList == 0) {
      elementList = 1;
    }
    else {
      elementList = elementList * 2;
    }
    FUN_0082d130(elementList); // reallocate/grow buffer
  }
  int *elementPtr = (int *)(*(int *)(this + 8) + listSize * 4); // +0x08: pointer to array of ints
  *(int *)(this + 0xc) = listSize + 1;
  if (elementPtr != (int *)0x0) {
    *elementPtr = value;
  }
  if (1 < *(uint *)(this + 0xc)) {
    _qsort(*(void **)(this + 8), *(uint *)(this + 0xc), 4, (_PtFuncCompare *)&LAB_00833690); // comparison function at 0x00833690
  }
  return;
}
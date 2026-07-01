// FUNC_NAME: SortedArray::insert
void __thiscall SortedArray::insert(int this, undefined4 value)
{
  undefined4 *elementPtr;
  int currentSize;
  
  currentSize = *(int *)(this + 0x10); // +0x10: capacity
  if (*(int *)(this + 0xc) == currentSize) { // +0x0c: count
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    FUN_0082b020(currentSize); // reallocate/resize array
  }
  elementPtr = (undefined4 *)(*(int *)(this + 8) + *(int *)(this + 0xc) * 4); // +0x08: data pointer
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1; // increment count
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = value; // store value at end
  }
  if (1 < *(uint *)(this + 0xc)) {
    // Sort the array after insertion if more than 1 element
    _qsort(*(void **)(this + 8), *(uint *)(this + 0xc), 4, (_PtFuncCompare *)&LAB_00833690);
  }
  return;
}
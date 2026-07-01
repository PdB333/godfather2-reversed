// FUNC_NAME: SortedArray::insert
void __thiscall SortedArray::insert(int this, int value)
{
  int *puVar1;
  int iVar2;
  
  iVar2 = *(int *)(this + 0x10); // capacity
  if (*(int *)(this + 0xc) == iVar2) { // size == capacity
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    else {
      iVar2 = iVar2 * 2; // double capacity
    }
    FUN_0082ab90(iVar2); // reallocate array
  }
  puVar1 = (int *)(*(int *)(this + 8) + *(int *)(this + 0xc) * 4); // &data[size]
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1; // size++
  if (puVar1 != (int *)0x0) {
    *puVar1 = value; // append value
  }
  if (1 < *(uint *)(this + 0xc)) { // if more than 1 element
    _qsort(*(void **)(this + 8), *(uint *)(this + 0xc), 4, (_PtFuncCompare *)&LAB_00833690); // sort ascending
  }
  return;
}
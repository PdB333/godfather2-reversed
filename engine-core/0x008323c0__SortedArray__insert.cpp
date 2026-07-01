// FUNC_NAME: SortedArray::insert
void __thiscall SortedArray::insert(int this, undefined4 value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = *(int *)(this + 0x10);
  if (*(int *)(this + 0xc) == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    FUN_0082b370(capacity); // likely reallocate/grow array
  }
  slot = (undefined4 *)(*(int *)(this + 8) + *(int *)(this + 0xc) * 4);
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1; // increment count
  if (slot != (undefined4 *)0x0) {
    *slot = value;
  }
  if (1 < *(uint *)(this + 0xc)) {
    _qsort(*(void **)(this + 8), *(uint *)(this + 0xc), 4, (_PtFuncCompare *)&LAB_00833690); // sort callback
  }
  return;
}
// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int this, undefined4 value)
{
  undefined4 *slot;
  int capacity;
  
  capacity = *(int *)(this + 0x60);
  if (*(int *)(this + 0x5c) == capacity) {
    if (capacity == 0) {
      capacity = 1;
    }
    else {
      capacity = capacity * 2;
    }
    // Reallocate array to new capacity
    FUN_009179f0(capacity);
  }
  // Get pointer to next free slot
  slot = (undefined4 *)(*(int *)(this + 0x58) + *(int *)(this + 0x5c) * 4);
  // Increment element count
  *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + 1;
  if (slot != (undefined4 *)0x0) {
    *slot = value;
  }
  return;
}
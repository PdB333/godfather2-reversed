// FUNC_NAME: DynamicArray::pushBack
undefined4 __thiscall DynamicArray::pushBack(int this, undefined4 value)
{
  undefined4 *elementPtr;
  int newCapacity;
  
  newCapacity = *(int *)(this + 0xc); // capacity
  if (*(int *)(this + 8) == newCapacity) { // size == capacity
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2; // double capacity
    }
    FUN_005fa9a0(newCapacity); // reallocate
  }
  elementPtr = (undefined4 *)(*(int *)(this + 4) + *(int *)(this + 8) * 4); // data + size * 4
  newCapacity = *(int *)(this + 8) + 1; // increment size
  *(int *)(this + 8) = newCapacity;
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = value; // store value at new slot
  }
  return CONCAT31((int3)((uint)newCapacity >> 8),1); // return success flag
}
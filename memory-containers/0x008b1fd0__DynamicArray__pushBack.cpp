// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(int *this, undefined4 value)
{
  undefined4 *elementPtr;
  int currentSize;
  
  currentSize = this[6]; // +0x18: capacity
  if (this[5] == currentSize) { // +0x14: size == capacity
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2;
    }
    // Reallocate array to new capacity
    FUN_00486800(currentSize); // likely realloc or growArray
  }
  elementPtr = (undefined4 *)(this[4] + this[5] * 4); // +0x10: data pointer + size*4
  this[5] = this[5] + 1; // increment size
  if (elementPtr != (undefined4 *)0x0) {
    *elementPtr = value; // store value at new slot
  }
  // Notify observers/listeners (vtable call at offset 0x28)
  (**(code **)(*this + 0x28))(2);
  return;
}
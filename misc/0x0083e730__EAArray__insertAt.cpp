// FUNC_NAME: EAArray::insertAt
int __thiscall EAArray::insertAt(int *this, uint index)
{
  int *elementPtr;
  uint count;
  int newCapacity;
  undefined4 *slotPtr;
  
  newCapacity = this[2];
  if (this[1] == newCapacity) {
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    FUN_004b1440(newCapacity); // likely EAArray::grow or realloc
  }
  elementPtr = (int *)(*this + this[1] * 8);
  if (index != this[1]) {
    if (elementPtr != (int *)0x0) {
      newCapacity = elementPtr[-2];
      *elementPtr = newCapacity;
      elementPtr[1] = 0;
      if (newCapacity != 0) {
        elementPtr[1] = *(int *)(newCapacity + 4);
        *(int **)(newCapacity + 4) = elementPtr;
      }
    }
    count = this[1];
    while (count = count - 1, index < count) {
      elementPtr = (int *)(*this + count * 8);
      if (elementPtr != elementPtr + -2) {
        newCapacity = elementPtr[-2];
        if (*elementPtr != newCapacity) {
          if (*elementPtr != 0) {
            FUN_004daf90(elementPtr); // likely destructor or release
          }
          *elementPtr = newCapacity;
          if (newCapacity != 0) {
            elementPtr[1] = *(int *)(newCapacity + 4);
            *(int **)(newCapacity + 4) = elementPtr;
          }
        }
      }
    }
    this[1] = this[1] + 1;
    newCapacity = index * 8;
    if (*(int *)(*this + newCapacity) != 0) {
      FUN_004daf90(*this + newCapacity); // release existing element
    }
    slotPtr = (undefined4 *)(*this + newCapacity);
    if (slotPtr != (undefined4 *)0x0) {
      *slotPtr = 0;
      slotPtr[1] = 0;
    }
    return *this + newCapacity;
  }
  if (elementPtr != (int *)0x0) {
    *elementPtr = 0;
    elementPtr[1] = 0;
  }
  newCapacity = this[1];
  this[1] = newCapacity + 1;
  return *this + newCapacity * 8;
}
// FUNC_NAME: DynamicArray::insert
undefined4 * __thiscall DynamicArray::insert(DynamicArray *this, uint index)
{
  uint size;
  int newCapacity;
  undefined4 *pSlot;
  
  size = this->size;
  if (this->size == this->capacity) {
    newCapacity = this->capacity;
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    // Resize the internal buffer to newCapacity
    DynamicArray::resize(newCapacity);
  }
  size = this->size;
  pSlot = (undefined4 *)(this->data + size * 8);
  if (index == size) {
    // Append at end
    this->size = size + 1;
    return pSlot;
  }
  // Ensure we have space for shifting (the slot at end is valid)
  if (pSlot != (undefined4 *)0x0) {
    // Copy the last element into the empty slot at end
    *pSlot = *(pSlot - 2);
    pSlot[1] = *(pSlot - 1);
  }
  size = this->size;
  // Shift elements from index to size-1 to the right, starting from the end
  while (size = size - 1, index < size) {
    pSlot = (undefined4 *)(this->data + size * 8);
    *pSlot = *(undefined4 *)(this->data + (size - 1) * 8);
    pSlot[1] = *(undefined4 *)(this->data + (size - 1) * 8 + 4);
  }
  this->size = this->size + 1;
  return (undefined4 *)(this->data + index * 8);
}
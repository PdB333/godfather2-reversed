// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(DynamicArray *this, uint newCapacity)
{
  // Structure layout:
  // +0x00: T* data (pointer to array)
  // +0x04: uint size (number of elements)
  // +0x08: uint capacity (allocated capacity)
  uint oldCapacity = this->capacity;
  if (oldCapacity < newCapacity)
  {
    // Allocate new buffer (each element is 4 bytes)
    T* newData = (T*)malloc(newCapacity * 4);
    if (this->data != 0)
    {
      uint i = 0;
      T* dst = newData;
      if (this->size != 0)
      {
        do {
          if (dst != 0) {
            *dst = this->data[i]; // Copy element
          }
          i++;
          dst++;
        } while (i < this->size);
      }
      free(this->data);
    }
    this->data = newData;
    this->capacity = newCapacity;
  }
  return;
}
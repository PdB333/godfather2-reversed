// FUNC_NAME: DynamicArray::appendElementsAtOffset
int * __thiscall DynamicArray::appendElementsAtOffset(int *this, int sourceData, int sourceOffset, int elementCount)
{
  int oldCount;
  longlong newCapacityLong;
  uint newCapacity;
  void *newData;
  
  oldCount = this[1]; // +0x04 m_count
  if (oldCount != 0) {
    newCapacity = (oldCount + elementCount) * 2;
    if (newCapacity < (uint)this[2]) { // +0x08 m_capacity (stored as element count)
      _memcpy((void *)(*this + oldCount * 2), // +0x00 m_data
              (void *)(sourceData + sourceOffset * 2),
              elementCount * 2);
    }
    else {
      // Need to grow the buffer
      newCapacityLong = (ulonglong)((oldCount + elementCount & 0x7fffffffU) + 1) * 2;
      newData = (void *)FUN_009c8e50(-(uint)((int)((ulonglong)newCapacityLong >> 0x20) != 0) | (uint)newCapacityLong);
      _memcpy(newData, (void *)*this, this[1] * 2);
      _memcpy((void *)((int)newData + this[1] * 2),
              (void *)(sourceData + sourceOffset * 2),
              elementCount * 2);
      if (*this != 0) {
        (*(code *)this[3])(*this); // +0x0C m_deleter function pointer
      }
      *this = (int)newData;
      this[2] = newCapacity; // +0x08 m_capacity
      this[3] = (int)thunk_FUN_009c8eb0; // +0x0C m_deleter set to default free
    }
    this[1] = this[1] + elementCount; // +0x04 m_count
    *(undefined2 *)(*this + this[1] * 2) = 0; // Null-terminate new elements (they are 2-byte types)
    return this;
  }
  // Fallback: handle empty array case via another function
  FUN_004dbb10(sourceData, sourceOffset, elementCount);
  return this;
}
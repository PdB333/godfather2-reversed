// FUNC_NAME: DataChunk::readPropertyField
int DataChunk::readPropertyField(int index)
{
  int *elementPtr;
  int result;
  
  // If index is 0 or negative, get the initial element pointer from buffer start
  if (index < 1) {
    elementPtr = (int *)getInitialElementPtr();                          // FUN_00625430
  }
  else {
    // Compute address of element at index (each element is 8 bytes, stored before +0xC base)
    elementPtr = (int *)(*(int *)(this + 0x0C) + -8 + index * 8);         // base + (index*8 - 8)
    // Check against end pointer at this+0x08
    if (elementPtr <= *(int **)(this + 0x08)) {                            // if past end
      return 0;
    }
  }
  if (elementPtr == (int *)0x0) {
    return 0;
  }
  // If element type is 4 (inline direct value), return data field + 0x10
  if (*elementPtr == 4) {
    return elementPtr[1] + 0x10;
  }
  // Otherwise try to resolve indirect data
  result = resolveIndirectData(this);                                       // FUN_00633990
  if (result != 0) {
    result = elementPtr[1] + 0x10;
  }
  else {
    result = 0;
  }
  // Check if write buffer at this+0x10 is full (writePointer <= readPointer + offset?)
  if (*(unsigned int *)(*(int *)(this + 0x10) + 0x20) <=
      *(unsigned int *)(*(int *)(this + 0x10) + 0x24)) {
    flushWriteBuffer();                                                     // FUN_00627360
  }
  return result;
}
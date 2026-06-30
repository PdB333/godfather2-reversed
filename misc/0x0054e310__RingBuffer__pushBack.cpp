// FUNC_NAME: RingBuffer::pushBack

void __thiscall RingBuffer::pushBack(int this, unsigned int value)
{
  // this points to a structure with fields:
  // +0x14: pointer to ring buffer metadata (likely RingBufferData)
  // RingBufferData layout:
  // +0x70: base pointer to data array (probably int*)
  // +0x74: current write index (number of elements written)
  // +0x78: capacity mask (size-1, e.g. 0x3fffffff for 2^30)
  // FUN_00aa4190 is likely a realloc or buffer resize function

  int *bufferData = *(int **)(this + 0x14);
  if (*(unsigned int *)(bufferData + 0x74) == (*(unsigned int *)(bufferData + 0x78) & 0x3fffffff))
  {
    FUN_00aa4190((int *)(bufferData + 0x70), 4);
  }
  *(unsigned int *)(*(int *)(bufferData + 0x70) + *(int *)(bufferData + 0x74) * 4) = value;
  int *currentWrite = (int *)(bufferData + 0x74);
  *currentWrite = *currentWrite + 1;
}
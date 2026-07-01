// FUNC_NAME: EARS::VectorAllocator::constructor
undefined4 * __thiscall EARS::VectorAllocator::constructor(undefined4 *this, uint elementCount)
{
  uint *allocatedMemory;
  uint adjustedSize;
  uint *elementArray;
  
  adjustedSize = -(uint)((int)((ulonglong)elementCount * 0x114 >> 0x20) != 0) |
                 (uint)((ulonglong)elementCount * 0x114);
  allocatedMemory = (uint *)FUN_009c8e80(-(uint)(0xfffffffb < adjustedSize) | adjustedSize + 4);
  if (allocatedMemory == (uint *)0x0) {
    elementArray = (uint *)0x0;
  }
  else {
    elementArray = allocatedMemory + 1;
    *allocatedMemory = elementCount;
    _vector_constructor_iterator_(elementArray,0x114,elementCount,(_func_void_ptr_void_ptr *)&LAB_00963e20);
  }
  this[1] = elementCount;  // +0x04: capacity
  *this = elementArray;     // +0x00: data pointer
  this[2] = 0;              // +0x08: size (initialized to 0)
  this[3] = 0;              // +0x0C: unknown (maybe flags or padding)
  return this;
}
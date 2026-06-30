// FUNC_NAME: MemoryAllocator::allocateAlignedArray
undefined4 __thiscall MemoryAllocator::allocateAlignedArray(MemoryAllocator *this, int count, int elementSize)
{
  int alignedElementSize;
  int allocatedBlock;
  undefined4 result;
  int originalElementSize; // unaff_EDI
  struct { undefined4 field_0; undefined4 field_4; undefined4 field_8; } allocInfo;
  
  originalElementSize = elementSize;
  // Align element size to multiple of 4 (round up)
  alignedElementSize = elementSize;
  if ((elementSize & 3) != 0) {
    alignedElementSize = (elementSize - (elementSize & 3)) + 4;
  }
  
  // Allocation info structure: likely containing flags/alignment hints
  allocInfo.field_0 = 2;   // +0x00 allocation flags?
  allocInfo.field_4 = 4;   // +0x04 alignment?
  allocInfo.field_8 = 0;   // +0x08 padding?
  
  // Call vtable allocator function at index 0
  // Signature: int allocate(size_t size, void *allocationInfo)
  allocatedBlock = (*(int (**)(int, struct{undefined4;undefined4;undefined4}*))(*(int *)this))(alignedElementSize * count + 0x20, &allocInfo);
  
  if (allocatedBlock != 0) {
    // Initialize the array payload: offset 0x20 for header, size = alignedSize*count, original element size, alignment 4
    result = initializeMemoryArray(allocatedBlock + 0x20, alignedElementSize * count, originalElementSize, 4);
    return result;
  }
  
  return 0;
}
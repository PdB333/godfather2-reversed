// FUNC_NAME: eastl::vector::operator= (copy assignment from initializer list or raw pointer range)
int * __thiscall eastlVectorAssign(int *thisPtr, int *otherData)
{
  int elementCount;
  int *newBuffer;
  int bufferSize;
  
  // Calculate number of elements: each element is 0x50 bytes (80 bytes)
  elementCount = (otherData[1] - *otherData) / 0x50;
  
  // Allocate new buffer if needed
  if (elementCount == 0) {
    newBuffer = (int *)0x0;
  }
  else {
    // Allocate memory: elementCount * 0x50 bytes, with alignment 0x10
    newBuffer = (int *)FUN_0068abc0(elementCount * 0x50, 0x10, 0, "EASTL", 0, 0,
                                     "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xfd);
  }
  
  // Set up the vector structure: begin, end, capacity_end
  *thisPtr = (int)newBuffer;                                          // +0x00: begin
  thisPtr[1] = (int)newBuffer;                                        // +0x04: end
  thisPtr[2] = (int)newBuffer + elementCount * 0x50;                  // +0x08: capacity_end
  
  // Copy elements from other vector range [begin, end) into new buffer
  FUN_00888850(&otherData, *otherData, otherData[1], (int)newBuffer, otherData);
  
  // Update end pointer to reflect the copied data (TODO: verify this logic)
  thisPtr[1] = (int)otherData;  // This seems wrong - should be newBuffer + elementCount * 0x50
  
  return thisPtr;
}
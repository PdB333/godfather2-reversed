// FUNC_NAME: EA::Allocator::constructVectorBuffer
int * __thiscall EA::Allocator::constructVectorBuffer(int *this, int elementCount)
{
  int buffer;
  
  if (elementCount == 0) {
    buffer = 0;
  }
  else {
    // Allocate memory for a vector: elementCount * 0x50 bytes each, alignment 0x10
    buffer = FUN_0068abc0(elementCount * 0x50, 0x10, 0, "EASTL", 0, 0,
                         "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xfd);
  }
  // Set up the vector structure: begin, end, capacity
  this[0] = buffer;       // +0x00: begin pointer
  this[1] = buffer;       // +0x04: end pointer (initially same as begin)
  this[2] = elementCount * 0x50 + buffer; // +0x08: capacity end pointer
  return this;
}
// FUNC_NAME: EARSStreamBuffer::constructor
undefined4 * __fastcall EARSStreamBuffer::constructor(undefined4 *this)
{
  undefined4 *allocResult;
  
  *this = &PTR_FUN_00d73784;  // vtable pointer
  this[1] = 0;                // +0x04: buffer pointer (null initially)
  allocResult = FUN_009c8e80(0x40);  // allocate 64 bytes for buffer
  this[2] = allocResult;      // +0x08: allocated buffer
  this[3] = 0;                // +0x0C: current position/offset
  this[4] = 0x10;             // +0x10: buffer size (16 elements? or 16 bytes?)
  return this;
}
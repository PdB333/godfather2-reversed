// FUNC_NAME: SomeClass::initializeArrayOrSomething
void SomeClass::initializeArrayOrSomething(void)
{
  undefined4 *this = in_EAX;
  void *dst;
  
  this[1] = 0x101;  // +0x04: count/capacity (257 = 0x101)
  *this = 0;        // +0x00: pointer (initialized to null)
  this[2] = 0;      // +0x08: unknown field
  this[3] = 0;      // +0x0C: unknown field
  this[4] = 0;      // +0x10: unknown field
  *(undefined1 *)(this + 5) = 1;  // +0x14: some flag (byte)
  
  // Allocate 0x404 bytes (1028 = 257 * 4)
  dst = (void *)FUN_009c8e80(0x404);
  *this = dst;  // store pointer at +0x00
  
  // Clear the allocated memory
  _memset(dst, 0, this[1] * 4);  // 257 * 4 = 1028 bytes
  
  // Call another initialization function
  FUN_004e0e80();
  
  return;
}
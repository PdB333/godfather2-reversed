// FUNC_NAME: MemoryAllocator::allocateAndZero
void MemoryAllocator::allocateAndZero(void)
{
  void *dst;
  size_t size;
  undefined4 *buffer;
  
  // Call allocator function via vtable pointer at DAT_012234ec + 4
  dst = (void *)(**(code **)**(undefined4 **)(DAT_012234ec + 4))();
  *buffer = dst; // +0x00: store allocated pointer
  _memcpy(dst, (void *)0x0, size); // zero-fill memory (memcpy with NULL source)
  buffer[2] = 0; // +0x08: some flag/count
  buffer[1] = size; // +0x04: store allocation size
  return;
}
// FUNC_NAME: PoolAllocator::free
int __thiscall PoolAllocator::free(void* this, byte freeFlags)
{
  FUN_009fd9b0();
  if ((freeFlags & 1) != 0) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(this, *(unsigned short*)((int)this + 4), 0x2f); // +0x4 = memoryBlockIndex
  }
  return (int)this;
}
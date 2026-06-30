// FUNC_NAME: MemReader::readAligned
void __thiscall MemReader::readAligned(void *destBuffer, size_t size, int alignment)
{
  // +0x18 : current read position (pointer to next byte to read)
  // Align current position up to specified alignment, then read data
  void *src = (void *)(((int)((char *)this + 0x18) + alignment - 1) & ~(alignment - 1));
  *(int *)((char *)this + 0x18) = (int)src;
  _memcpy(destBuffer, src, size);
  // Advance position by size rounded up to 4-byte boundary
  *(int *)((char *)this + 0x18) = *(int *)((char *)this + 0x18) + ((size + 3) & 0xfffffffc);
}
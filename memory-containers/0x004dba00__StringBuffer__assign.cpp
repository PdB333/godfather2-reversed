// FUNC_NAME: StringBuffer::assign
void __thiscall StringBuffer::assign(int *this, void *source, uint length)
{
  longlong lVar1;
  void *dst;
  
  if (length != 0) {
    this[1] = length;               // +0x04: mLength
    this[2] = length * 2;           // +0x08: mCapacity (allocated size)
    lVar1 = (ulonglong)((length & 0x7fffffff) + 1) * 2;
    dst = (void *)FUN_009c8e50(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
    this[0] = (int)dst;             // +0x00: mBuffer
    _memcpy(dst, source, this[1] * 2);
    *(undefined2 *)(this[0] + this[1] * 2) = 0;  // null-terminate (UTF-16)
    this[3] = (int)thunk_FUN_009c8eb0;  // +0x0C: mDeallocator function pointer
    return;
  }
  this[0] = 0;                     // +0x00: mBuffer = null
  this[2] = 0;                     // +0x08: mCapacity = 0
  this[1] = 0;                     // +0x04: mLength = 0
  return;
}
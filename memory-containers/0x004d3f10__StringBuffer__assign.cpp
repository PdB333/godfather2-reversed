// FUNC_NAME: StringBuffer::assign
int * __thiscall StringBuffer::assign(int *this, int src, int offset, uint length)
{
  int iVar1;
  
  if (length != 0) {
    if ((uint)this[2] <= length) {
      if (this[0] != 0) {
        (*(code *)this[3])(this[0]); // free old buffer
      }
      iVar1 = FUN_009c8e50(length + 1); // allocate new buffer
      this[0] = iVar1;
      this[2] = length; // +0x08: capacity
      this[3] = (int)thunk_FUN_009c8eb0; // +0x0C: deallocator function
    }
    _memcpy((void *)this[0], (void *)(src + offset), length);
    *(undefined1 *)(length + this[0]) = 0; // null-terminate
    this[1] = length; // +0x04: current length
    return this;
  }
  this[1] = 0; // +0x04: current length
  if ((undefined1 *)this[0] != (undefined1 *)0x0) {
    *(undefined1 *)this[0] = 0; // set first byte to null
  }
  return this;
}
// FUNC_NAME: EARSString::ensureCapacity
void __thiscall EARSString::ensureCapacity(int *this, uint requiredLength)
{
  void *oldData;
  longlong allocSize;
  uint newCapacity;
  uint doubledRequired;
  void *newData;
  undefined2 *newDataPtr;
  
  doubledRequired = requiredLength * 2;
  if ((uint)this[2] < doubledRequired) {
    oldData = (void *)*this;
    newCapacity = (requiredLength & 0x7fffffff) + 1;
    if (oldData == (void *)0x0) {
      allocSize = (ulonglong)newCapacity * 2;
      newDataPtr = (undefined2 *)
                   FUN_009c8e50(-(uint)((int)((ulonglong)allocSize >> 0x20) != 0) | (uint)allocSize);
      *this = (int)newDataPtr;
      *newDataPtr = 0;
    }
    else {
      allocSize = (ulonglong)newCapacity * 2;
      newData = (void *)FUN_009c8e50(-(uint)((int)((ulonglong)allocSize >> 0x20) != 0) | (uint)allocSize);
      *this = (int)newData;
      _memcpy(newData, oldData, this[1] * 2); // copy existing characters (each 2 bytes)
      *(undefined2 *)(*this + this[1] * 2) = 0; // null terminate
      if (oldData != (void *)0x0) {
        (*(code *)this[3])(oldData); // call deallocator
        this[2] = doubledRequired;
        this[3] = (int)thunk_FUN_009c8eb0;
        return;
      }
    }
    this[3] = (int)thunk_FUN_009c8eb0;
    this[2] = doubledRequired;
  }
  return;
}
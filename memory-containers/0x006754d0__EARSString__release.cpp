// FUNC_NAME: EARSString::release
void EARSString::release(void)
{
  int *stringData;
  int refCount;
  int *thisPtr;
  
  if (this != (int *)0x0) {
    refCount = this[3];
    thisPtr = (int *)*this;
    if (refCount != 0) {
      // Clear the pointer in the string table at offset +0xC using the index from refCount-8
      *(undefined4 *)(*(int *)(thisPtr + 0xc) + *(int *)(refCount + -8) * 4) = 0;
      // Decrement reference count at +0x4
      stringData = (int *)(thisPtr + 4);
      *stringData = *stringData + -1;
      // Free the string data block (offset -0x10 from refCount)
      (*DAT_01206694)(refCount + -0x10);
    }
    refCount = *this;
    // Clear the pointer in the string table at +0xC using the index from this[-2]
    *(undefined4 *)(*(int *)(refCount + 0xc) + this[-2] * 4) = 0;
    // Decrement reference count at +0x4
    stringData = (int *)(refCount + 4);
    *stringData = *stringData + -1;
    // Free the string object itself (offset -0x4 from this)
    (*DAT_01206694)(this + -4);
  }
  return;
}
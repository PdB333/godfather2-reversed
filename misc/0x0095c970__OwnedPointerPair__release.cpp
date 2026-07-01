// FUNC_NAME: OwnedPointerPair::release
void __thiscall OwnedPointerPair::release(int *thisPtr)
{
  // Check if second owned pointer (at +0x10) is non-null
  if (thisPtr[4] != 0) {
    // Call its destructor stored at +0x1C
    ((void (__thiscall *)(int *))thisPtr[7])((int *)thisPtr[4]);
  }
  // Check if first owned pointer (at +0x00) is non-null
  if (*thisPtr != 0) {
    // Call its destructor stored at +0x0C
    ((void (__thiscall *)(int *))thisPtr[3])((int *)*thisPtr);
  }
}
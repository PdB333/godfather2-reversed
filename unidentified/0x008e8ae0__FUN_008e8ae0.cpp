// FUNC_NAME: SomeClass::getSomePointerOrOffset
int __fastcall SomeClass::getSomePointerOrOffset(int *thisPtr)
{
  // Call virtual function at vtable offset 0x15c (87th virtual function)
  (**(code **)(*thisPtr + 0x15c))();

  // Check if field at offset 0x19c (0x67 * 4) is non-zero
  if (thisPtr[0x67] != 0) {
    // Return the value minus 0x48 (72 bytes)
    return thisPtr[0x67] + -0x48;
  }
  return 0;
}
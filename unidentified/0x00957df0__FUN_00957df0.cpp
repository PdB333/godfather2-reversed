// FUNC_NAME: SomeClass::checkAndExecuteVirtualMethod
void __fastcall checkAndExecuteVirtualMethod(int *thisPtr)
{
  // Check if byte at offset +0x4C (0x13 * 4) is non-zero
  // This is likely a flag indicating whether to execute a virtual method
  if ((char)thisPtr[0x13] != '\0') {
    // Call virtual function at vtable offset +0xA0 (method index 40)
    // This is a polymorphic call through the object's vtable
    (**(code **)(*thisPtr + 0xa0))();
    return;
  }
  return;
}
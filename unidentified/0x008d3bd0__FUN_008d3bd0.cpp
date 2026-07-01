// FUNC_NAME: SomeClass::clearFlagOrCallGlobalFunc
void __thiscall FUN_008d3bd0(void* thisPtr)
{
  // Check flag at offset +0x80 (likely a bool or status byte)
  // +0x80: Some flag indicating state/permission
  if (*(char*)((int)thisPtr + 0x80) != '\0') {
    // Call global function with DAT_0112f9d0 as argument (likely a static singleton or manager)
    FUN_004086d0(&DAT_0112f9d0);
    // Clear the flag at offset +0x80
    *(char*)((int)thisPtr + 0x80) = '\0';
  }
  return;
}
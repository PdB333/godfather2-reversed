// FUNC_NAME: SomeClass::incrementRefCount
void __fastcall incrementRefCount(int thisPtr)
{
  // +0x78: reference count field
  *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + 1;
  return;
}
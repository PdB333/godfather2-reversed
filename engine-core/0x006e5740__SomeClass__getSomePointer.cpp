// FUNC_NAME: SomeClass::getSomePointer
int __fastcall getSomePointer(int thisPtr)
{
  if (*(int *)(thisPtr + 0x30c0) != 0) {
    return *(int *)(thisPtr + 0x30c0) + -0x48;
  }
  return 0;
}
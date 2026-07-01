// FUNC_NAME: SomeClass::resetSomeField
void __fastcall SomeClass::resetSomeField(int thisPtr)
{
  // +0x20: some flag/byte field, reset to 0
  *(char *)(thisPtr + 0x20) = 0;
  // +0x1c: some int/float field, reset to 0
  *(int *)(thisPtr + 0x1c) = 0;
  return;
}
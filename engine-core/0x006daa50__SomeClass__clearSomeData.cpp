// FUNC_NAME: SomeClass::clearSomeData
void __fastcall SomeClass::clearSomeData(int thisPtr)
{
  *(undefined4 *)(thisPtr + 0x1c) = 0;
  *(undefined4 *)(thisPtr + 0x18) = 0;
  *(undefined4 *)(thisPtr + 0x14) = 0;
  *(undefined4 *)(thisPtr + 0x10) = 0;
  *(undefined4 *)(thisPtr + 0x2c) = 0;
  *(undefined4 *)(thisPtr + 0x28) = 0;
  *(undefined4 *)(thisPtr + 0x24) = 0;
  *(undefined4 *)(thisPtr + 0x20) = 0;
  return;
}
// FUNC_NAME: SomeClass::clearSomeFields
void __fastcall clearSomeFields(int thisPtr)
{
  *(undefined8 *)(thisPtr + 0x4c) = 0;  // +0x4c: field1 (8 bytes, likely a pointer or double)
  *(undefined8 *)(thisPtr + 0x54) = 0;  // +0x54: field2 (8 bytes)
  *(undefined4 *)(thisPtr + 0x5c) = 0;  // +0x5c: field3 (4 bytes, likely an int or float)
  return;
}
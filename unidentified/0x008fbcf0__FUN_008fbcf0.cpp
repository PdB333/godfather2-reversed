// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int thisPtr)
{
  FUN_004086d0(&DAT_0120e970); // Initialize some global or static data at 0x0120e970
  *(undefined1 *)(thisPtr + 200) = 0; // Clear byte at offset +0xC8 (200 = 0xC8)
  return;
}
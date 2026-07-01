// FUNC_NAME: SomeClass::initializeMembers
void __fastcall SomeClass::initializeMembers(int thisPtr)
{
  FUN_005c1740();
  FUN_005c01d0(&DAT_00d90eb0, thisPtr + 100, 1, 0, 0, 1);  // +0x64: some member
  FUN_005c01d0(&DAT_00d90ea8, thisPtr + 0x50, 1, 0, 0, 1); // +0x50: some member
  FUN_005c01d0(&DAT_00d83f88, thisPtr + 0x10c, 1, &LAB_009867c0, 0, 0); // +0x10c: callback member
  return;
}
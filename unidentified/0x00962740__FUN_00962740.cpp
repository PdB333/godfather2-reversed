// FUNC_NAME: SomeClass::constructor
int __fastcall SomeClass::constructor(int this)
{
  FUN_008a2dd0(0, 3, 0, 0, 0); // Likely initializes some subsystem or memory pool
  *(undefined4 *)(this + 0x50) = 0; // +0x50: some member variable (int)
  *(undefined4 *)(this + 0x54) = 0; // +0x54: some member variable (int)
  *(undefined1 *)(this + 0x58) = 0; // +0x58: some member variable (byte)
  *(undefined1 *)(this + 0x59) = 0; // +0x59: some member variable (byte)
  *(undefined4 *)(this + 0x5c) = 0; // +0x5c: some member variable (int)
  return this;
}
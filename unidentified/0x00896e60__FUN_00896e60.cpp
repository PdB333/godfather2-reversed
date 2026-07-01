// FUNC_NAME: SomeClass::clearSomeFlag
void __fastcall SomeClass::clearSomeFlag(int this)
{
  *(uint *)(this + 0x58) = *(uint *)(this + 0x58) & 0xfffffffd; // Clear bit 1 (0x2) of flags at +0x58
  return;
}
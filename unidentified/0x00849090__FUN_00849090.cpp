// FUNC_NAME: SomeClass::clearFlagBit0
void __fastcall clearFlagBit0(int this)
{
  if ((*(byte *)(this + 0x58) & 1) != 0) {
    *(uint *)(this + 0x58) = *(uint *)(this + 0x58) & 0xfffffffe;
  }
  return;
}
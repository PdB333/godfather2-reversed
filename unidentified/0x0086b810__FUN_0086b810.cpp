// FUNC_NAME: SomeClass::setFlagBit2
void __thiscall SomeClass::setFlagBit2(int this, char enable)
{
  if (enable != '\0') {
    *(ushort *)(this + 200) = *(ushort *)(this + 200) | 4;  // +0xC8: flags field, set bit 2
    return;
  }
  *(ushort *)(this + 200) = *(ushort *)(this + 200) & 0xfffb;  // +0xC8: flags field, clear bit 2
  return;
}
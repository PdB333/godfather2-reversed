// FUNC_NAME: SomeClass::setSomeShortValue
void __thiscall setSomeShortValue(int this, uint value)
{
  // Store the lower 16 bits of value into the lower 16 bits of the field at offset 0x58
  // This preserves the upper 16 bits of the existing field
  *(uint *)(this + 0x58) = *(uint *)(this + 0x58) & 0xffff0000 | value;
  return;
}
// FUNC_NAME: SomeClass::setSomeField
void __thiscall setSomeField(int this, undefined4 value)
{
  // +0x8: some field
  *(undefined4 *)(this + 8) = value;
  return;
}
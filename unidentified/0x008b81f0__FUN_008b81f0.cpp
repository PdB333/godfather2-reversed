// FUNC_NAME: SomeClass::setSomeMember
void __thiscall setSomeMember(int this, undefined4 value)
{
  // +0x0C: some member field
  *(undefined4 *)(this + 0xc) = value;
  return;
}
// FUNC_NAME: SomeClass::setSomeProperty
void __thiscall setSomeProperty(int this, undefined4 value)
{
  // +0x1c: some property field
  *(undefined4 *)(this + 0x1c) = value;
  return;
}
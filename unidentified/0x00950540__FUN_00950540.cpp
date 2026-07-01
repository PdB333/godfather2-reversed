// FUNC_NAME: SomeClass::setSomeField
void __thiscall SomeClass::setSomeField(int this, undefined4 value)
{
  *(undefined4 *)(this + 0x204) = value; // +0x204: some field
  return;
}
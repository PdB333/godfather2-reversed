// FUNC_NAME: SomeClass::setSomeValue
void __thiscall SomeClass::setSomeValue(int this, undefined4 value)
{
  *(undefined4 *)(this + 0x230) = value;  // +0x230: some member variable
  *(undefined4 *)(*(int *)(this + 0x20) + 4) = value;  // dereference pointer at +0x20, write to offset +4
  return;
}
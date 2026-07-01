// FUNC_NAME: SomeClass::setSomeField
void __thiscall SomeClass::setSomeField(int this, undefined4 value)
{
  // +0x58: pointer to some internal data structure
  // +0x24f4: offset within that structure where the value is stored
  *(undefined4 *)(*(int *)(this + 0x58) + 0x24f4) = value;
  return;
}
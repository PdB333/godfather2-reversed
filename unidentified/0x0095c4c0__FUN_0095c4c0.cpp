// FUNC_NAME: SomeClass::getSomeField
void __thiscall getSomeField(int this, undefined4 *outValue)
{
  *outValue = *(undefined4 *)(this + 0xdc); // +0xdc: likely some stored value
  return;
}
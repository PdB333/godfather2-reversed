// FUNC_NAME: SomeClass::resetSomeFields
void __fastcall SomeClass::resetSomeFields(int this)
{
  *(undefined4 *)(this + 8) = 0;  // +0x08: field1
  *(undefined4 *)(this + 0xc) = 0; // +0x0C: field2
  return;
}
// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int this)
{
  *(undefined4 *)(this + 8) = 8;  // +0x08: some member initialized to 8
  *(undefined4 *)(this + 4) = 0;  // +0x04: some member initialized to 0
  return;
}
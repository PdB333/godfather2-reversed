// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int this)
{
  FUN_00612e00(); // likely base class constructor or initialization
  *(undefined4 *)(this + 0xb4) = 0; // +0xB4: some member, e.g., m_someFlag
  *(undefined4 *)(this + 0xb8) = 0; // +0xB8: another member
  *(undefined4 *)(this + 0xbc) = 0; // +0xBC: another member
  return;
}
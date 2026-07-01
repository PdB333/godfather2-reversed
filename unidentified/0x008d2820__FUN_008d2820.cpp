// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  FUN_008d27a0();
  *this = &PTR_FUN_00d7d3ec;
  this[0x12] = 0; // +0x48: some member initialized to 0
  return this;
}
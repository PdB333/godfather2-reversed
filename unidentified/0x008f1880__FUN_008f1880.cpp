// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  DAT_011299b8 = this;
  *this = &PTR_FUN_00d80f30;  // vtable pointer
  this[1] = 0;  // +0x04: some member, likely a pointer or handle
  this[2] = 0;  // +0x08: some member, likely a pointer or handle
  this[3] = 0;  // +0x0C: some member, likely a pointer or handle
  return;
}
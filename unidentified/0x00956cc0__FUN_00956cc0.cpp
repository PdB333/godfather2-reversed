// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d8c1b8; // vtable pointer
  this[4] = &PTR_LAB_00d8c194; // +0x10: some member pointer
  this[0x13] = &PTR_LAB_00d8c190; // +0x4C: some member pointer
  this[0x13] = &PTR_LAB_00d8c18c; // +0x4C: overwritten with another pointer
  DAT_01130020 = 0; // global flag reset
  FUN_005c16e0(); // likely some initialization routine
  return;
}
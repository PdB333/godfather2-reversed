// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)

{
  undefined4 uVar1;
  
  FUN_008334a0();
  uVar1 = _DAT_00d5780c;
  *this = &PTR_FUN_00d734c; // vtable pointer
  this[0x13] = 0; // +0x4C - some field
  this[0x14] = 0; // +0x50
  this[0x15] = 0; // +0x54
  this[0x16] = 0; // +0x58
  this[0x17] = 0; // +0x5C
  this[0x18] = 0; // +0x60
  this[0x19] = uVar1; // +0x64 - stores global value
  return this;
}
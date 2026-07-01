// FUNC_NAME: FUN_0092ffe0
undefined4 * __fastcall FUN_0092ffe0(undefined4 *this)
{
  FUN_005bf9b0();
  *this = &PTR_FUN_00d892e8; // vtable pointer
  this[4] = &PTR_LAB_00d892c0; // +0x10: some pointer
  this[0x13] = 0; // +0x4C: initialize to 0
  this[0x14] = 0; // +0x50: initialize to 0
  this[0x15] = 0; // +0x54: initialize to 0
  this[0x16] = 0; // +0x58: initialize to 0
  this[0x17] = 0; // +0x5C: initialize to 0
  this[0x18] = 0; // +0x60: initialize to 0
  return this;
}
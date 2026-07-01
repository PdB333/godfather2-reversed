// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d69bbc;  // vtable pointer for EARSObject
  this[0xf] = &PTR_LAB_00d69bac;  // +0x3C - some member pointer
  this[0x12] = &PTR_LAB_00d69ba8;  // +0x48 - some member pointer
  FUN_004086d0(&DAT_0120e93c);  // likely some global initialization
  FUN_0046c640();  // likely base class constructor or member init
  return;
}
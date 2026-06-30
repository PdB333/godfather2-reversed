// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  FUN_004737b0();
  *this = &PTR_FUN_00d5f4d4;          // vtable pointer
  this[0xf] = &PTR_LAB_00d5f4c4;      // +0x3C - some function pointer
  this[0x12] = &PTR_LAB_00d5f4c0;     // +0x48 - another function pointer
  this[0x14] = &PTR_LAB_00d5f4bc;     // +0x50 - another function pointer
  this[0x16] = 0;                     // +0x58 - initialize to null
  this[0x17] = 0;                     // +0x5C - initialize to null
  this[0x18] = 0;                     // +0x60 - initialize to null
  this[0x19] = 0;                     // +0x64 - initialize to null
  FUN_006d69c0();                     // sub-object constructor call
  return this;
}
// FUNC_NAME: UnknownClass::constructor
undefined4 * __fastcall UnknownClass_constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  FUN_008334a0();
  uVar1 = _DAT_00d5780c;
  *this = &PTR_LAB_00d73738;
  this[0x13] = uVar1; // +0x4C - store some value at offset 0x4C
  return this;
}
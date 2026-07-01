// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)

{
  undefined1 *puVar1;
  
  FUN_005bf9b0();
  this[0x13] = &PTR_LAB_00d87b68;
  DAT_0112a87c = this;
  *this = &PTR_FUN_00d87b98;
  this[4] = &PTR_LAB_00d87b70;
  this[0x13] = &PTR_LAB_00d87b6c;
  this[0x14] = 0;
  this[0x15] = 0;
  this[0x16] = 0;
  this[0x17] = 0xffffffff;
  this[0x18] = 0;
  this[0x19] = 0;
  this[0x1c] = 0;
  this[0x1e] = 0;
  *(undefined1 *)(this + 0x1f) = 0;
  this[0x14] = this[0x14] | 2;
  puVar1 = (undefined1 *)FUN_009c8e80(0x80);
  this[0x1a] = puVar1;
  *puVar1 = 0;
  puVar1 = (undefined1 *)FUN_009c8e80(0x80);
  this[0x1b] = puVar1;
  *puVar1 = 0;
  return this;
}
// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  FUN_0083f250(0x1afdd13b,0x10);
  this[0x56] = &PTR_LAB_00d741d0; // +0x158: vtable or function pointer
  DAT_0112aff0 = this; // global singleton pointer
  *this = &PTR_FUN_00d741f0; // +0x00: vtable pointer
  this[0xf] = &PTR_LAB_00d741dc; // +0x3C: another vtable or function pointer
  this[0x12] = &PTR_LAB_00d741d8; // +0x48: another vtable or function pointer
  this[0x56] = &PTR_LAB_00d741d4; // +0x158: overwritten with different pointer
  return;
}
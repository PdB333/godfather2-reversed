// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d82768;
  this[0xf] = &PTR_LAB_00d82758;  // +0x3C
  this[0x12] = &PTR_LAB_00d82754;  // +0x48
  this[0x14] = &PTR_LAB_00d82750;  // +0x50
  FUN_004086d0(this + 0x1a);  // +0x68, likely initialize a sub-object
  FUN_00408310(this + 0x1a);  // +0x68, likely set default values for that sub-object
  FUN_009068c0();  // static initialization call
  return;
}
// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *this)
{
  // Set vtable pointer to EARSObject vtable
  *this = &PTR_FUN_00d8c370;
  // Set another vtable or interface pointer at offset +0x10
  this[4] = &PTR_LAB_00d8c34c;
  // Call base class constructor or initialization routine
  FUN_005c16e0();
  return;
}
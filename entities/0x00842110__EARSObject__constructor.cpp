// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  // Call base class constructor
  FUN_00848d00();
  // Call member initialization
  FUN_008420b0();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d74894;
  
  // Set another vtable or interface pointer at offset +0x10
  this[4] = &PTR_LAB_00d74828;
  
  // Initialize fields at offsets +0x180 and +0x184 to 0
  this[0x60] = 0;
  this[0x61] = 0;
  
  return this;
}
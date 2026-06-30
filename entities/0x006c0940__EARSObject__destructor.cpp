// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  *this = &PTR_FUN_00d5ef08;  // vtable pointer
  this[0xf] = &PTR_LAB_00d5eef8;  // +0x3C
  this[0x12] = &PTR_LAB_00d5eef4; // +0x48
  this[0x14] = &PTR_LAB_00d5eef0; // +0x50
  if (this[0x24] != 0) {  // +0x90 - some pointer member
    FUN_004daf90(this + 0x24);  // release/free resource at +0x90
  }
  FUN_00473880();  // base class destructor or cleanup
  return;
}
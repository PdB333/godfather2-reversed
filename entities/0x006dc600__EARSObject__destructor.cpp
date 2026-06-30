// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_FUN_00d5f6a4;
  // Set secondary vtable pointer (likely for another interface)
  this[2] = &PTR_LAB_00d5f69c;
  
  // Destroy child object at offset +0xC8 (0x32 * 4)
  if (this[0x32] != 0) {
    FUN_004daf90(this + 0x32); // likely operator delete or destructor call
  }
  
  // Destroy child object at offset +0xC0 (0x30 * 4)
  if (this[0x30] != 0) {
    FUN_004daf90(this + 0x30); // likely operator delete or destructor call
  }
  
  // Call base class destructor or cleanup function
  FUN_006c9820();
  return;
}
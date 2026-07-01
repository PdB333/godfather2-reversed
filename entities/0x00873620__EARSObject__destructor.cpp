// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
  *this = &PTR_LAB_00d76278;  // Set vtable pointer (likely to base class destructor vtable)
  if (this[0x18] != 0) {      // +0x60: Check if some member pointer is non-null
    FUN_004daf90(this + 0x18); // Release/free resource at offset +0x60
  }
  FUN_0086aff0();             // Call base class destructor or cleanup
  return;
}
// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointers (likely to base class destructor vtables)
  *this = &PTR_FUN_00d8fe88;
  this[4] = &PTR_LAB_00d8fe60;
  this[0x14] = &PTR_LAB_00d8fe5c;
  
  // Release two resources at offsets 0xF8 and 0xFC (0x3E * 4 = 0xF8, 0x3F * 4 = 0xFC)
  FUN_009c8f10(this[0x3e]);
  FUN_009c8f10(this[0x3f]);
  
  // Set more vtable pointers
  this[0x2d] = &PTR_LAB_00d8fe4c;
  this[0x1c] = &PTR_LAB_00d8fe4c;
  
  // Release resource at offset 0x54 if non-null
  if (this[0x15] != 0) {
    FUN_009c8f10(this[0x15]);
  }
  
  // Set final vtable pointer
  this[0x14] = &PTR_LAB_00d8fe58;
  
  // Clear global flag
  DAT_0112fee4 = 0;
  
  // Call cleanup function
  FUN_00957d90();
  
  return;
}
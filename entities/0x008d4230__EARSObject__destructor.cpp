// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(undefined4 *this)
{
  // Set vtable pointer to destructor vtable
  *this = &PTR_FUN_00d7d60c;
  this[0x13] = &PTR_LAB_00d7d5fc;
  
  // Check if some flag at offset 0x81 is set
  if (*(char *)((int)this + 0x81) != '\0') {
    // Call cleanup function with global data
    FUN_004086d0(&DAT_0112f9c0);
    // Clear the flag
    *(undefined1 *)((int)this + 0x81) = 0;
  }
  
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_FUN_00d7d588;
  this[0x13] = &PTR_LAB_00d7d578;
  
  // Call destructors for member objects at offsets +0x58 and +0x68
  FUN_00408310(this + 0x16);  // +0x58
  FUN_00408310(this + 0x1a);  // +0x68
  
  // Call global cleanup functions
  FUN_004083d0();
  FUN_008d2680();
  return;
}
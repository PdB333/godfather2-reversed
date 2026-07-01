// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer to destructor vtable (likely for base class)
  *this = &PTR_FUN_00d7d530;
  // Set another vtable pointer at offset +0x4C (0x13 * 4)
  this[0x13] = &PTR_LAB_00d7d520;
  
  // Check if a flag at offset +0x80 (0x20 * 4) is set
  if (*(char *)(this + 0x20) != '\0') {
    // Call some cleanup function with a global data reference
    FUN_004086d0(&DAT_0112f9d0);
    // Clear the flag
    *(undefined1 *)(this + 0x20) = 0;
  }
  
  // Restore vtable pointers (likely for derived class destructor chain)
  *this = &PTR_FUN_00d7d4d8;
  this[0x13] = &PTR_LAB_00d7d4c8;
  
  // Call destructors for sub-objects at offsets +0x58 (0x16 * 4) and +0x68 (0x1A * 4)
  FUN_00408310(this + 0x16);
  FUN_00408310(this + 0x1a);
  
  // Global cleanup calls
  FUN_004083d0();
  FUN_008d2680();
  
  return;
}
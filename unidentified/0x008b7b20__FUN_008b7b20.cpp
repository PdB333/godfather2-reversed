// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  // Set vtable pointer to first vtable
  *this = &PTR_FUN_00d7b3a4;
  // Set second vtable pointer (likely for multiple inheritance)
  this[1] = &PTR_LAB_00d7b3a0;
  
  // Call some initialization function with a hash/ID
  FUN_004639e0(0x8d946a1b);
  
  // Update second vtable pointer
  this[1] = &PTR_LAB_00d7b39c;
  
  // Set a global flag to 0 (likely initialization complete flag)
  DAT_011299cc = 0;
  
  // Set primary vtable pointer to final vtable
  *this = &PTR_LAB_00e30fe0;
  
  return;
}
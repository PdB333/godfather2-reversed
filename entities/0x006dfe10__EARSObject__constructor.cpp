// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d5f758;
  
  // Initialize member pointers at various offsets
  // +0x3C (0xf * 4)
  this[0xf] = &PTR_LAB_00d5f748;
  // +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d5f744;
  // +0x50 (0x14 * 4)
  this[0x14] = &PTR_LAB_00d5f740;
  
  // Check if a pointer at offset +0x68 (0x1a * 4) is non-null
  if (this[0x1a] != 0) {
    // Call destructor/release function on that pointer
    FUN_004daf90(this + 0x1a);
  }
  
  // Call some initialization function
  FUN_00473880();
  
  return;
}
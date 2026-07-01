// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7d464;
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d7d454;  // +0x3C - some vtable or function pointer
  this[0x12] = &PTR_LAB_00d7d450; // +0x48 - another vtable or function pointer
  
  // If there's an existing object at +0x50, destroy it first
  if (this[0x14] != 0) {          // +0x50 - pointer to sub-object
    FUN_004086d0(this + 0x14);    // destructor call
    FUN_00408310(this + 0x14);    // deallocation
  }
  
  // Call some initialization function
  FUN_0046c640();                 // likely a global or static init
  
  // If flag bit 0 is set, allocate memory for this object
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x80);     // allocate 0x80 bytes for this object
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e32b30;
  
  // Initialize various member pointers at offsets
  this[0xf] = &PTR_LAB_00e32b50;  // +0x3C
  this[0x12] = &PTR_LAB_00e32b60; // +0x48
  this[0x14] = &PTR_LAB_00e32b64; // +0x50
  this[0x14] = &PTR_LAB_00e32854; // +0x50 (overwrites previous)
  
  // Call base class constructor or initialization function
  FUN_0046c640();
  
  // If flag bit 0 is set, call allocation/deallocation function
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x90); // Size 0x90 bytes
  }
  
  return this;
}
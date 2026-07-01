// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable to base class destructor vtable
  *this = &PTR_FUN_00d7bc58;
  this[1] = &PTR_LAB_00d7bc54;
  
  // Log destruction event (hash 0x253131b5)
  FUN_004639e0(0x253131b5);
  
  // Delete child object if it exists (at +0x08)
  if (this[2] != 0) {
    FUN_009c8f10(this[2]); // likely operator delete or destructor call
  }
  
  // Update vtable to final destructor stage
  this[1] = &PTR_LAB_00d7bc50;
  
  // Clear global flag
  DAT_01129908 = 0;
  
  // Set vtable to base class vtable
  *this = &PTR_LAB_00e30fe0;
  
  // If flag bit 0 is set, call operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete
  }
  
  return this;
}
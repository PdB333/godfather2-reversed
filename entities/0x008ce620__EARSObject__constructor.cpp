// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7cae8;
  
  // Initialize member pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d7cad8;  // +0x3C
  this[0x12] = &PTR_LAB_00d7cad4; // +0x48
  
  // Call sub-object constructors
  FUN_004086d0(this + 0x14); // +0x50 sub-object constructor
  FUN_00408310(this + 0x14); // +0x50 sub-object initializer
  
  // Global initialization call
  FUN_0046c640();
  
  // If flag bit 0 is set, call operator delete (size 0x70)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x70);
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d74438;
  
  // Initialize member pointers at offsets +0x3C (0xF * 4) and +0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d74428;  // +0x3C
  this[0x12] = &PTR_LAB_00d74424; // +0x48
  
  // Call base class constructor or initialization function
  FUN_0083f0e0();
  
  // If bit 0 of flags is set, call operator delete with size 0x158
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x158);  // operator delete(this, 0x158)
  }
  
  return this;
}
// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d73570;
  
  // Initialize member pointers at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d73560;  // +0x3C
  this[0x12] = &PTR_LAB_00d7355c; // +0x48
  
  // Check global flag for additional initialization
  if (DAT_0112db84 != 0) {
    FUN_00835410(this);  // Likely some engine-specific initialization
  }
  
  // Call base class or utility initialization
  FUN_0046c640();
  
  // If flag bit 0 is set, delete this object (size 0x54)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x54);  // operator delete with size
  }
  
  return this;
}
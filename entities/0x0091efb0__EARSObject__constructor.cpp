// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to EARSObject vtable
  *this = &PTR_FUN_00d85ee0;
  
  // Set additional vtable-like pointers
  this[4] = &PTR_LAB_00d85eb8;
  this[0x13] = &PTR_LAB_00d85eb4;
  this[0x13] = &PTR_LAB_00d85d7c;
  
  // Reset global singleton flag
  DAT_0112a9cc = 0;
  
  // Call base class or initialization function
  FUN_005c16e0();
  
  // If flag bit 0 is set, call destructor (placement new cleanup)
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
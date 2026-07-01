// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to base class vtable
  *this = &PTR_FUN_00d70288;
  this[1] = &PTR_LAB_00d70278;
  
  // Call base class constructor
  FUN_0043b400();
  
  // Set vtable to derived class vtable
  *this = &PTR_LAB_00d70274;
  
  // Initialize static global flag
  DAT_0112bb50 = 0;
  
  // If flag bit 0 is set, call placement delete (size 0x74)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x74);
  }
  
  return this;
}
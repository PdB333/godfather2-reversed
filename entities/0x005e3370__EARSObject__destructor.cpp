// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  // Set vtable to first destructor vtable
  *this = &PTR_FUN_00e3f50c;
  
  // If the child object pointer is non-null, call its destructor
  if ((int *)this[1] != (int *)0x0) {
    (**(code **)(*(int *)this[1] + 0xc))();
  }
  
  // Set vtable to second destructor vtable (base class)
  *this = &PTR_LAB_00e3f510;
  
  // Clear global flag
  DAT_01223518 = 0;
  
  // If flags bit 0 is set, free the memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete
  }
  
  return this;
}
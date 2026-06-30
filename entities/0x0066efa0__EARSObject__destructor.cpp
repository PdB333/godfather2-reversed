// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  // Set vtable pointer (destructor step)
  *this = &PTR_FUN_00e444d0;
  
  // If the object has a child object at offset +0xA1C (0x287 * 4), call its destructor
  // +0xA1C: pointer to child object (likely a sub-component or derived object)
  if ((int *)this[0x287] != (int *)0x0) {
    (**(code **)(*(int *)this[0x287] + 0xc))();  // Call vtable[3] (destructor) on child
  }
  
  // Call base class destructor or cleanup function
  FUN_00aa1900();
  
  // If the 'delete' flag is set (bit 0), free the memory
  if ((flags & 1) != 0) {
    (*(code *)PTR___aligned_free_00ef3e60)(this);
  }
  
  return this;
}
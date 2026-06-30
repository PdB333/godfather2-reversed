// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_LAB_00d996b0;
  
  // Call base class destructor
  SomeBaseClass::destructor();
  
  // If the object was allocated with 'new' (bit 0 set), free the memory
  if ((flags & 1) != 0) {
    __aligned_free(this);
  }
  
  return this;
}
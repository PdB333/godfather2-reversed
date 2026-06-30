// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e3f2c8;
  
  // Call base class constructor
  SomeBaseClass::constructor();
  
  // If the flags indicate we should delete this, call destructor
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
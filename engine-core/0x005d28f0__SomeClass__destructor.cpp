// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e3edd4;
  
  // If the 5th field (offset +0x10) is non-zero, call a cleanup function
  if (this[4] != 0) {
    SomeClass::cleanup();
  }
  
  // If the low bit of flags is set, free the memory via operator delete
  if ((flags & 1) != 0) {
    operatorDelete(this);
  }
  
  return this;
}
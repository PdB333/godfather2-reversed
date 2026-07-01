// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor or initialization function
  FUN_00792c50();
  
  // If the flags parameter has bit 0 set, call the destructor or cleanup function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
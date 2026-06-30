// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor or initialization function
  SomeClass::baseInit(this);
  
  // If the low bit of flags is set, call the destructor or cleanup function
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
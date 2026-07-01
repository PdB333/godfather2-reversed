// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor or initialization function
  FUN_0080d4f0();
  
  // If the first bit of flags is set, call the destructor? (operator delete?)
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return (undefined4)this;
}
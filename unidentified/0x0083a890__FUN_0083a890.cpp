// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor or initialization function
  SomeClass::baseConstructor(this);
  
  // If the flags parameter has bit 0 set, call the destructor
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return (undefined4)this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor or initialization function
  SomeClass::init(this);
  
  // If the flags parameter has bit 0 set, call the destructor/deallocation function
  if ((flags & 1) != 0) {
    SomeClass::operatorDelete(this);
  }
  
  return (undefined4)this;
}
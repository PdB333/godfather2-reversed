// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor
  SomeBaseClass::constructor();
  
  // If the flags parameter has bit 0 set, call the destructor
  // This is a common pattern for placement new / operator delete
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
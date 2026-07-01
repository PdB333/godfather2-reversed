// FUNC_NAME: SomeEAObject::constructor
undefined4 __thiscall SomeEAObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x007788e0
  SomeBaseClass::constructor();
  
  // If bit 0 of flags is set, call destructor-like cleanup at 0x00624da0
  if ((flags & 1) != 0) {
    SomeEAObject::destructor(this);  // likely operator delete or free
  }
  
  return this;
}
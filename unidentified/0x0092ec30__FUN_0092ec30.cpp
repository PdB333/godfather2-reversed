// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x0092dce0
  SomeClass::baseConstructor(this);
  
  // If the low bit of flags is set, call destructor at 0x005c4480
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return (undefined4)this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x98e470
  BaseClass::constructor(this);
  
  // If the low bit of flags is set, call the destructor at 0x5c4480
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
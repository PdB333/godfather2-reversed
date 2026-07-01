// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00897de0
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call destructor at 0x009c8eb0
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0076ea40
  BaseClass::constructor();
  
  // If the low bit of flags is set, call the destructor at 0x00624da0
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
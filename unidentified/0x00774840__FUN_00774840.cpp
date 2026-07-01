// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x00774030
  BaseClass::constructor(this);
  
  // If the low bit of flags is set, call the destructor (placement delete) at 0x00624da0
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
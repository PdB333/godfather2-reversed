// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008169b0
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call destructor at 0x009c8eb0
  // This pattern is typical for placement new with cleanup on failure
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);
  }
  
  return this;
}
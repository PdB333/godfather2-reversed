// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor or initialization function
  FUN_0056a0a0();
  
  // If the low bit of flags is set, call a cleanup/destructor-like function
  // This pattern is common for placement new or conditional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
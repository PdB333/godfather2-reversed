// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0077b650
  FUN_0077b650();
  
  // If the low bit of flags is set, call a cleanup/destructor-like function
  // This pattern is typical for placement new or conditional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
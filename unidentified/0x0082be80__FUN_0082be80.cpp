// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0082a9d0
  FUN_0082a9d0();
  
  // If the low bit of flags is set, call a destructor-like function at 0x009c8eb0
  // This pattern is typical for placement new / operator delete handling
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
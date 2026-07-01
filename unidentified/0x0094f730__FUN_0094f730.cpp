// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0094f6b0
  FUN_0094f6b0();
  
  // If the low bit of flags is set, call a destructor-like function
  // This pattern is typical for placement new / operator delete handling
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
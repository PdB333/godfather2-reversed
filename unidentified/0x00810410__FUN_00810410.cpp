// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00810000
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call destructor-like cleanup at 0x009c8eb0
  // This pattern is typical for placement new / operator delete handling
  if ((flags & 1) != 0) {
    SomeClass::destructor(this);  // FUN_009c8eb0 likely a destructor or deallocation
  }
  
  return this;
}
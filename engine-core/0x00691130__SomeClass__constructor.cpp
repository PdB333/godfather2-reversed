// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x4083d0
  BaseClass::constructor();
  
  // If the low bit of flags is set, call a destructor-like cleanup function
  // This pattern is typical for placement new / operator delete handling
  if ((flags & 1) != 0) {
    SomeClass::destructor(this); // 0x9c8eb0
  }
  
  return this;
}
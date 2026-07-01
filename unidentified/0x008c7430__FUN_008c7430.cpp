// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)

{
  // Call parent/base class constructor
  FUN_008c7060();
  
  // If the low bit of flags is set, call destructor-related function
  // This pattern is typical of placement new with a cleanup function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
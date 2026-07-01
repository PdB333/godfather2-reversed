// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00909d50
  FUN_00909d50();
  
  // If the low bit of flags is set, call operator delete with size 0xD4
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xd4); // operator delete(this, 0xD4)
  }
  
  return this;
}
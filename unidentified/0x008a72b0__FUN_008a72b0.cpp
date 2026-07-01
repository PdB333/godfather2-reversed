// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008a70e0
  FUN_008a70e0();
  
  // If bit 0 of flags is set, call operator delete with size 0x98
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x98); // operator delete(this, 0x98)
  }
  
  return this;
}
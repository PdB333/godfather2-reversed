// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008fde20
  FUN_008fde20();
  
  // If the low bit of flags is set, call operator delete with size 0xe4
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xe4);
  }
  
  return this;
}
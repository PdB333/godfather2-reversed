// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x008bb8d0
  FUN_008bb8d0(this);
  
  // If bit 0 of flags is set, call operator delete with size 0x2b0
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x2b0);
  }
  
  return this;
}
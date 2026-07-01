// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0082ba50
  FUN_0082ba50();
  
  // If the low bit of flags is set, call another initialization function
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
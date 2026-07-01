// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x007d00e0
  FUN_007d00e0();
  
  // If the low bit of flags is set, call a destructor-like function at 0x00624da0
  // This is likely a placement new / conditional cleanup pattern
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}
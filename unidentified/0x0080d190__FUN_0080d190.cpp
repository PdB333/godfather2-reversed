// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0080c9c0
  FUN_0080c9c0();
  
  // If the low bit of flags is set, call the destructor at 0x00624da0
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}
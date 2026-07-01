// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall UnknownClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00915f40
  FUN_00915f40();
  
  // If bit 0 of flags is set, call destructor at 0x005c4480
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
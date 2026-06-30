// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall UnknownClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x006a9410
  FUN_006a9410();
  
  // If bit 0 of flags is set, call operator delete with size 0xec
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0xec);
  }
  
  return this;
}
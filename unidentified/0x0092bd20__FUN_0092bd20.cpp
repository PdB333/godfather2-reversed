// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0092a830
  FUN_0092a830();
  
  // If bit 0 of flags is set, call destructor at 0x005c4480
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
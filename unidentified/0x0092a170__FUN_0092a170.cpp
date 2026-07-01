// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x00929ea0
  FUN_00929ea0(this);
  
  // If the low bit of flags is set, call the destructor at 0x005c4480
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
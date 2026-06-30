// FUNC_NAME: SomeEARSObject::constructor
undefined4 __thiscall SomeEARSObject::constructor(SomeEARSObject *this, byte flags)
{
  // Calls base class constructor at 0x00581a70
  FUN_00581a70();
  
  // If flag bit 0 is set, call another initialization function (likely destructor cleanup)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return (undefined4)this;
}
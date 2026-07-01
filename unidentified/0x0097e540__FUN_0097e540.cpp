// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x0097dd40
  BaseClass::constructor();
  
  // If the low bit of flags is set, call additional initialization at 0x009c8eb0
  if ((flags & 1) != 0) {
    SomeClass::additionalInit(this);
  }
  
  return (undefined4)this;
}
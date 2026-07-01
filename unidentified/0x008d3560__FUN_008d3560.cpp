// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008d32e0
  FUN_008d32e0();
  
  // If bit 0 of flags is set, call destructor at 0x009c8eb0
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
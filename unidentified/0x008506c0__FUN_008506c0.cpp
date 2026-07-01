// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00850450
  BaseClass::constructor();
  
  // If bit 0 of flags is set, call operator delete with size 0xAC (172 bytes)
  if ((flags & 1) != 0) {
    operatorDelete(this, 0xac);
  }
  
  return this;
}
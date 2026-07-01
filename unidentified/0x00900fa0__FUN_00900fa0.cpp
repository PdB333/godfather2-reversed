// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00900a70
  BaseClass::constructor();
  
  // If the low bit of flags is set, allocate additional memory (0x1e0 bytes)
  if ((flags & 1) != 0) {
    operatorNew(this, 0x1e0); // +0x1e0 allocation
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x008d0800
  BaseClass::constructor(this);
  
  // If bit 0 of flags is set, allocate additional memory (0xA0 bytes)
  if ((flags & 1) != 0) {
    operatorNew(this, 0xa0);  // FUN_0043b960 - likely operator new or placement new
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)

{
  // Call base class constructor at 0x008e3ba0
  BaseClass::constructor(this);
  
  // If bit 0 of flags is set, call operator delete with size 0x240
  if ((flags & 1) != 0) {
    operatorDelete(this, 0x240);
  }
  
  return this;
}
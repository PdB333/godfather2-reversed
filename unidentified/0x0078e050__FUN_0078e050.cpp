// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x0078df40
  SomeBaseClass::constructor(this);
  
  // If bit 0 of flags is set, call operator delete with size 0x18c
  if ((flags & 1) != 0) {
    operatorDelete(this, 0x18c);
  }
  
  return (undefined4)this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)

{
  // Call base class constructor at 0x007c3fc0
  SomeBaseClass::constructor(this);
  
  // If the low bit of flags is set, call a destructor-like function (operator delete?)
  if ((flags & 1) != 0) {
    operatorDelete(this); // 0x00624da0 - likely operator delete or destructor
  }
  
  return this;
}
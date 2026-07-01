// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0088e730
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call operator delete with size 0x88
  if ((flags & 1) != 0) {
    operatorDelete(this, 0x88);
  }
  
  return this;
}
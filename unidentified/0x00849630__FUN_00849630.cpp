// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008494c0
  SomeBaseClass::constructor();
  
  // If the low bit of flags is set, call operator delete (or destructor) with size 0xB8
  if ((flags & 1) != 0) {
    operatorDelete(this, 0xb8); // 0x0043b960 - likely operator delete or placement delete
  }
  
  return this;
}
// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte param_2)

{
  // Call base class (or member) constructor
  FUN_005ea790();
  
  // If the destructor flag (bit 0) is set, call operator delete
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
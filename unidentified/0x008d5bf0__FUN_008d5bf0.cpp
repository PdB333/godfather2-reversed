// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte param_2)

{
  // Call base class constructor at 0x008d5750
  BaseClass::constructor();
  
  // If the low bit of param_2 is set, call operator delete with size 0xAC
  if ((param_2 & 1) != 0) {
    operatorDelete(this, 0xac);
  }
  return this;
}
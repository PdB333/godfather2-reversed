// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte param_2)

{
  // Call base class constructor at 0x008e13f0
  SomeBaseClass::constructor();
  
  // If bit 0 of param_2 is set, allocate or initialize something at offset 0x1fc
  if ((param_2 & 1) != 0) {
    SomeClass::initSomething(this, 0x1fc);
  }
  
  return this;
}
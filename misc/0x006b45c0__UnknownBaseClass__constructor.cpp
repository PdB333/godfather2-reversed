// FUNC_NAME: UnknownBaseClass::constructor
undefined4 __thiscall UnknownBaseClass_constructor(undefined4 this, byte param_2)

{
  // Call base constructor
  FUN_006b3930();
  
  // If the lowest bit of the parameter is set, call the virtual destructor cleanup
  // This is a pattern often used for placement new / constructor chaining
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete or destructor cleanup
  }
  
  return this;
}
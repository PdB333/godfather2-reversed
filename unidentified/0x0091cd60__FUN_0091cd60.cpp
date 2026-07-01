// FUNC_NAME: someClass::constructor
undefined4 __thiscall someClass::constructor(undefined4 this, byte param_2)

{
  // Call base class constructor or common initialization
  FUN_0091a7e0();
  
  // If the low bit of param_2 is set, call destructor? 
  // Or maybe it's an allocation flag that controls cleanup
  if ((param_2 & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
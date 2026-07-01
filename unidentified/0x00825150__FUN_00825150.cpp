// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, int param_2)

{
  // Call base class constructor at 0x0081f9f0
  FUN_0081f9f0(param_2);
  
  // Set vtable pointer (LAB_00d73448)
  *this = &PTR_LAB_00d73448;
  
  // Copy value from param_2 + 0x4c to this + 0x4c (offset 0x4c)
  this[0x13] = *(undefined4 *)(param_2 + 0x4c);
  
  return this;
}
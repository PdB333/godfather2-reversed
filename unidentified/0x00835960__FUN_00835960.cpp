// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  // Call base class constructor at 0x414970
  FUN_00414970(param_2, param_3);
  
  // Set vtable pointer to PTR_FUN_00d73b40
  *this = &PTR_FUN_00d73b40;
  
  return this;
}
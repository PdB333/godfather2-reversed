// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  // Set vtable pointer (likely to SomeClass vtable)
  *this = &PTR_FUN_00d91dac;
  
  // Call base class constructor or initialization function
  FUN_004de130();
  
  // If the flag bit is set, call a cleanup/destructor-like function
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
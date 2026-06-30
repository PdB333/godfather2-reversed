// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  // Call base class constructor or initialization function
  FUN_00414970(param_2, param_3);
  
  // Set vtable pointer to the class's virtual function table
  *this = &PTR_FUN_00d5fc10;
  
  // Initialize a byte field at offset +0xC (3 * 4 bytes = 12 bytes from this)
  *(undefined1 *)(this + 3) = 0;
  
  return this;
}
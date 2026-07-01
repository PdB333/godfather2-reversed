// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)
{
  *this = &PTR_FUN_00d85e48;  // vtable pointer assignment
  this[4] = &PTR_LAB_00d85e24; // member field offset +0x10
  this[0x13] = &PTR_LAB_00d85e20; // member field offset +0x4C
  this[0x13] = &PTR_LAB_00d85d78; // member field offset +0x4C (overwritten)
  DAT_0112fc8c = 0; // global variable initialization
  FUN_005c16e0(); // base class or static initialization
  if ((param_2 & 1) != 0) {
    FUN_005c4480(this); // deallocation or cleanup handler
  }
  return this;
}
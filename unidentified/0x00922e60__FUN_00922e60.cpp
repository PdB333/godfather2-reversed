// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointers (likely for base class and derived class)
  *this = &PTR_FUN_00d866a4;  // vtable pointer for base class
  this[1] = &PTR_LAB_00d86694; // secondary vtable or interface pointer

  // Call some initialization function with a magic constant (0xc914145c)
  FUN_004639e0(0xc914145c);

  // Update vtable pointers after initialization
  this[1] = &PTR_LAB_00e30fe0;
  *this = &PTR_LAB_00d86690;

  // Reset a global variable
  DAT_0113001c = 0;

  // If the low bit of flags is set, call destructor-like cleanup
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}
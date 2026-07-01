// FUNC_NAME: SomeEARSObject::constructor
undefined4 * __thiscall SomeEARSObject::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_LAB_00d76090;  // Set vtable pointer
  FUN_0086aff0();              // Base class constructor or initialization
  if ((param_2 & 1) != 0) {   // Check if bit 0 is set (likely a flag for allocation)
    FUN_00624da0(this);        // Deallocation or cleanup function
  }
  return this;
}
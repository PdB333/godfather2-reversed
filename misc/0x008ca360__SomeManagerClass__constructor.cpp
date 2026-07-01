// FUNC_NAME: SomeManagerClass::constructor
undefined4 * __thiscall SomeManagerClass::constructor(undefined4 *this, byte param_2)
{
  *this = &PTR_FUN_00d7bf40;
  // Call base class constructor
  FUN_008ca0d0();

  // Check if there is an existing pointer to clean up
  if (this[1] != 0) {
    // Delete/release pointer at offset +0x4
    FUN_009c8f10(this[1]);
  }

  // Set vtable to an alternative function table
  *this = &PTR_LAB_00d7bf3c;

  // Reset a global flag/variable
  DAT_01129990 = 0;

  // If parameter param_2 has bit 0 set, call destructor
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
    // Note: 'this' is returned after possible deletion, so caller gets the same pointer
  }

  return this;
}
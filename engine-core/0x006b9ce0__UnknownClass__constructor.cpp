// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass_constructor(undefined4 *this, byte param_2)
{
  // Set virtual function table pointer
  *this = &PTR_FUN_00d5e668;
  // Initialize fields at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d5e658; // +0x3C
  this[0x12] = &PTR_LAB_00d5e654; // +0x48

  // Call initialization functions on a sub-object at offset +0x98
  FUN_004086d0(this + 0x26); // +0x98
  FUN_00408310(this + 0x26); // +0x98

  // Global initialization call
  FUN_006bcd70();

  // If param_2 bit 0 is set, allocate memory (possibly for placement new)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0xc0); // size 0xC0 = 192 bytes
  }

  return this;
}
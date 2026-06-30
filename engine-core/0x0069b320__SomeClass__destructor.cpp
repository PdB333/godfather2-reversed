// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable to first destructor vtable
  *this = &PTR_FUN_00d5cec4;
  
  // If member at +0x3C (offset 0xF * 4) is non-null, call its destructor via vtable at +0x48 (offset 0x12 * 4)
  if (this[0xf] != 0) {
    (*(code *)this[0x12])(this[0xf]);
  }
  
  // If member at +0x2C (offset 0xB * 4) is non-null, call its destructor via vtable at +0x38 (offset 0xE * 4)
  if (this[0xb] != 0) {
    (*(code *)this[0xe])(this[0xb]);
  }
  
  // Set vtable to second destructor vtable
  *this = &PTR_FUN_00d5ce9c;
  
  // Call destructor for member at +0x14 (offset 5 * 4)
  FUN_0069a0e0(this[5]);
  
  // If flags bit 0 is set, deallocate memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
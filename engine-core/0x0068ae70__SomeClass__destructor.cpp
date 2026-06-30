// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Check if pointer at +0x18 (param_1[6]) is non-null and call its destructor via vtable at +0x24 (param_1[9])
  if (this[6] != 0) {
    (*(code *)this[9])(this[6]);
  }
  // Check if pointer at +0x08 (param_1[2]) is non-null and call its destructor via vtable at +0x14 (param_1[5])
  if (this[2] != 0) {
    (*(code *)this[5])(this[2]);
  }
  // Set vtable pointer to base class destructor (likely a static vtable for destroyed state)
  *this = &PTR_LAB_00d576d4;
  // If flags bit 0 is set, call operator delete (FUN_009c8eb0 is likely operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}
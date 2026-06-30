// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Check if the callback function pointer at offset +0x2C (0xB * 4) is non-null
  if (this[0xb] != 0) {
    // Call the callback function at offset +0x38 (0xE * 4) with the callback data as argument
    (*(code *)this[0xe])(this[0xb]);
  }
  // Set vtable pointer to the base class vtable (PTR_FUN_00d5ce9c)
  *this = &PTR_FUN_00d5ce9c;
  // Call destructor on the object at offset +0x14 (0x5 * 4)
  FUN_0069a0e0(this[5]);
  return;
}
// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte allocFlag)
{
  // Set vtable pointer at offset 0x00
  *this = &PTR_FUN_00d81254;
  // Set secondary vtable pointer at offset 0x3C (0xF * 4)
  this[0xF] = &PTR_LAB_00d81244;
  // Set tertiary vtable pointer at offset 0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d81240;

  // Call base class constructor
  BaseClass::BaseClass();

  // If the object was heap-allocated (allocFlag & 1), call cleanup/destructor
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x5c); // Likely operator delete or destructor with size
  }

  return this;
}
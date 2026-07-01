// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d8c370;
  // Set another vtable or interface pointer at offset +0x10
  this[4] = &PTR_LAB_00d8c34c;
  
  // Call base class constructor or initialization
  FUN_005c16e0();
  
  // If flag bit 0 is set, call additional initialization
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}
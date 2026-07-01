// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d69b04;
  this[0xf] = &PTR_LAB_00d69af4;
  this[0x12] = &PTR_LAB_00d69af0;
  // Call base class constructor or member initialization at offset +0x50 (0x14 * 4)
  FUN_004086d0(this + 0x14);
  // Call some global initialization function
  FUN_0046c640();
  // If param_2 bit 0 is set, call a cleanup/deallocation function (likely operator delete)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x78);
  }
  return this;
}
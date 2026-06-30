// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param2)
{
  *this = &PTR_FUN_00d5899c; // vtable pointer
  this[0xf] = &PTR_LAB_00d5898c; // offset +0x3C
  this[0x12] = &PTR_LAB_00d58988; // offset +0x48
  FUN_008b2820(); // base class constructor or initialization
  if ((param2 & 1) != 0) {
    FUN_0043b960(this,0x68); // operator delete or cleanup with size 0x68
  }
  return this;
}
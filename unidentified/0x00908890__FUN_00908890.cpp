// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d83028;
  this[3] = &PTR_LAB_00d83024;
  this[4] = &PTR_LAB_00d83014;
  FUN_00907f20();
  this[4] = &PTR_LAB_00e30fe0;
  this[3] = &PTR_LAB_00d83010;
  DAT_0112ff6c = 0;
  FUN_004083d0();
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}
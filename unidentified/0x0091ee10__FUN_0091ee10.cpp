// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d85db8;
  this[4] = &PTR_LAB_00d85d90;
  this[0x13] = &PTR_LAB_00d85d8c;
  this[0x13] = &PTR_LAB_00d85d74;
  DAT_0112a9d0 = 0;
  FUN_005c16e0();
  if ((param_2 & 1) != 0) {
    FUN_005c4480(this);
  }
  return this;
}
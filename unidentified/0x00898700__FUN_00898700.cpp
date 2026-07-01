// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d77b78;
  this[0xf] = &PTR_LAB_00d77b68;
  this[0x12] = &PTR_LAB_00d77b64;
  this[0x14] = &PTR_LAB_00d77b00;
  FUN_008b5040();
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this,0x1bc);
  }
  return this;
}
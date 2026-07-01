// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d72f04;
  this[0xf] = &PTR_LAB_00d72ef4;
  this[0x12] = &PTR_LAB_00d72ef0;
  FUN_004086d0(this + 0x14);
  FUN_00408310(this + 0x14);
  FUN_0046c640();
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this,0x5c);
  }
  return this;
}
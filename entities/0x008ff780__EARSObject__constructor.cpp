// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d816e0;
  this[0xf] = &PTR_LAB_00d816d0;
  this[0x12] = &PTR_LAB_00d816cc;
  FUN_004086d0(this + 0x16);
  FUN_00408310(this + 0x16);
  FUN_00408310(this + 0x18);
  FUN_00408310(this + 0x1a);
  FUN_0046c640();
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this,0x70);
  }
  return this;
}
// FUNC_NAME: DonControlGadget::operator new(uint)
undefined4 * __thiscall DonControlGadget_constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d79a94;
  this[0xf] = &PTR_LAB_00d79a84;
  this[0x12] = &PTR_LAB_00d79a80;
  FUN_00408310(this + 0x18);
  FUN_008a1380();
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this,0x6c);
  }
  return this;
}
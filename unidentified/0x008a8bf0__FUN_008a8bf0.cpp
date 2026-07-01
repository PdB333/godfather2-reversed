// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall FUN_008a8bf0(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();
  }
  FUN_0064d390(0,1);
  *this = &PTR_LAB_00e317dc;
  this[6] = 0;
  FUN_00454a10(uVar1);
  this[9] = 2;
  *this = &PTR_LAB_00d79c94;
  this[10] = &PTR_LAB_00d79ba0;
  this[0xc] = &LAB_008a8900;
  this[0xd] = 0;
  this[0xe] = &PTR_LAB_00e35c24;
  this[0xf] = 0xffffffff;
  this[0x10] = 0xffffffff;
  this[0x11] = 0;
  this[0x12] = 0xffffffff;
  this[0x13] = 0xffffffff;
  this[0x14] = 0;
  this[0x15] = 0;
  this[5] = this + 10;
  return this;
}
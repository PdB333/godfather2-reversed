// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)
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
  this[9] = 1;
  *this = &PTR_LAB_00d7a14c;
  this[10] = &PTR_FUN_00d7a12c;
  this[0xd] = 0;
  this[0xc] = &LAB_008a8a00;
  this[0x10] = 0;
  this[0x11] = 0;
  this[0x12] = 0;
  this[5] = this + 10;
  return this;
}
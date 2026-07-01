// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)
{
  int iVar1;
  
  *this = &PTR_FUN_00d6a7a8;
  iVar1 = FUN_004a8f00();
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + -0x58;
  }
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + 0x48;
  }
  this[1] = iVar1;
  this[2] = 0;
  if (iVar1 != 0) {
    this[2] = *(undefined4 *)(iVar1 + 4);
    *(undefined4 **)(iVar1 + 4) = this + 1;
  }
  iVar1 = FUN_004a8f00();
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + -0x58;
  }
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + 0x48;
  }
  this[3] = iVar1;
  this[4] = 0;
  if (iVar1 != 0) {
    this[4] = *(undefined4 *)(iVar1 + 4);
    *(undefined4 **)(iVar1 + 4) = this + 3;
  }
  this[0xb] = *(undefined4 *)(param_2 + 0x28);
  this[0xc] = *(undefined4 *)(param_2 + 0x2c);
  this[0xd] = *(undefined4 *)(param_2 + 0x30);
  this[0xe] = *(undefined4 *)(param_2 + 0x34);
  this[0xf] = *(undefined4 *)(param_2 + 0x38);
  this[0x10] = *(undefined4 *)(param_2 + 0x3c);
  this[0x11] = *(undefined4 *)(param_2 + 0x40);
  return this;
}
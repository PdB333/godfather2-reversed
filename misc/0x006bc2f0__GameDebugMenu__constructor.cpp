// FUNC_NAME: GameDebugMenu::constructor
undefined4 * __thiscall GameDebugMenu::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046e6b0(param_2, 0x4000);              // Some initialization call with size flag
  *this = &PTR_FUN_00d5e880;                  // Set vtable
  this[0xf] = &PTR_LAB_00d5e870;             // +0x3C: some pointer table
  this[0x12] = &PTR_LAB_00d5e86c;            // +0x48: another pointer table
  this[0x14] = &PTR_LAB_00d5e868;            // +0x50: another pointer table
  this[0x15] = &PTR_LAB_00d5e808;            // +0x54: another pointer table
  this[0x16] = &PTR_LAB_00d5e7a0;            // +0x58: another pointer table
  this[0x60] = 0;                            // +0x180: initialize to zero
  this[0x61] = 0;                            // +0x184: initialize to zero
  this[0x62] = 0;                            // +0x188: initialize to zero
  *(undefined2 *)(this + 99) = 0;            // +0x18C: short zero
  *(undefined2 *)((int)this + 0x18e) = 0;    // +0x18E: short zero
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000); // +0x3C: copy from global data
  }
  return this;
}
// Xbox PDB: EARS_Modules_SafeCrackerCSA_SafeCrackerCSA
// FUNC_NAME: MessageQueue::constructor
undefined4 * __thiscall MessageQueue::constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  FUN_008de740(param_2);
  uVar1 = _DAT_00d5780c;
  *this = &PTR_FUN_00d7f730;
  this[0xf] = &PTR_LAB_00d7f720;
  this[0x12] = &PTR_LAB_00d7f71c;
  this[0x14] = &PTR_LAB_00d7f718;
  this[0x15] = &PTR_LAB_00d7f6b8;
  this[0x16] = &PTR_LAB_00d7f650;
  this[0xa0] = 0xffffffff;  // +0x280: some ID or handle
  this[0xa1] = 0xffffffff;  // +0x284: another ID
  this[0xa2] = 0;           // +0x288: count or flag
  this[0xa3] = uVar1;       // +0x28c: some global value
  this[0xa4] = 0xffffffff;  // +0x290: ID
  this[0xa5] = 0xffffffff;  // +0x294: ID
  this[0xa6] = 0;           // +0x298: pointer to message data array
  this[0xa7] = 0;           // +0x29c: current message count
  this[0xa8] = 0;           // +0x2a0: allocated message capacity
  this[0xa9] = 0;           // +0x2a4: pointer to another array
  this[0xaa] = 0;           // +0x2a8: count for second array
  this[0xab] = 0;           // +0x2ac: capacity for second array
  FUN_00408240(&DAT_0112fc98,"iMsgMakePayoutAgain");
  if (DAT_0112fc98 != 0) {
    FUN_00408900(this + 0xf,&DAT_0112fc98,0x8000);
  }
  param_2 = 4;
  do {
    iVar3 = this[0xa8];
    if (this[0xa7] == iVar3) {
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = iVar3 * 2;
      }
      FUN_008defe0(iVar3);
    }
    puVar2 = (undefined4 *)(this[0xa7] * 0x10 + this[0xa6]);
    this[0xa7] = this[0xa7] + 1;
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = 0xbadbadba;
      puVar2[1] = 0xbeefbeef;
      puVar2[2] = 0xeac15a55;
      puVar2[3] = 0x91100911;
    }
    iVar3 = this[0xab];
    if (this[0xaa] == iVar3) {
      if (iVar3 == 0) {
        iVar3 = 1;
      }
      else {
        iVar3 = iVar3 * 2;
      }
      FUN_00486800(iVar3);
    }
    puVar2 = (undefined4 *)(this[0xa9] + this[0xaa] * 4);
    this[0xaa] = this[0xaa] + 1;
    if (puVar2 != (undefined4 *)0x0) {
      *puVar2 = 0;
    }
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return this;
}
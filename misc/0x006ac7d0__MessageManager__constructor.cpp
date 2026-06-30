// FUNC_NAME: MessageManager::constructor
undefined4 * __fastcall MessageManager::constructor(undefined4 *this)
{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar1 = this + 1;
  DAT_0112a554 = this;
  *puVar1 = &PTR_FUN_00e2f19c;
  this[2] = 1;
  this[3] = 0;
  *this = &PTR_FUN_00d5db44;
  *puVar1 = &PTR_LAB_00d5db34;
  puVar3 = this + 4;
  iVar4 = 0x13;
  do {
    puVar3[3] = 0;
    puVar3[2] = 0;
    puVar3[1] = 0;
    *puVar3 = 0;
    puVar3[4] = 0xffffffff;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0;
    puVar3[9] = 4;
    puVar3[10] = 0;
    puVar3[0xb] = 0;
    puVar3 = puVar3 + 0xc;
    iVar4 = iVar4 + -1;
  } while (-1 < iVar4);
  piVar2 = this + 0xfc;
  this[0xf4] = 0x14;
  *piVar2 = 0;
  *(undefined2 *)(this + 0xfd) = 0;
  *(undefined2 *)((int)this + 0x3f6) = 0;
  this[0xf5] = 0;
  this[0xf6] = 0;
  this[0xf7] = 0;
  this[0xf8] = 0;
  this[0xf9] = 0;
  this[0xfa] = 0;
  this[0xfb] = 0;
  FUN_00408240(piVar2,"iMsgBankUpdateMoney");
  FUN_00408240(&DAT_0112a578,"iMsgTransferStolenMoney");
  FUN_00408240(&DAT_0112b36c,"iMsgPlayerReset");
  FUN_00408240(&DAT_0112a564,"iMsgEndTruckHeist");
  FUN_00408240(&DAT_0112a56c,"iMsgEndFakeBankHeist");
  if (*piVar2 != 0) {
    FUN_00408900(puVar1,piVar2,0x8000);
  }
  if (DAT_0112a578 != 0) {
    FUN_00408900(puVar1,&DAT_0112a578,0x8000);
  }
  if (DAT_0112b36c != 0) {
    FUN_00408900(puVar1,&DAT_0112b36c,0x8000);
  }
  if (DAT_0112a564 != 0) {
    FUN_00408900(puVar1,&DAT_0112a564,0x8000);
  }
  if (DAT_0112a56c != 0) {
    FUN_00408900(puVar1,&DAT_0112a56c,0x8000);
  }
  return this;
}
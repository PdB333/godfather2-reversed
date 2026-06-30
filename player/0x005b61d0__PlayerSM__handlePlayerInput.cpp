// FUNC_NAME: PlayerSM::handlePlayerInput
undefined4 FUN_005b61d0(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint *puVar4;
  
  FUN_005a0d00(0);
  FUN_0059c3b0();
  cVar2 = FUN_005a4140();
  if (cVar2 == '\0') {
    cVar2 = FUN_005a3c40();
    if (cVar2 == '\0') {
      iVar3 = FUN_005a8fe0();
    }
    else {
      iVar3 = FUN_005a3a40();
      uVar1 = *(undefined4 *)(iVar3 + 0xc);
      FUN_0059c3b0();
      iVar3 = FUN_005a19c0();
      iVar3 = FUN_005bb050(*(undefined4 *)(*(int *)(iVar3 + 8) + 0x10),uVar1);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = FUN_005a8fe0();
        iVar3 = iVar3 + 1;
      }
    }
    iVar3 = iVar3 + -1;
    if (-1 < iVar3) {
      FUN_0059c3b0(iVar3);
      FUN_005b8fe0(iVar3);
      FUN_0059c3b0();
      iVar3 = FUN_005a19c0();
      puVar4 = (uint *)(iVar3 + 0x14);
      *puVar4 = *puVar4 ^ ((uint)(param_1 != 0) << 0x18 ^ *puVar4) & 0x1000000;
    }
  }
  return DAT_0119cbbc;
}
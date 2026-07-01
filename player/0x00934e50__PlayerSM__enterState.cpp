// FUNC_NAME: PlayerSM::enterState
void PlayerSM::enterState(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_01223484;
  iVar2 = 0;
  if (((DAT_01223484 != 0) &&
      (*(int *)(DAT_01223484 + 0x28) != 0 || *(int *)(DAT_01223484 + 0x2c) != 0)) &&
     ((undefined4 *)(DAT_01223484 + 0x28) != (undefined4 *)0x0)) {
    *(undefined4 *)(DAT_01223484 + 0x28) = 0;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
  }
  iVar1 = FUN_009c8e50(0xf0);
  if (iVar1 != 0) {
    iVar2 = FUN_00982280(0);
  }
  *(undefined4 *)(iVar2 + 0xc) = 3;
  FUN_00981eb0(param_1);
  FUN_00982400(1);
  *(undefined1 **)(iVar2 + 0x14) = &LAB_00933a70;
  FUN_00982e10();
  return;
}
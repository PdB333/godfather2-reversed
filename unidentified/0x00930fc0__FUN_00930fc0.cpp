// FUNC_NAME: FUN_00930fc0
undefined4 FUN_00930fc0(undefined4 param_1)

{
  char extraout_AL;
  undefined3 uVar1;
  undefined3 extraout_var;
  undefined1 uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = (undefined3)((uint)DAT_01129814 >> 8);
  uVar3 = 0;
  uVar4 = 0xf;
  if (*(byte *)(DAT_01129814 + 0x14) < 0x10) {
    uVar3 = (uint)*(byte *)(DAT_01129814 + 0x14);
    uVar4 = uVar3;
  }
  uVar2 = 0;
  for (; uVar3 <= uVar4; uVar3 = uVar3 + 1) {
    FUN_00410280(uVar3,param_1,2);
    if (extraout_AL != '\0') {
      uVar2 = 1;
    }
    uVar1 = extraout_var;
  }
  return CONCAT31(uVar1,uVar2);
}
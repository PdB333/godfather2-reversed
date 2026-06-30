// FUNC_NAME: BitStream::readBits
int BitStream::readBits(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int unaff_EDI;
  
  if (param_1 + 9999U < 10000) {
    param_1 = (*(int *)(unaff_EDI + 8) - *(int *)(unaff_EDI + 0xc) >> 3) + 1 + param_1;
  }
  if (*(uint *)(*(int *)(unaff_EDI + 0x10) + 0x20) <= *(uint *)(*(int *)(unaff_EDI + 0x10) + 0x24))
  {
    FUN_00627360();
  }
  puVar4 = *(undefined4 **)(unaff_EDI + 8);
  *puVar4 = 4;
  uVar2 = FUN_00638920();
  puVar4[1] = uVar2;
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 8;
  FUN_00625e70();
  iVar3 = FUN_00628380();
  if (iVar3 < 0) {
    FUN_00628430();
    if (param_1 < 1) {
      puVar4 = (undefined4 *)FUN_00625430();
    }
    else {
      puVar4 = (undefined4 *)(*(int *)(unaff_EDI + 0xc) + -8 + param_1 * 8);
    }
    puVar5 = *(undefined4 **)(unaff_EDI + 8);
    *puVar5 = *puVar4;
    puVar5[1] = puVar4[1];
    *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 8;
    FUN_00625e70();
    iVar3 = FUN_00628380();
    if (iVar3 < 0) {
      iVar3 = 1;
      while( true ) {
        if (param_1 < 1) {
          FUN_00625430();
        }
        puVar5 = (undefined4 *)FUN_00637f10();
        puVar4 = *(undefined4 **)(unaff_EDI + 8);
        *puVar4 = *puVar5;
        puVar4[1] = puVar5[1];
        *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 8;
        iVar1 = *(int *)(unaff_EDI + 8);
        iVar6 = FUN_00625740();
        *(int *)(unaff_EDI + 8) = iVar1 + -8;
        if (iVar6 == 0) break;
        iVar3 = iVar3 + 1;
      }
      iVar3 = iVar3 + -1;
    }
  }
  return iVar3;
}
// FUNC_NAME: PlayerActionableInfo::constructor
undefined2 * PlayerActionableInfo::constructor(int *param_1)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  if (DAT_01206690 == (code *)0x0) {
    return (undefined2 *)0x0;
  }
  puVar1 = (undefined2 *)(*DAT_01206690)(0x1e3c);
  if (puVar1 != (undefined2 *)0x0) {
    uVar2 = FUN_00672e60(param_1);
    iVar4 = *param_1;
    *(undefined4 *)(puVar1 + 0xf1c) = uVar2;
    if (iVar4 == 0) {
      *puVar1 = 0;
      *(undefined4 *)(puVar1 + 2) = 0;
      puVar1[4] = 0;
      *(undefined4 *)(puVar1 + 6) = 0;
      puVar1[8] = 0;
      *(undefined4 *)(puVar1 + 10) = 0;
      puVar1[0xd] = 0;
      puVar1[0xc] = 0;
      puVar3 = (undefined4 *)(puVar1 + 0x18);
      iVar4 = 0x80;
      do {
        *(undefined2 *)((int)puVar3 + -0x12) = 0xffff;
        *puVar3 = 0;
        puVar3[1] = 0;
        puVar3 = puVar3 + 0xf;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      *(undefined4 *)(puVar1 + 0xf18) = 0x48;
      *(undefined4 *)(puVar1 + 0xf1a) = 0x48;
      *(undefined4 *)(puVar1 + 0xf10) = 0;
      *(undefined4 *)(puVar1 + 0xf12) = 0;
      puVar1[0xf0e] = 0xffff;
      puVar1[0xf14] = 3;
      puVar1[0xf15] = 1;
      puVar1[0xf16] = 0x409;
      puVar1[0xf17] = 4;
      return puVar1;
    }
    (*DAT_01206694)(puVar1);
    puVar1 = (undefined2 *)0x0;
  }
  return puVar1;
}
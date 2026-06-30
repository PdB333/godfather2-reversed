// FUNC_NAME: HuffmanEncoder::encodeString
undefined4 HuffmanEncoder::encodeString(char *inputStr, uint maxLen)

{
  int iVar1;
  char *pcVar2;
  char cVar3;
  int thisPtr;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  
  uVar5 = maxLen;
  pcVar2 = inputStr;
  if (inputStr == (char *)0x0) {
    if ((*(int *)(thisPtr + 0x18) + 1U <= *(uint *)(thisPtr + 0x30)) ||
       (cVar3 = FUN_0064b7c0(), cVar3 != '\0')) {
      pbVar4 = (byte *)(*(int *)(thisPtr + 0xc) + (*(uint *)(thisPtr + 0x18) >> 3));
      *pbVar4 = *pbVar4 & ~('\x01' << ((byte)*(uint *)(thisPtr + 0x18) & 7));
      *(int *)(thisPtr + 0x18) = *(int *)(thisPtr + 0x18) + 1;
    }
    inputStr = (char *)0x0;
    FUN_0064b810(8,&inputStr);
    return 1;
  }
  if (DAT_0120588e == '\0') {
    FUN_0065a940();
  }
  pcVar7 = pcVar2;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  uVar8 = (int)pcVar7 - (int)(pcVar2 + 1);
  if (uVar5 < (uint)((int)pcVar7 - (int)(pcVar2 + 1))) {
    uVar8 = uVar5;
  }
  uVar6 = 0;
  uVar5 = 0;
  if (uVar8 != 0) {
    do {
      pbVar4 = (byte *)(pcVar2 + uVar5);
      uVar5 = uVar5 + 1;
      uVar6 = uVar6 + *(byte *)(DAT_01223360 + 4 + (uint)*pbVar4 * 0xc);
    } while (uVar5 < uVar8);
  }
  if (uVar8 * 8 <= uVar6) {
    if ((*(int *)(thisPtr + 0x18) + 1U <= *(uint *)(thisPtr + 0x30)) ||
       (cVar3 = FUN_0064b7c0(), cVar3 != '\0')) {
      pbVar4 = (byte *)((*(uint *)(thisPtr + 0x18) >> 3) + *(int *)(thisPtr + 0xc));
      *pbVar4 = *pbVar4 & ~('\x01' << ((byte)*(uint *)(thisPtr + 0x18) & 7));
      *(int *)(thisPtr + 0x18) = *(int *)(thisPtr + 0x18) + 1;
    }
    inputStr = (char *)uVar8;
    FUN_0064b810(8,&inputStr);
    FUN_0064b810(uVar8 * 8,pcVar2);
    return 1;
  }
  if ((*(int *)(thisPtr + 0x18) + 1U <= *(uint *)(thisPtr + 0x30)) ||
     (cVar3 = FUN_0064b7c0(), cVar3 != '\0')) {
    pbVar4 = (byte *)((*(uint *)(thisPtr + 0x18) >> 3) + *(int *)(thisPtr + 0xc));
    *pbVar4 = *pbVar4 | '\x01' << ((byte)*(uint *)(thisPtr + 0x18) & 7);
    *(int *)(thisPtr + 0x18) = *(int *)(thisPtr + 0x18) + 1;
  }
  inputStr = (char *)uVar8;
  FUN_0064b810(8,&inputStr);
  uVar5 = 0;
  if (uVar8 != 0) {
    do {
      iVar1 = DAT_01223360 + (uint)(byte)pcVar2[uVar5] * 0xc;
      FUN_0064b810(*(undefined1 *)(iVar1 + 4),iVar1 + 8);
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar8);
  }
  return 1;
}
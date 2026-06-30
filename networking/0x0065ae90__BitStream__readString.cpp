// FUNC_NAME: BitStream::readString
undefined4 BitStream::readString(int param_1)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  int unaff_ESI;
  uint uVar4;
  int iVar5;
  uint local_4;
  
  if (DAT_0120588e == '\0') {
    FUN_0065a940();
  }
  uVar4 = *(uint *)(unaff_ESI + 0x18);
  if (*(uint *)(unaff_ESI + 0x2c) < uVar4) {
    *(undefined1 *)(unaff_ESI + 0x1c) = 1;
  }
  else {
    bVar1 = *(byte *)((uVar4 >> 3) + *(int *)(unaff_ESI + 0xc));
    *(uint *)(unaff_ESI + 0x18) = uVar4 + 1;
    if ((bVar1 & (byte)(1 << ((byte)uVar4 & 7))) != 0) {
      uVar4 = 0;
      local_4 = 0;
      FUN_0064b9e0(8,&local_4);
      if ((local_4 & 0xff) != 0) {
        do {
          iVar5 = 0;
          do {
            uVar3 = *(uint *)(unaff_ESI + 0x18);
            if (*(uint *)(unaff_ESI + 0x2c) < uVar3) {
              *(undefined1 *)(unaff_ESI + 0x1c) = 1;
LAB_0065af3c:
              sVar2 = *(short *)(DAT_01223354 + 4 + iVar5 * 8);
            }
            else {
              bVar1 = *(byte *)((uVar3 >> 3) + *(int *)(unaff_ESI + 0xc));
              *(uint *)(unaff_ESI + 0x18) = uVar3 + 1;
              if ((bVar1 & (byte)(1 << ((byte)uVar3 & 7))) == 0) goto LAB_0065af3c;
              sVar2 = *(short *)(DAT_01223354 + 6 + iVar5 * 8);
            }
            iVar5 = (int)sVar2;
          } while (-1 < iVar5);
          *(undefined1 *)(param_1 + uVar4) = *(undefined1 *)(DAT_01223360 + iVar5 * -0xc + -7);
          uVar4 = uVar4 + 1;
        } while (uVar4 < (local_4 & 0xff));
      }
      *(undefined1 *)((local_4 & 0xff) + param_1) = 0;
      return 1;
    }
  }
  local_4 = 0;
  FUN_0064b9e0(8,&local_4);
  uVar4 = local_4 & 0xff;
  FUN_0064b9e0(uVar4 * 8,param_1);
  *(undefined1 *)(uVar4 + param_1) = 0;
  return 1;
}
// FUNC_NAME: BitStream::readBits
void BitStream::readBits(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int local_10 [3];
  code *local_4;
  
  iVar3 = param_1;
  FUN_00472c10(param_1);
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (*(uint *)(iVar3 + 0x2c) < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
  }
  else {
    param_1 = 1;
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
    *(uint *)(iVar3 + 0x18) = uVar2 + 1;
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
      FUN_0064b9e0(0x20,&param_1);
    }
  }
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (*(uint *)(iVar3 + 0x2c) < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
  }
  else {
    param_1 = 1;
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
    *(uint *)(iVar3 + 0x18) = uVar2 + 1;
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
      FUN_0064b9e0(0x20,&param_1);
    }
  }
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (*(uint *)(iVar3 + 0x2c) < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
  }
  else {
    param_1 = 1;
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
    *(uint *)(iVar3 + 0x18) = uVar2 + 1;
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
      FUN_0064b9e0(0x80,local_10);
    }
  }
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (*(uint *)(iVar3 + 0x2c) < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
  }
  else {
    param_1 = 1;
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
    *(uint *)(iVar3 + 0x18) = uVar2 + 1;
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
      FUN_0064b9e0(0x20,&param_1);
      FUN_0064b9e0(0x20,&param_1);
      FUN_0064b9e0(0x20,&param_1);
    }
  }
  uVar2 = *(uint *)(iVar3 + 0x18);
  uVar5 = *(uint *)(iVar3 + 0x2c);
  if (uVar5 < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
  }
  else {
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
    uVar4 = uVar2 + 1;
    *(uint *)(iVar3 + 0x18) = uVar4;
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
      if (uVar5 < uVar4) {
        *(undefined1 *)(iVar3 + 0x1c) = 1;
      }
      else {
        bVar1 = *(byte *)((uVar4 >> 3) + *(int *)(iVar3 + 0xc));
        *(uint *)(iVar3 + 0x18) = uVar2 + 2;
        if ((bVar1 & (byte)(1 << ((byte)uVar4 & 7))) != 0) {
          local_10[0] = 0;
          local_10[1] = 0;
          local_10[2] = 0;
          local_4 = (code *)0x0;
          FUN_004a9d10(iVar3,local_10);
          if (local_10[0] != 0) {
            (*local_4)(local_10[0]);
          }
        }
      }
      FUN_0064b9e0(0x20,&param_1);
      FUN_0064b9e0(0x20,&param_1);
      FUN_0064b9e0(0x20,&param_1);
      uVar5 = *(uint *)(iVar3 + 0x2c);
      if (uVar5 < *(uint *)(iVar3 + 0x18)) {
        *(undefined1 *)(iVar3 + 0x1c) = 1;
      }
      else {
        *(uint *)(iVar3 + 0x18) = *(uint *)(iVar3 + 0x18) + 1;
      }
    }
  }
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (uVar5 < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
    return;
  }
  bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
  *(uint *)(iVar3 + 0x18) = uVar2 + 1;
  if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
    FUN_004a8ec0(0);
    FUN_004a9360(iVar3,local_10);
  }
  return;
}
// FUNC_NAME: BitStream::readBit
void BitStream::readBit(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = param_1;
  FUN_00472c10(param_1);
  uVar2 = *(uint *)(iVar3 + 0x18);
  if (*(uint *)(iVar3 + 0x2c) < uVar2) {
    *(undefined1 *)(iVar3 + 0x1c) = 1;
    return;
  }
  bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(iVar3 + 0xc));
  *(uint *)(iVar3 + 0x18) = uVar2 + 1;
  if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
    FUN_0064b9e0(0x20,&param_1);
  }
  return;
}
// FUNC_NAME: BitStream::readBits
short __fastcall BitStream::readBits(undefined4 *param_1)
{
  char cVar1;
  byte bVar2;
  short sVar3;
  byte *pbVar4;
  
  if (*(short *)(param_1 + 1) == 0) {
    cVar1 = *(char *)*param_1;
    pbVar4 = (byte *)((char *)*param_1 + 1);
  }
  else {
    pbVar4 = (byte *)((char *)*param_1 + 1);
    cVar1 = (*pbVar4 >> 4) + *(char *)*param_1 * 0x10;
  }
  bVar2 = *pbVar4;
  *param_1 = pbVar4;
  if (*(short *)(param_1 + 1) == 0) {
    *(undefined2 *)(param_1 + 1) = 1;
    bVar2 = bVar2 >> 4;
  }
  else {
    bVar2 = bVar2 & 0xf;
    *(undefined2 *)(param_1 + 1) = 0;
    *param_1 = pbVar4 + 1;
  }
  sVar3 = cVar1 * 0x10 + (ushort)bVar2;
  if ((ushort)(sVar3 + 0x80U) < 0x100) {
    if (*(short *)(param_1 + 1) == 0) {
      cVar1 = *(char *)*param_1;
      *param_1 = (char *)*param_1 + 1;
      return sVar3 * 0x100 + (short)cVar1;
    }
    cVar1 = *(char *)*param_1;
    pbVar4 = (byte *)((char *)*param_1 + 1);
    *param_1 = pbVar4;
    sVar3 = sVar3 * 0x100 + (short)(char)((*pbVar4 >> 4) + cVar1 * 0x10);
  }
  return sVar3;
}
// FUNC_NAME: BitStream::readByte
uint BitStream::readByte(void)
{
  byte bVar1;
  byte *pbVar2;
  int *unaff_ESI;
  int local_4;
  
  pbVar2 = (byte *)(*(code *)unaff_ESI[2])(0,unaff_ESI[3],&local_4);
  if ((pbVar2 != (byte *)0x0) && (local_4 != 0)) {
    unaff_ESI[1] = (int)pbVar2;
    *unaff_ESI = local_4 + -1;
    bVar1 = *pbVar2;
    unaff_ESI[1] = (int)(pbVar2 + 1);
    return (uint)bVar1;
  }
  return 0xffffffff;
}
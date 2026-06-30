// FUNC_NAME: StreamBuffer::readByte
uint StreamBuffer::readByte(void)
{
  byte bVar1;
  byte *pbVar2;
  int *this; // unaff_ESI
  int local_4;

  if (*this != 0) {
LAB_00638569:
    return (uint)*(byte *)this[1];
  }
  pbVar2 = (byte *)(*(code *)this[2])(0, this[3], &local_4);
  if ((pbVar2 != (byte *)0x0) && (local_4 != 0)) {
    this[1] = (int)pbVar2;
    *this = local_4 + -1;
    bVar1 = *pbVar2;
    this[1] = (int)(pbVar2 + 1);
    if (bVar1 != 0xffffffff) {
      *this = local_4;
      this[1] = (int)pbVar2;
      goto LAB_00638569;
    }
  }
  return 0xffffffff;
}
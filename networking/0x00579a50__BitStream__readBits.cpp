// FUNC_NAME: BitStream::readBits
void BitStream::readBits(void)
{
  byte *pbVar1;
  uint uVar2;
  undefined4 *unaff_EDI;
  
  pbVar1 = (byte *)*unaff_EDI;
  uVar2 = *pbVar1 & 0xf;
  if (uVar2 == 5) {
    *unaff_EDI = pbVar1 + *(ushort *)(pbVar1 + 2);
    return;
  }
  *unaff_EDI = pbVar1 + *(int *)(&DAT_00e2c758 + uVar2 * 4) *
                        ((uint)pbVar1[1] << 4 | (uint)(*pbVar1 >> 4)) +
                        *(int *)(&DAT_00e2c720 + uVar2 * 4);
  return;
}
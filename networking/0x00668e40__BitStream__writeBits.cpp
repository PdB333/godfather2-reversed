// FUNC_NAME: BitStream::writeBits
int __thiscall BitStream::writeBits(int *this, int numBits)
{
  int *in_EAX;
  int iVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  int local_c;
  
  if ((this != in_EAX) && (iVar1 = FUN_00665ce0(), iVar1 != 0)) {
    return iVar1;
  }
  if ((in_EAX[1] < numBits / 0x1c + 1 + *in_EAX) && (iVar1 = FUN_00667740(), iVar1 != 0)) {
    return iVar1;
  }
  if ((0x1b < numBits) && (iVar1 = FUN_006687e0(numBits / 0x1c), iVar1 != 0)) {
    return iVar1;
  }
  if (numBits % 0x1c == 0) {
LAB_00668f1f:
    iVar1 = *in_EAX;
    if (iVar1 < 1) goto LAB_00668f3c;
    do {
      if (*(int *)(in_EAX[3] + -4 + *in_EAX * 4) != 0) break;
      iVar1 = *in_EAX + -1;
      *in_EAX = iVar1;
    } while (0 < iVar1);
  }
  else {
    bVar2 = (byte)(numBits % 0x1c);
    local_c = 0;
    uVar4 = 0;
    puVar5 = (uint *)in_EAX[3];
    if (0 < *in_EAX) {
      do {
        uVar3 = *puVar5 >> (0x1c - bVar2 & 0x1f) & (1 << (bVar2 & 0x1f)) - 1U;
        *puVar5 = (*puVar5 << (bVar2 & 0x1f) | uVar4) & 0xfffffff;
        local_c = local_c + 1;
        uVar4 = uVar3;
        puVar5 = puVar5 + 1;
      } while (local_c < *in_EAX);
      if (uVar3 != 0) {
        *(uint *)(in_EAX[3] + *in_EAX * 4) = uVar3;
        *in_EAX = *in_EAX + 1;
      }
      goto LAB_00668f1f;
    }
  }
  iVar1 = *in_EAX;
LAB_00668f3c:
  if (iVar1 == 0) {
    in_EAX[2] = 0;
  }
  return 0;
}
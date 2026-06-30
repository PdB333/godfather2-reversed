// FUNC_NAME: TNLConnection::sendPacket
void TNLConnection::sendPacket(void)
{
  uint *puVar1;
  int *in_EAX; // this pointer
  uint uVar2;
  int *unaff_EDI; // packetData pointer
  undefined4 uVar3;
  
  if (unaff_EDI[8] != 0) {  // +0x20: packetFlags / sequence info
    if (*unaff_EDI == 0xc) {  // +0x00: packetType == 12 (reliable?)
      // Clear bits 6-0 and set bit 5 in flag field at +0x0C
      puVar1 = (uint *)(*(int *)(*in_EAX + 0xc) + unaff_EDI[1] * 4); // +0x00: vtable? +0x0C: some array, +0x04: index
      *puVar1 = *puVar1 & 0xffff803f;
      uVar3 = *(undefined4 *)(in_EAX[3] + 8); // +0x0C: some pointer, +0x08: data
      // +0x1C: multiplier field, +0x14: some other field +4
      uVar2 = unaff_EDI[7] * 0x40 - 0x40U | *(int *)(unaff_EDI[5] + 4) << 0x18 | 0x20;
    }
    else {
      if (*unaff_EDI != 0) {  // non-zero packetType
        FUN_00642ec0();  // some packet-related function
      }
      uVar3 = *(undefined4 *)(in_EAX[3] + 8);
      uVar2 = unaff_EDI[7] * 0x40 - 0x21U | *(int *)(unaff_EDI[5] + 4) << 0x18 | 0x1f;
    }
    FUN_006438e0(uVar2,uVar3); // send/process packet
    in_EAX[9] = *(int *)(unaff_EDI[5] + 4) + 1; // +0x24: nextSequenceNum
  }
  return;
}
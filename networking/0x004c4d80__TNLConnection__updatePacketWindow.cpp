// FUNC_NAME: TNLConnection::updatePacketWindow
void TNLConnection::updatePacketWindow(int param_1, undefined8 *param_2)
{
  bool bVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  int iVar5;
  undefined8 *puVar6;
  
  iVar5 = (int)*(short *)(in_EAX + 0x2a); // +0x2a: currentSequenceIndex
  if (-1 < iVar5) {
    iVar4 = iVar5 * 0x20; // 32-byte packet window entry size
    iVar3 = *(int *)(unaff_ESI + 0x10) + iVar4; // +0x10: packetWindowBase
    iVar2 = FUN_004c4ae0(); // getCurrentSequenceNumber
    if ((*(int *)(iVar3 + 0xc) != param_1) || (bVar1 = false, *(int *)(iVar3 + 0x14) != iVar2)) {
      bVar1 = true; // packet mismatch detected
    }
    iVar3 = 0;
    if ((*(char *)(unaff_ESI + 0x3c) != '\0') && (bVar1)) { // +0x3c: isReliable
      iVar3 = FUN_004c4870(unaff_ESI,1); // allocateReliablePacket
    }
    puVar6 = (undefined8 *)(iVar5 * 0x10 + *(int *)(unaff_ESI + 4)); // +0x04: packetDataArray
    *puVar6 = *param_2; // copy packet header (16 bytes)
    puVar6[1] = param_2[1];
    if (bVar1) {
      *(int *)(*(int *)(unaff_ESI + 0x10) + 0xc + iVar4) = param_1; // update sequence number
      *(int *)(*(int *)(unaff_ESI + 0x10) + 0x14 + iVar4) = iVar2; // update ack number
      if ((*(char *)(unaff_ESI + 0x3c) != '\0') && (iVar3 != 0)) {
        FUN_004c4730(unaff_ESI,iVar3); // sendReliablePacket
        *(undefined1 *)(unaff_ESI + 0x18) = 0; // +0x18: packetSendFlag
      }
    }
  }
  return;
}
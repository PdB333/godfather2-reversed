// FUNC_NAME: TNLConnection::findNextPacketToSend
void __thiscall TNLConnection::findNextPacketToSend(int thisPtr)
{
  int packetNode;
  char packetFlag;
  
  packetNode = *(int *)(thisPtr + 8); // +0x08: firstPacketNode in send queue
  packetFlag = *(char *)(packetNode + 0x25); // +0x25: packetSendFlag (0 = not sent, 1 = sent)
  while (packetFlag == '\0') {
    packetNode = *(int *)(packetNode + 8); // +0x08: nextPacketNode in linked list
    packetFlag = *(char *)(packetNode + 0x25);
  }
  return;
}
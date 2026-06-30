// FUNC_NAME: TNLConnection::sendPacket
void TNLConnection::sendPacket(BitStream* packet)
{
  NetSession* session = getNetSession();
  if (session == nullptr) {
    return;
  }
  
  undefined1 dummyBuffer1[8];
  undefined1 dummyBuffer2[8];
  undefined1 serializedBuffer[256];
  undefined1 packetBuffer[636];  // 636 bytes for packet data
  
  fillBuffer(0x40, dummyBuffer1);  // memset(dummyBuffer1, 0, 0x40)
  fillBuffer(0x40, dummyBuffer2);  // memset(dummyBuffer2, 0, 0x40)
  
  if (isConnectionActive()) {
    return;
  }
  if (isConnectionActive()) {  // double check? Possibly different flag
    return;
  }
  
  // Align packet's bit position to 8-byte boundary
  uint alignedPos = (packet->bitPosition + 7) & 0xFFFFFFF8;
  packet->bitPosition = alignedPos;
  
  if (session->flag131 != 0) {  // +0x131: some send-enable flag
    buildPacket(packetBuffer);  // assemble packet data
    char result = validatePacket(packet, packetBuffer);
    if (result == 0) {
      handleAck();
      return;
    }
    handleAck();
  }
  
  // Serialize the packet
  serializePacket(serializedBuffer);
  
  // Virtual function call at vtable offset 0x10 (sendData?)
  // First parameter 3 indicates packet type or priority
  (this->vtable[0x10])(3, serializedBuffer);
  
  // Update session state or queue
  queueForSend(this, session);
}